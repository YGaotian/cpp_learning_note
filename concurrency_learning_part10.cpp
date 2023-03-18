#include "header_learning.h"
#include <thread>
#include <future>

/*--------------------------------------------------------------------------
并不是所有运算符都被原子操作所支持，同样是对变量的值+1，++能被正常执行，但其他的并不是全都行
--------------------------------------------------------------------------*/
//全局原子对象声明
std::atomic<int> atomicIntObj;

//原子操作线程入口函数1
void atomicOperate_1()
{
    for (int i = 0; i < 10000000; ++i)
        atomicIntObj = atomicIntObj + 1;
}

//原子操作线程入口函数2
void atomicOperate_2()
{
    for (int i = 0; i < 10000000; ++i)
        atomicIntObj = atomicIntObj - 1;
}

void asyncTwoPolicyTest()
{
    std::cout << "asyncTwoPolicyTest is running!" << std::endl;
}


//原子操作-续
void atomicUsage_continue()
{
    atomicIntObj = 10;
    std::thread atomicThreadNotSupportedOne_add(atomicOperate_1);
    std::thread atomicThreadNotSupportedOne_minus(atomicOperate_2);
    atomicThreadNotSupportedOne_add.join();
    atomicThreadNotSupportedOne_minus.join();
    std::cout << atomicIntObj << std::endl;
    //通过上面的代码知道，a = a + 1 这样的操作并不被atomic支持，执行结果依然不符合我们的意图，然而其实 a += 1 是可以的
    //并且，对原子对象赋值，递增是原子操作，读取原子对象也是原子操作，但是 std::cout << atomicIntObj << std::endl; 这样对原子对象进行输出的一整行代码并不是原子操作
    //所以说，如果在循环中输出一个正在同时被写入数据的原子对象，屏幕上输出的便是原子对象的曾经值
    //然后，原子对象不允许拷贝赋值或拷贝构造，所以下面的代码是无法通过编译的
    /// std::atomic<int> at2 = atomicIntObj;    //报错
    //如果希望用一个原子对象的值对另一个原子对象进行赋值，可以使用 load() 方法，这个方法可以读取一个原子对象存储的值
    std::atomic<int> atomicIntObj_2(atomicIntObj.load());
    std::cout << "atomicIntObj_2 is " << atomicIntObj_2.load() << std::endl;
    //有读就有写，所以可以使用 store() 方法来以原子操作的方式对原子对象写入数据
    atomicIntObj_2.store(123);
    std::cout << "atomicIntObj_2 is " << atomicIntObj_2.load() << std::endl;
}


/*--------------------------------------------------------------------------
thread 和 async 的区别就在于，thread 一定会创建一个新的线程，但如果系统资源比较紧张，线程可能会创建失败，导致程序运行崩溃
而 async 可以由我们手动指定创建策略，如果不指定，则会视情况决定是否创建新线程，它也可能以 deferred 策略执行异步任务，即等到调用 get 或 wait 方法时再执行
我们在创建 async 的时候，可以写 std::launch::async | std::launch::deferred，这样表示两种创建策略都可以，具体使用哪一种由系统决定，这种创建策略也就是默认的创建策略，效果是相同的
--------------------------------------------------------------------------*/
//async-续
void asyncUsage_continue()
{
    //如果我们使用了默认的创建策略，那么我们的程序就可能成功创建新线程，但是当然也有不创建的可能，那我们写代码的时候就需要去区分不同的情况，以使用不同的方法完成后续的任务
    //我们去区分不同情况的方法就是使用 future 的 wait_for() 方法，去根据它的返回值判断当前有没有创建新的线程，之前已经说过，它返回枚举值，分别是 ready / timeout / deferred
    std::future<void> asyncTwoPolicyFuture = std::async(std::launch::async | std::launch::deferred, asyncTwoPolicyTest);
    using namespace std::chrono;
    //此处不需要等太久，所以写1秒即可，由于提供了 using namespace std::chrono; 所以可以直接写1s，或者10min，2h，7ms，9ns，20us之类的，否则应该写 std::chrono::second(0)
    std::future_status asyncTskStatus = asyncTwoPolicyFuture.wait_for(1s);
    /*--------------------------------------------------------------------------------------------------------------------------------------------
    这些时间单位后缀的运算符声明于命名空间 std::literals::chrono_literals，其中 literals 与 chrono_literals 为内联命名空间
    能通过 using namespace std::literals / using namespace std::chrono_literals 及 using namespace std::literals::chrono_literals 取得对这些运算符的访问。
    另外，在命名空间 std::chrono 中，标准库提供 using namespace literals::chrono_literals; 指令
    故若程序员使用 using namespace std::chrono; 取得对 chrono 库中的类的访问，则对应的字面量运算符亦变为可见
    --------------------------------------------------------------------------------------------------------------------------------------------*/
    switch (asyncTskStatus)
    {
    case std::future_status::ready:
        std::cout << "async ready" << std::endl;
        asyncTwoPolicyFuture.wait();    //既然异步任务已经运行了，那我们就可以直接 get 返回值了，当然，由于我们的异步任务没有返回值，所以此处写 wait
        break;
    case std::future_status::timeout:
        std::cout << "async timeout，我等，我等" << std::endl;
        asyncTwoPolicyFuture.wait();
        break;
    case std::future_status::deferred:
        std::cout << "async deferred, now begin running" << std::endl;
        asyncTwoPolicyFuture.wait();    //因为是deferred，所以这里既然检测到了，我们就希望这个异步任务从此就可以执行了，所以调用一下 wait 或者 get
        break;
    }   //上述代码竟然都得用同样的行为来处理不同的情况，然而实际工程中可能不会只有两行代码，会对不同的情况进行更多的不同的操作来保证程序能被正确执行，而不仅仅是打印一行文字然后等待任务执行完毕
}



//本节主调函数
void concurrency_learning_part10()
{
    atomicUsage_continue();
    asyncUsage_continue();
}
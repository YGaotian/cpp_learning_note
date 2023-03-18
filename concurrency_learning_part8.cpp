#include "header_learning.h"
#include <thread>
#include <future>

/*
std::async 是个函数模板，如果我们希望线程能有返回值，我们就可以使用它，它用来启动一个异步任务，启动一个异步任务的意思就是创建一个线程并执行线程入口函数
这个函数模板返回一个 std::future 类模板对象，这个对象内就有线程入口函数的返回结果，我们可以通过调用 future 的成员函数 get() 来获取线程返回结果
所以说，std::future 提供了一种能获取到异步操作结果（即可能无法立刻得到，但将来某个时刻线程执行完毕能得到的结果）的机制，
*/

//线程入口函数
int asyncThreadFunc_1(int returnValue)
{
    std::cout << "Sub thread: common function with id- " << std::this_thread::get_id() << std::endl;
    std::chrono::milliseconds sec(1000);
    for (int i = 3; i != 0; --i)
    {
        std::cout << "wait for " << i << " seconds " << std::endl;
        std::this_thread::sleep_for(sec);
    }
    return returnValue;
}

//该类的成员函数将作为 async 的入口函数
class AsyncThreadFuncClass
{
public:
    std::string asyncThreadFunc_2(std::string returnString)
    {
        std::cout << "Sub thread: class member function with id- " << std::this_thread::get_id() << std::endl;
        return returnString;
    }
};

//async的阻塞机制试验线程入口函数
void asyncSleptTest()
{
    std::chrono::milliseconds sec(3000);
    std::this_thread::sleep_for(sec);
}

//延迟执行的线程的入口函数
double deferredThreadFunc_1(double ad)
{
    std::cout << ad;
    double doubleAd = 2 * ad;
    std::cout << " is the value:  ";
    return doubleAd;
}

//异步任务入口函数
int asyncThreadFunc_2()
{
    std::cout << "std::launch::async task id- " << std::this_thread::get_id() << " is running " << std::endl;
    std::chrono::milliseconds sec(2000);
    std::this_thread::sleep_for(sec);
    return 200;
}

//packaged_task 要打包的线程入口函数
double packagedThreadFunc(int a, const double b)
{
    std::cout << "input value: " << a << " and " << b << std::endl;
    double a2double = static_cast<double>(a);
    double aTimesB = a2double * b;
    std::cout << "output value: " << aTimesB << std::endl;
    return aTimesB;
}

//packaged_task 包装该函数后被直接调用
std::string illustrateSelf()
{
    std::cout << std::this_thread::get_id() << std::endl;
    return std::string("The current function is called through a std::packaged_task directly");
}

//promise试验的线程入口函数
void promiseThreadTestFunc_1(std::promise<int>& prms, int val)
{
    val *= 5;
    //将对象存入 promise 中
    prms.set_value(val);
}

//在这个线程入口函数中获取上面这个 promise 保存的值
void promiseGetValueThread(std::future<int>& prmsFuture)
{
    std::cout << "std::promise<int> 存储了 20*5： " << prmsFuture.get() << std::endl;
}



//本节主调函数
void concurrency_learning_part8()
{
    std::cout << "Main thread: " << std::this_thread::get_id() << std::endl;
    //普通函数作为线程入口
    int returnVal = 100;
    std::future<int> threadIntResult = std::async(asyncThreadFunc_1, returnVal);

    //成员函数作为线程入口函数
    AsyncThreadFuncClass atfc;
    std::future<std::string> threadStringResult = std::async(&AsyncThreadFuncClass::asyncThreadFunc_2, &atfc, "Return-String");

    //如果线程没有执行完，get() 就拿不到返回结果，那么 get 就会一直阻塞在这里，直到能获取返回值为止，所以 get() 的结果不一定是能立刻得到的，同时它不能被调用多次，否则会报异常，因为get()返回其实是移动语义
    std::cout << threadIntResult.get() << " is returned by the asynchronous task." << std::endl;   //此处没有把字符串写在get的前面是因为这里get没能立刻得到返回值，如果字符串在前面，会发生字符串和返回值分开打印的结果
    std::cout << threadStringResult.get() << " sub thread exited" << std::endl;
    //future对象还有一个成员函数 wait()，它也等待线程返回，但我们并不能通过它获取返回的值
    std::cout << std::endl;


    /// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //async 创建的异步任务被执行的时机
    auto begin = std::chrono::system_clock::now();
    {
        //如果有对象接收 async 的返回值，当 async 一旦被创建（非deferred模式），异步任务就会执行，就是说在异步策略下，线程入口函数会从任务被创建开始立刻执行，即在此过程中程序会阻塞
        //下列代码总共阻塞3秒，因为它们是在两个线程上一起执行的，而每个异步任务是阻塞3秒
        //但是如果 async 的返回值没有被任何变量接收的话，那么每一行所返回的 future 都会立刻析构
        //由于编译器必须保证异步任务在 future 析构前必须被执行一次，而此时立刻就要析构，所以此处也会执行线程入口函数，于是阻塞立刻发生，阻塞完了，析构完成再执行下一行，那么就会先后阻塞3秒，总共6秒
        //如果 async 被局部对象接收，且 async 是 deferred 策略创建的，那么就依然会阻塞6秒，除非没有任何 wait 或 get 调用，就不会有任何线程创建，直接阻塞0秒
        auto f1 = std::async(std::launch::async, asyncSleptTest);
        auto f2 = std::async(std::launch::async, asyncSleptTest);
        /*f1.wait();
        f2.wait();*/
    }
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
    std::cout << "Slept for " << duration.count() << " seconds" << std::endl;
    std::cout << std::endl;


    /// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //我们可以对 std::async() 传递一个额外的 std::launch 类型参数（这个类型其实是枚举），来达到额外的目的，这个参数表示的是异步任务的创建策略
    // 
    //(1) std::launch::deferred
    //  该策略表示线程入口函数延迟到 wait() 或 get() 调用时才被执行，但是如果 get() 和 wait() 都没有被调用的话，线程的入口函数就根本不会被执行
    std::future<double> threadDoubleDeferred = std::async(std::launch::deferred, deferredThreadFunc_1, 3.14);
    //输出 async 延迟执行的结果。事实上，一旦用了 std::launch::deferred，那么 async 就不会创建一个新线程，也就是说，线程入口函数实际是在主线程中执行的
    std::cout << "double of the input double: " << threadDoubleDeferred.get() << std::endl;
    //
    //(2) std::launch::async
    //  该策略表示立即执行异步任务
    //  与本节最开始不写任何参数的 async 的例子相比，它们之间的区别是，如未明确指定任何创建策略，async 的默认创建策略是 undefined，它是一个基于任务的程序设计，内部有一个调度器(线程池)，会根据实际情况决定采用哪种策略
    std::future<int> asyncThreadIntResult_1 = std::async(std::launch::async, asyncThreadFunc_2);
    std::future<int> asyncThreadIntResult_2 = std::async(std::launch::async, asyncThreadFunc_2);
    std::cout << asyncThreadIntResult_1.get() << " is returned by the std::launch::async task 1." << std::endl;
    std::cout << asyncThreadIntResult_2.get() << " is returned by the std::launch::async task 2." << std::endl;
    std::cout << std::endl;


    /// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //std::packaged_task 是个类模板，它的模板参数是各种可调用对象，它可以将各种可调用对象打包，方便将来作为线程入口函数来调用
    //模板参数中，参数是函数的返回类型与特征标，比如一个foo函数长这样：int foo(double)，那么模板参数中就省略函数名，写上函数的返回类型与形参的类型：int(double)
    std::packaged_task<double(int, const double)> packagedTSK(packagedThreadFunc);
    std::thread threadPkgd(std::ref(packagedTSK), 2, 3.3);  //需要使用move或者ref将packagedTSK包装起来，因为packaged_task无法被复制，只能被移动
                                                            //  而std::ref可以创建行为像引用但可被复制的对象，就是一个reference_wrapper包装器
                                                            //  用了ref之后，此时此处的packaged_task既不会被复制，也不会被移动，因为传进thread的是包装器
                                                            //  此处不使用move的原因是下面还要获取这个对象的future，一旦使用move，它就变成了移后源，不能再使用
    threadPkgd.join();
    //包装好了之后，我们就可以用 future 来获取 packaged_task，并得到它的返回值
    std::future<double> pkgdResult = packagedTSK.get_future();  //使用 get_future() 方法来返回一个future对象
    std::cout << "input value * 2 returns: " << pkgdResult.get() << std::endl;
    std::cout << std::endl;


    /// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //std::packaged_task 将可调用对象包装起来后，也可以直接再被调用
        //调用被 packaged_task 包装起来的 lambda 表达式
    std::packaged_task<void(std::chrono::seconds)> packagedLambda([](std::chrono::seconds sec)
        {
            //std::cout << "wait " << sec << std::endl;   //cpp 20 新特性，可以 cout << std::chrono::seconds，clang 似乎还不能完全支持
            std::this_thread::sleep_for(sec);
        });
    packagedLambda(std::chrono::seconds(2));
    //调用被 packaged_task 包装起来的函数
    std::packaged_task<std::string()> packagedIllustrateSelf(illustrateSelf);
    //可以将包装好的任务存进一个容器，以便后续的调用
    std::vector<std::packaged_task<std::string()>> pkgTasks_vec;
    //使用移动语义将包装好的任务存到vec，因为packaged_task的拷贝构造函数被删除，就是说不允许复制，只能移动
    pkgTasks_vec.push_back(std::move(packagedIllustrateSelf));  //不能使用std::ref的原因是生成的reference_wrapper并不会禁止复制
                                                                //而push_back会将packaged_task复制一份，然而正如上面说的那样，packaged_task禁用了拷贝构造
    //将任务从容器中取出并调用
    std::vector<std::packaged_task<std::string()>>::iterator iter = pkgTasks_vec.begin();
    std::packaged_task<std::string()> pkgHeadTask = std::move(*iter);   //取出第一个元素
    std::future<std::string> futureStr = pkgHeadTask.get_future();
    pkgTasks_vec.erase(iter);   //取出后就将它从容器中删除
    pkgHeadTask();
    std::cout << futureStr.get() << std::endl;
    std::cout << std::endl;


    /// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //std::promise 是个类模板，可用于线程间通讯，我们可以在一个线程中将需要的对象存到promise中，然后在另一个线程中获取它
    //模板参数是 promise 中要保存的对象的类型
    std::promise<int> promiseInt;
    std::thread promiseThread_1(promiseThreadTestFunc_1, std::ref(promiseInt), 20);
    promiseThread_1.join();
    std::future<int> promiseIntFuture = promiseInt.get_future();
    std::thread getPromiseThread(promiseGetValueThread, std::ref(promiseIntFuture));
    getPromiseThread.join();

    std::cout << "Main Thread exited." << std::endl;
}
#include <thread>
#include <future>
#include "header_learning.h"

//线程入口函数1
void pause4someTime()
{
    std::chrono::seconds secs(5);
    std::this_thread::sleep_for(secs);
}

//线程入口函数2
void deferredPause()
{
    std::chrono::seconds secs(3);
    std::this_thread::sleep_for(secs);
}

//线程入口函数3
int returnForSharedFuture()
{
    return 200;
}

//线程入口函数4
int getFuture2Shared()
{
    return 300;
}

//原子操作-------------------------------------------
//std::atomic 是个类模板，用来封装某个类型的值
std::atomic<int> atomicNum(10);
int genNum = 10;
std::mutex mut;

void atomicNumIncrease()
{
    for (int i = 1; i <= 10000000; ++i)
    {
        atomicNum++;
        mut.lock();
        ++genNum;
        mut.unlock();
    }
    return;
}

void atomicNumDecrease()
{
    for (int i = 1; i <= 10000000; ++i)
    {
        atomicNum--;
        mut.lock();
        --genNum;
        mut.unlock();
    }
    return;
}



//本节主调函数
void concurrency_learning_part9()
{
    std::future<void> pauseAction = std::async(std::launch::async, pause4someTime);
    std::cout << "A sub task has begun, waiting for it to finish" << std::endl;
    //std::future_status 是个枚举类型，它表示一个 future 的状态，future.wait_for() 可以等待异步任务运行，等待时长由我们自己传入
    //一旦超过规定时间,异步任务还没结束的话，就会返回 std::future_status::timeout，如果顺利结束，则返回 std::future_status::ready
    std::future_status status = pauseAction.wait_for(std::chrono::seconds(6));
    if (status == std::future_status::timeout)
        std::cout << "Wait for too long!" << std::endl;
    else if (status == std::future_status::ready)
        std::cout << "Asynchronous task execution finished" << std::endl;
    pauseAction.wait();
    std::cout << std::endl;
    /// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 如果将 async 的创建策略改为 deferred，那么 wait_for() 返回的 status 也会变成 std::future_status::deferred
    std::future<void> deferredPauseAction = std::async(std::launch::deferred, deferredPause);
    std::cout << "Deferred pause has been created" << std::endl;
    std::future_status deferredStatus = deferredPauseAction.wait_for(std::chrono::seconds(0));
    if (deferredStatus == std::future_status::deferred)
    {
        std::cout << "The task is deferred, now begin to work." << std::endl;
        deferredPauseAction.wait();
    }
    std::cout << std::endl;
    /// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // shared_future 的能力，就是可以被 get() 多次，因为它不是移动语义，而是复制
    std::future<int> originalFuture = std::async(std::launch::async, returnForSharedFuture);
    std::shared_future<int> sharedFutureInt;
    // future.valid() 可以检查一个future对象中是否拥有有效值，如果里面的数据已经被移动了，那么就没有有效值，就会返回 false
    if (originalFuture.valid())
        /// std::shared_future<int> sharedFutureInt(std::move(originalFuture)); //也可以这么写
        sharedFutureInt = originalFuture.share();   //等同于上面的写法
    std::cout << sharedFutureInt.get() << "\n" << sharedFutureInt.get() + 1 << std::endl;
    if (not originalFuture.valid()) //现在已经没有有效值了
        std::cout << "get() has been called, now there is no valid value." << std::endl;
    std::cout << std::endl;
    /// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //对于 packaged_task 可以直接用 get_future 的返回值来初始化一个 shared_future 对象，因为 get_future() 的返回值并不是 future 对象
    std::packaged_task pkgTask2share(getFuture2Shared);    //cpp 17 新特性 类模板参数类型自动推导，可以不写类型模板参数，clang 好像推不出来函数指针类型
    std::shared_future<int> sharedFutureInt_2(pkgTask2share.get_future());
    pkgTask2share();
    std::cout << sharedFutureInt_2.get() << std::endl;
    std::cout << std::endl;
    /// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    /*-----------------------------------------------------------------------------------------------------------------------------
    在多线程中，我们如果有两个线程同时对某个数据进行操作，我们需要用互斥量来对代码段进行加锁与解锁，通常我们操作的是一系列数据
    而如果是对单一的变量进行操作，比如说赋值，看似只有一行代码，只做了一个动作，事实上在计算机内部也是被分割成了多个小步骤完成的
    那么我们当然也需要对该操作进行保护，以防多线程同时操作造成的不可预料的错误后果，但是如果我们要循环地反复地对这个变量进行赋值，我们就要反复加锁解锁
    事实证明这样做效率很低下，那么无锁并发技术就有了用武之地，原子操作就是其中之一。原子操作是针对单一对象的，它也能防止多线程同时对单一对象操作造成的错误结果
    但是原子操作效率更高，它是一种不可被分割的操作，自然地它也只能保护单一的动作，而不是对一系列代码段进行保护
    -----------------------------------------------------------------------------------------------------------------------------*/
    std::future<void> futureAtomic_1 = std::async(std::launch::async, atomicNumIncrease);
    std::future<void> futureAtomic_2 = std::async(std::launch::async, atomicNumDecrease);
    futureAtomic_1.wait();
    futureAtomic_2.wait();
    //也可以使用thread，要在thread.join之后再使用所操作的对象
    /// std::thread atomicIncreaseThread(atomicNumIncrease);
    /// std::thread atomicDecreaseThread(atomicNumDecrease);
    /// atomicIncreaseThread.join();
    /// atomicDecreaseThread.join();
    std::cout << atomicNum << " and " << genNum << std::endl;   //对于async来说，应该在它返回的future对象调用get或wait方法后再使用所操作的对象，否则异步任务可能会还没执行完，那我们使用的就是错误结果

    std::cout << "All tasks finished" << std::endl;
}
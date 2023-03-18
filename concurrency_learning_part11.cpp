#include "header_learning.h"
#include <chrono>
#include <mutex>
#include <future>

/*--------------------------------------------------------------------------------------------------
常规的mutex并不能满足在解锁之前重复加锁的操作，但是有时候可能确实需要这么做，比如两个不同的函数都有对某个互斥量加锁的操作
而如果某一天其中一个函数需要调用另一个，那就会产生这样的行为，如果要实现这样的需求，可以使用 recursive_mutex
虽然 recursive 意思是递归的，但并不是真的要递归，只是说明这个互斥量支持重复地加锁
--------------------------------------------------------------------------------------------------*/
using namespace std::chrono;

class testObj
{
public:
    testObj()
    {
        std::cout << "testObj created" << std::endl;
    }

    ~testObj()
    {
        std::cout << "testObj released\n" << std::endl;
    }
};

std::recursive_mutex recsvMutex;
void repeatedlyLock_2();
void repeatedlyLock_1()
{
    for (int a = 0; a < 15; a++)
    {
        testObj t;  //这个东西应该会在每次重复加锁之前构造一次，解锁后析构一次
        std::lock_guard<std::recursive_mutex> recsvGuard(recsvMutex);
        std::cout << "扑通 " << a << std::endl;
        repeatedlyLock_2();
    }
}

void repeatedlyLock_2()
{
    std::lock_guard<std::recursive_mutex> recsvGuard(recsvMutex);
    std::cout << "bibibi~ " << std::endl;
}

/*-----------------------------------------------------------
timed_mutex 是个带超时功能的互斥量
-----------------------------------------------------------*/
//可以通过 try_lock_for 等待一段时间，如果超时，再结束阻塞干别的事，如果成功拿到锁，返回true，否则false
std::timed_mutex timedMutex;
void timedMutexTest_1()
{
    for (int i = 0; i < 1000; ++i)
    {
        if (timedMutex.try_lock_for(.2s))
        {
            std::lock_guard<std::timed_mutex> timedGuard(timedMutex, std::adopt_lock);
            std::cout << "mewo" << std::endl;
        }
        else
            std::cout << "Owww!!" << std::endl;
    }
}

void timedMutexTest_2()
{
    for (int i = 0; i < 1000; ++i)
    {
        timedMutex.lock();
        std::lock_guard<std::timed_mutex> timedGuard(timedMutex, std::adopt_lock);
        std::cout << "woof" << std::endl;
    }
}

//可以通过 try_lock_until 不停地尝试加锁，直至到达未来某个时间点
//与 try_lock_for 的不同之处在于如果想要在某个指定的时间停止尝试加锁，只需要输入具体时刻，而不需要去计算从现在开始到达那个时刻，要花费多久
void timedMutexTest_3()
{
    for (int i = 0; i < 50000; ++i)
    {
        timedMutex.lock();
        std::cout << "ping" << std::endl;
        std::this_thread::sleep_for(30ms);
        timedMutex.unlock();
    }
}

void timedMutexTest_4()
{
    for (int i = 0; i < 50000; ++i)
    {
        if (timedMutex.try_lock_until(std::chrono::steady_clock::now() + 1s))
        {
            std::cout << "线程4执行 " << i + 1 << "次 " << std::endl;
            std::cout << "qqq" << std::endl;
            timedMutex.unlock();
        }
        else
            std::cout << "try lock失败 " << std::endl;
    }
}

/*-----------------------------------------------------------
timed_recursive_mutex 是个带超时功能的可递归互斥量
-----------------------------------------------------------*/
std::recursive_timed_mutex recsvTmutex;
void timedMutexTest_6();    //声明
void timedMutexTest_5()
{
    for (int i = 0; i < 100; ++i)
    {
        if (recsvTmutex.try_lock_until(std::chrono::steady_clock::now() + 10ms))
        {
            std::cout << "线程5执行 " << i + 1 << "次 " << std::endl;
            timedMutexTest_6();
            std::cout << "locked recursively" << std::endl;
            recsvTmutex.unlock();
        }
        else
            std::cout << "recursively try lock失败" << std::endl;
    }
}

void timedMutexTest_6()
{
    for (int i = 0; i < 40; ++i)
    {
        recsvTmutex.lock();
        std::cout << "线程6执行" << i + 1 << "次" << std::endl;
        recsvTmutex.unlock();
    }
}



//本节主调函数
void concurrency_learning_part11()
{
    std::future<void> f1 = std::async(std::launch::async, repeatedlyLock_1);
    f1.wait();
    std::cout << std::endl;
    //重复加锁太多次也可能报异常，5次以内应该基本没问题，recursive_mutex 和普通的 mutex 用法上没什么区别
    /// /////////////////////////////////////////////////////////////////////////////////////////

    std::thread tryLockForThread_1(timedMutexTest_1);
    std::thread tryLockForThread_2(timedMutexTest_2);
    tryLockForThread_1.join();
    tryLockForThread_2.join();
    std::cout << std::endl;
    /// /////////////////////////////////////////////////////////////////////////////////////////

    /*std::this_thread::sleep_for(2s);
    std::thread tryLockForThread_3(timedMutexTest_3);
    std::thread tryLockForThread_4(timedMutexTest_4);
    tryLockForThread_3.join();
    tryLockForThread_4.join();
    std::cout << std::endl;*/
    /// /////////////////////////////////////////////////////////////////////////////////////////

    std::this_thread::sleep_for(seconds(2));
    std::thread tryLockForThread_5(timedMutexTest_5);
    std::thread tryLockForThread_6(timedMutexTest_6);
    tryLockForThread_5.join();
    tryLockForThread_6.join();
    std::cout << std::endl;
}
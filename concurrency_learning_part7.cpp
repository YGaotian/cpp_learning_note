#include "header_learning.h"
#include <thread>
#include <mutex>

/*-------------------------------------------------------------------------------------------------------------------------------------------------
条件变量 std::condition_variable 是一个类，需要和互斥量配合使用，它等待一个条件达成
生产者生产数据，没有数据的时候，整个循环流程都停滞着，等有数据被生产出来了，条件就达成了，它就通知消费者前来使用数据，消费者才可以来对数据做处理
这样做就不需要每次循环的时候都判断一下当前是否有数据可用，与不停地循环判断相比，循环一直阻塞到条件变量满足为止再执行更有效率
-------------------------------------------------------------------------------------------------------------------------------------------------*/

//condition variable 测试类
class ThreadConditionVariableTest
{
public:
    void condLockWrite()
    {
        for (int n = 0; n < 10000; ++n)
        {
            //锁住 mutexA
            std::unique_lock<std::mutex> autoMutexA_write(listAMutex);
            //数据写入 listA
            listA.push_back(n);
            //唤醒读取线程，使 wait() 停止阻塞
            condLock.notify_one();
            std::cout << "notified" << std::endl;
            //如果我们有多个线程都需要由同一个条件变量唤醒，我们可以使用 notify_all()，因为 notify_one() 一次只能唤醒一个线程
            //但是如果多个线程用的都是同一个互斥量的话，即使都被唤醒，也会因为要与别的线程竞争互斥量，如果没竞争到的话就要继续卡着
        }
    }

    void condLockRead()
    {
        int n = 10000;
        while(n)
        {
            std::unique_lock<std::mutex> autoMutexA_read(listAMutex);
            //wait 根据第二个参数的返回值判断本行是否堵塞，第二个参数是一个可调用对象，如果它返回false，wait就解锁互斥量，并堵塞在本行，直到其他线程调用 notify_one() 函数唤醒 wait 为止
            //wait 也有不接受第二个参数的版本，它会无条件堵塞
            //一旦 wait 被唤醒，它就会不断地尝试对互斥量加锁，加锁成功后如果第二个参数返回 true 就继续往下执行，如果加锁失败，就依然会卡着，所以其他的线程调用 notify_one() 后要尽快解锁互斥量
            //如果 wait 没有第二个参数，那么唤醒一次后就会直接往下执行，然后新的一次循环中 wait 又会堵塞
            condLock.wait(autoMutexA_read, [this] { //此处的可调用对象是个lambda表达式
                if (!listA.empty())
                    return true;
                else
                    return false;
                });
            //程序来到这时，互斥量一定是锁住的
            //读取 listA
            std::cout << listA.front() << std::endl;
            listA.pop_front();  //扔掉最旧数据
            --n;
        }
        std::cout << listA.empty() << std::endl;
    }

private:
    std::mutex     listAMutex;
    std::list<int> listA;
    //条件变量对象
    std::condition_variable condLock;
};


//本节主调函数
void concurrency_learning_part7()
{
    //按正确顺序锁住多个互斥量后的执行结果
    ThreadConditionVariableTest tcvt;
    std::thread          myThread_cond_1(&ThreadConditionVariableTest::condLockWrite, &tcvt);
    std::thread          myThread_cond_2(&ThreadConditionVariableTest::condLockRead, &tcvt);
    myThread_cond_1.join();
    myThread_cond_2.join();
}

/*----------------------------------------------------------------------------------------------------------------------------
Spurious wakeups，虚假唤醒，意思是一个条件变量在条件不满足的情况下，被唤醒的现象，发生虚假唤醒的情况有很多，当一个线程从等待中醒来，此时条件是满足的，
但是突然另一个线程竞争到了互斥量，将状态改变了，等回到第一个线程中的时候，这个线程等待的条件不再满足，就会发生虚假唤醒，又比如当一个线程调用了 notify_all()
那么所有的条件变量都会被唤醒，但是只有第一个竞争到锁的线程可以更改数据，更改完后，轮到别的线程，条件就不再满足了，这也是虚假唤醒。上面的代码中有效地避免了
虚假唤醒会导致的错误，因为用了一个循环，在循环中条件变量不断地在被唤醒后判断条件是否满足，所以条件变量中的lambda表达式对条件的判断十分重要，同时这个判断
不是仅仅判断一次，而是每次被唤醒都会判断，因此while也很重要，并且在条件变量 wait 之前先加了互斥量，保证了之后程序的执行过程中互斥量一定是锁住的
----------------------------------------------------------------------------------------------------------------------------*/
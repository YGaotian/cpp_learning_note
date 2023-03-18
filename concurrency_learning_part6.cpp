#include "header_learning.h"
#include <mutex>
#include <thread>

class UniqueLockContinue
{
public:
    void uniqueLockWriteTest()
    {
        for (int i = 0; i < 1000; ++i)
        {
            //unique_lock 还有一个标志参数 std::defer_lock，该参数可以让 unique_lock 在实例化的时候不调用 lock()，同时也不需要我们事先手动对互斥量进行 lock
            //我们可以之后再手动调用 unique_lock 的成员方法去锁定互斥量，相当于在目前阶段只是对我们的 mutex 与 unique_lock 对象进行绑定，以便我们直接使用更多的 unique_lock 的成员方法
            std::unique_lock<std::mutex> autoMutex_uniqWrite(mutexA, std::defer_lock);
            //try_lock() 方法可以对 mutex 上锁，如果成功则返回 True，否则返回 False，与 owns_lock() 的不同之处就在于 owns_lock() 不尝试上锁
            if (autoMutex_uniqWrite.try_lock()) //需要注意的是 try_lock 的上锁操作与普通的 lock 不同之处就在于，它如果上锁失败并不阻塞，所以 else 里的 --i 至关重要
            {
                listA.push_back(i);
                std::cout << "push " << i << std::endl;
            }
            else
            {
                --i;    //如果没有 --i，那么循环的总次数就是1000，因为 try_lock 不阻塞，很容易导致 push_back 的条件还没来得及成立，循环就结束了，那么就会导致 write 从未成功写入数据过
                std::cout << "pushing failed" << std::endl;
            }
        }
    }
    void uniqueLockReadTest()
    {
        for (int k = 0; k < 1000; ++k)
        {
            std::unique_lock<std::mutex> autoMutex_uniqRead(mutexA, std::defer_lock);
            autoMutex_uniqRead.lock();
            
            if (!listA.empty())
            {
                std::cout << listA.front() << std::endl;
                listA.pop_front();
            }
            else
            {
                --k;
            }
            //unique_lock 也有 unlock 方法，可以让我们在需要的时候自己手动解锁互斥量，更加灵活
            autoMutex_uniqRead.unlock();
        }
        //release() 方法可以返回 unique_lock 所管理的 mutex 的指针，并断开与 mutex 的联系，如果在互斥量被锁定着的时候这么做，我们就需要用一个 mutex* 来接住指针，再手动调用 unlock()
        //mutex锁住的代码段的多少，就称为锁的粒度，粒度粗就说明锁住的代码段很多，反之粒度就细，粒度越细，代码的执行效率就越高，因为其他线程等待的时间就少，我们应选择合适的粒度

        //我们可以转移 unique_lock 对 mutex 的所有权
        std::mutex mutexTemp;
        std::cout << &mutexTemp << std::endl;
        std::unique_lock<std::mutex> autoMutex_entrust(mutexTemp);
        std::unique_lock<std::mutex> autoMutex_takeOver(std::move(autoMutex_entrust));
        std::cout << autoMutex_takeOver.release() << std::endl;
        mutexTemp.unlock(); //release 之后要手动 unlock
    }

private:
    std::mutex mutexA;
    std::list<int> listA;
};

void concurrency_learning_part6()
{
    UniqueLockContinue ulc;
    std::thread myThread_16(&UniqueLockContinue::uniqueLockWriteTest, &ulc);
    std::thread myThread_17(&UniqueLockContinue::uniqueLockReadTest, &ulc);
    myThread_16.join();
    myThread_17.join();
}
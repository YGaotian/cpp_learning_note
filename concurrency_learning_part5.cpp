#include "header_learning.h"
#include <thread>
#include <mutex>

/*-------------------------------------------------------------------------------------------------------------------------------------------------
lock_guard 效率高，内存占用少，推荐使用，但是我们有一个可以完全代替它的东西，就是 unique_lock
unique_lock 在性能方面不如 lock_guard，但是它更加灵活
-------------------------------------------------------------------------------------------------------------------------------------------------*/

//unique_lock 测试类
class ThreadUniqueLockTest
{
public:
    void multiLockTestWrite()
    {
        for (int n = 0; n < 1000; ++n)
        {
            //锁住 mutexA
            std::unique_lock<std::mutex> autoMutexA_write(listAMutex);
            //数据写入 listA
            listA.push_back(n);
            //锁住 mutexB
            std::unique_lock<std::mutex> autoMutexB_write(listBMutex);
            //数据写入 listB
            listB.push_back(n + 1000);
        }
    }

    void multiLockTestRead()
    {
        for (int s = 0; s < 1000; ++s)
        {
            //锁住 mutexA 和 mutexB
            std::lock(listAMutex, listBMutex);
            ///unique_lock 也可以使用 std::adopt_lock 参数，这个标志参数的意思是 lock() 已经被调用，所以我们必须在之前写好 lock() 的调用代码，后面一样也不用手动 unlock()
            std::unique_lock<std::mutex> autoMutexA_read(listAMutex, std::adopt_lock);
            std::unique_lock<std::mutex> autoMutexB_read(listBMutex, std::adopt_lock);
            //判断列表是否为空，不为空则取出数据并输出
            if (!listA.empty() && !listB.empty())
            {
                //读取 listA
                std::cout << listA.front() << std::endl;
                listA.pop_front();  //扔掉最旧数据
                //读取 listB
                std::cout << listB.front() << std::endl;
                listB.pop_front();  //扔掉最旧数据
            }
            else
            {
                --s;
                std::cout << "--s" << std::endl;
            }
        }
    }
    void doAnythingElse()
    {
        ///由于 read 线程在主调函数中是先创建出来的，所以会先运行，这时如果线程切换到 write 或 doAnythingElse，却因为无法锁上已经被 read 锁住的 mutex，函数就不会继续执行，效率很低
        ///我们可以借助 unique_lock 的灵活性来改善这一现象，std::try_to_lock 标志参数可以用来告诉 unique_lock，我们要尝试去锁一个互斥量
        ///如果成功了，那就正常执行我们的函数，如果这个互斥量已经被其他线程锁住了，那我们也不多等，先执行其他操作
        //如果我们要使用 std::try_to_lock，我们就不应该在这个线程中对互斥量调用 lock()，因为接收了这个标志的 unique_lock 会自己尝试去锁互斥量
        while (!listA.empty())
        {
            std::unique_lock<std::mutex> autoMutexA_else(listAMutex, std::try_to_lock);
            if (autoMutexA_else.owns_lock())
            {
                std::cout << "do something else sucessfully" << std::endl;
            }
            else
            {
                std::cout << "I can't wait, I have to do something to ensure the program running efficiency" << std::endl;
            }
        }
    }

private:
    std::mutex     listAMutex;
    std::mutex     listBMutex;
    std::list<int> listA;
    std::list<int> listB;
};


//本节主调函数
void concurrency_learning_part5()
{
    //按正确顺序锁住多个互斥量后的执行结果
    ThreadUniqueLockTest tult;
    std::thread          myThread_13(&ThreadUniqueLockTest::multiLockTestRead, &tult);
    std::thread          myThread_14(&ThreadUniqueLockTest::multiLockTestWrite, &tult);
    std::thread          myThread_15(&ThreadUniqueLockTest::doAnythingElse, &tult);
    myThread_13.join();
    myThread_14.join();
    myThread_15.join();
}
#include "header_learning.h"
#include <thread>
#include <mutex>

/*-------------------------------------------------------------------------------------------------------------------------------------------------
一般我们对每个对象都分配一个对应的mutex，而不是所有对象都使用同一个mutex
如果现在有两个线程1和2，两个互斥量A和B，线程1中mutexA锁上了，并且在解锁之前需要锁上mutexB，线程2中mutexB锁上了，并且在解锁之前需要锁上mutexA
而此时线程A中将要锁上mutexB的时候，程序调度到了线程2上，线程2先锁上了mutexB，并要锁上mutexA，但这时就发现mutexA已经锁了，所以无法继续往下执行以解锁mutexB
那么回到线程A又发现mutexB无法锁上，所以也就无法解锁mutexA，这时候两个线程就都卡住了，无法继续往下执行，这就是多线程的死锁
那死锁的解决办法就是两个线程中，对mutex进行锁定的顺序应该保持一致，只要线程1中锁mutexA，线程2中也先锁mutexA，等线程1中mutexA解锁，线程2就能锁mutexA了，同时，mutexB也能正常锁住
-------------------------------------------------------------------------------------------------------------------------------------------------*/

//死锁解决方案模型类
class ThreadMultiLockModel
{
public:
    void multiLockTestWrite()
    {
        for (int n = 0; n < 1000; ++n)
        {
            //锁住 mutexA
            std::lock_guard<std::mutex> autoMutexA_write(listAMutex);
            //数据写入 listA
            listA.push_back(n);
            //锁住 mutexB
            std::lock_guard<std::mutex> autoMutexB_write(listBMutex);
            //数据写入 listB
            listB.push_back(n + 1000);
        }
    }

    void multiLockTestRead()
    {
        //我们也可以用函数模板 std::lock() 来一次性锁住多个mutex，这个函数接收至少两个互斥量，它会尝试将接收到的多个互斥量一起锁住
        // 只要其中有一个没能成功锁住，它就会将已经被自己锁住的互斥量都解锁，并一直等待，直到能将所有互斥量都锁住，再继续执行后面的代码
        // 这样就不存在锁定顺序不正确的问题了

        for (int s = 0; s < 1000; ++s)
        { 
            //锁住 mutexA 和 mutexB
            std::lock(listAMutex, listBMutex);
            //但是一旦用了 std::lock，我们还得手动在后面 unlock()，这样就又变得麻烦了
            //为了解决这个问题，我们依然可以使用 std::lock_guard()，只是在使用它的时候，需要再向它传入一个参数 std::adopt_lock
            //该参数可以让 lock_guard 在调用构造函数的时候不执行 mutex.lock()，这样的话就不会重复对一个 mutex 调用 lock()，也依然能自动帮我们 unlock()
            std::lock_guard<std::mutex> autoMutexA_read(listAMutex, std::adopt_lock);
            std::lock_guard<std::mutex> autoMutexB_read(listBMutex, std::adopt_lock);
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
                std::cout << "list empty" << std::endl;
            }
            //由于使用了 std::lock_guard<std::mutex> autoMutex_read(mutex, std::adopt_lock)，所以不用再手动 unlock()
            //listAMutex.unlock();
            //listBMutex.unlock();
        }
    }

private:
    std::mutex     listAMutex;
    std::mutex     listBMutex;
    std::list<int> listA;
    std::list<int> listB;
};


//本节主调函数
void concurrency_learning_part4()
{
    //按正确顺序锁住多个互斥量后的执行结果
    ThreadMultiLockModel tmlm;
    std::thread          myThread_11(&ThreadMultiLockModel::multiLockTestWrite, &tmlm);
    std::thread          myThread_12(&ThreadMultiLockModel::multiLockTestRead, &tmlm);
    myThread_11.join();
    myThread_12.join();
}
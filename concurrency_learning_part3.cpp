#include "header_learning.h"
#include <thread>
#include <mutex>

/*-----------------------------------------------------------------------------------------------------------------------------------------------------
如果要在多线程中读取数据，不会有什么问题，但如果要写入数据，或是一边读一边写，就会出大问题
比如说，两个线程写数据，八个线程一边还在读数据，程序就很可能会崩溃，因为写入数据的过程可能会有很多小步，而线程的调度又是乱序的
  很可能写数据的步骤才执行两步，别的线程就读数据了，然后又回到写数据的线程，如果里面还涉及到指针的操作，就极有可能乱套了，会导致不可预料的结果，最可能发生的情况，就是程序崩溃
  所以我们需要写一些防止崩溃的代码
数据共享时，也可能会有问题，比如有多个线程都要读同一个数据，但同一时间段内这个数据只应该由一个线程获取，如果不加以限制，也会导致混乱的结果
    
我们需要将共享数据的代码锁住，只让一个线程拥有访问权，当这个线程的任务执行完毕，再解锁，让下一个线程访问，并再次锁住，所以我们需要引入一个新概念，互斥量mutex
互斥量是个类对象，可以理解为一把锁，我们要让多个线程一起尝试调用自己的lock成员函数，去锁定这把锁，但只有一个线程的lock函数返回了结果，代表锁定成功，其余的线程则一直卡着，直到自己锁定成功
-----------------------------------------------------------------------------------------------------------------------------------------------------*/

int inputRecord  = 0;
int outputRecord = 0;

//数据列表读写模型类
class ThreadTestWriteReadModel
{
public:
    void listWriteData()
    {
        for (int i = 0; i < 1000; ++i)
        {
            //互斥量的用法：先lock()，在unlock()，它们必须成对使用
            //锁定线程
            m_listMutex.lock();
            //写入数据
            m_dataList.push_back(i);
            ++inputRecord;
            std::cout << "current data input: " << i << std::endl;
            //解锁线程
            m_listMutex.unlock();
        }
    }

    void listReadData()
    {
        
        for (int k = 0; k < 1000; ++k)
        {
            //在实际开发中，很容易漏写unlock()，一旦发生这种情况，程序一定会发生异常，但错误到底在哪里很难排查，所以为了帮助我们写代码，c++也有像智能指针一样方便的工具，帮我们自动unlock
            // 这个功能就是类模板 std::lock_guard<>，一旦使用了lock_guard<>，就直接取代了原本的lock()和unlock()，也就是说我们不用也不能再写lock()和unlock()了
            std::lock_guard<std::mutex> autoMutex(m_listMutex);    //lock_guard<>的工作原理其实就是在这个类模板的构造函数中使用了lock()，在析构函数中使用了unlock()
                                                                        //这样就能保证函数退出一定执行了unlock()
            //读取数据
            if (!m_dataList.empty())
            {
                int data = m_dataList.front();
                std::cout << "current data output: " << data << std::endl;
                m_dataList.pop_front();
                ++outputRecord;
            }
            else
            {
                std::cout << "The data list is currently empty" << std::endl;
                --k;
            }
        }
    }

private:
    std::list<int>   m_dataList;
    std::mutex       m_listMutex;    //互斥量成员
};


//线程函数入口
void myThreadInitialFunc_7(int i)
{
    std::cout << "Thread " << i << " created" << std::endl;
}


//本节主调函数
void concurrency_learning_part3()
{
    std::vector<std::thread> threadVec;
    //创建10个线程，统一使用作为函数入口，但实际上这10个线程是乱序执行的，与操作系统内部对线程的调度机制有关
    for (int i = 0; i < 10; ++i)
        threadVec.push_back(std::thread(myThreadInitialFunc_7, i + 1));
    for (auto iter = threadVec.begin(); iter != threadVec.end(); ++iter)
        iter->join();
    
    //双线程读写数据列表，由于使用了mutex，所以现在运行不会崩溃
    ThreadTestWriteReadModel ttlm;
    std::thread              myThread_9(&ThreadTestWriteReadModel::listWriteData, &ttlm);
    std::thread              myThread_10(&ThreadTestWriteReadModel::listReadData, &ttlm);
    myThread_9.join();
    myThread_10.join();

    std::cout << "input: " << inputRecord << " datas" << std::endl;
    std::cout << "output: " << outputRecord << " datas" << std::endl;
}


#include "header_learning.h"
#include <Windows.h>
#include <mutex>

//在对windows平台进行开发时，我们可以使用windows自己的一种叫做critical section的东西来替代互斥量，这个东西翻译过来叫做临界区
//临界区与互斥量的不同之处在于，这个东西只能在windows平台下使用
//此外，互斥量还可以用于对不同应用程序的不同线程之间的数据操作进行保护加锁，而临界区不行

//我们可以定义一个开关
#define RUN_ON_WINDOWS

//自动析构临界区技术，定义了一个类似于 lock_guard 的类，这样的类称为 RAII（resource acquisition is initialization，资源获取即初始化） 类
class critical_guard
{
public:
    critical_guard() = delete;

    critical_guard(CRITICAL_SECTION* criticalSectionTmp)
    {
        m_critical_section_ptr = criticalSectionTmp;
        EnterCriticalSection(m_critical_section_ptr);
    }

    ~critical_guard()
    {
        LeaveCriticalSection(m_critical_section_ptr);
    }

private:
    CRITICAL_SECTION* m_critical_section_ptr;
};

//数据读写模型类
class DataIOListModel
{
private:
    std::list<int> listA;
    std::mutex     listAMutex;
    #ifdef RUN_ON_WINDOWS
        CRITICAL_SECTION criticalSection_1;    //创建临界区对象
    #endif

public:
    //临界区与互斥量在使用上的不同之处就在于，临界区需要先初始化才能使用，所以我们要写一下类的构造函数，在构造函数中对临界区初始化
    DataIOListModel()
    {
        #ifdef RUN_ON_WINDOWS
            //对临界区对象进行初始化，需要调用windows自己的接口
            InitializeCriticalSection(&criticalSection_1);  //传入的是临界区对象的地址
        #endif  
    }

public:
    void multiLockTestWrite()
    {
        for (int n = 0; n < 10000; ++n)
        {
            #ifdef RUN_ON_WINDOWS
                //临界区保护数据的方法和互斥量很像，但不叫加锁与解锁，而称为进入临界区与离开临界区
                EnterCriticalSection(&criticalSection_1);
                EnterCriticalSection(&criticalSection_1);   //同一个线程中，临界区可以重复进入
                listA.push_back(n);
                LeaveCriticalSection(&criticalSection_1);
                LeaveCriticalSection(&criticalSection_1);   //一旦重复进入了临界区，那么离开临界区时也要离开同样的次数
            #else
                //锁住 mutexA
                std::lock_guard<std::mutex> autoMutexA_write(listAMutex);
                //数据写入 listA
                listA.push_back(n);
            #endif
        }
    }

    void multiLockTestRead()
    {
        for (int s = 0; s < 10000; ++s)
        {
            #ifdef RUN_ON_WINDOWS
                //自动析构临界区，使用的时候不要忘记，需要实例化一个自定义类 critical_guard 的实例对象
                critical_guard sectionGuard(&criticalSection_1);
                if (!listA.empty())
                {
                    //读取 listA
                    std::cout << listA.front() << std::endl;
                    listA.pop_front();  //扔掉最旧数据
                }
                else
                {
                    --s;
                    std::cout << "list empty" << std::endl;
                }
            #else
                //锁住 mutexA
                listAMutex.lock();
                //但是一旦用了 lock，我们还得手动在后面 unlock()，这样就又变得麻烦了
                //为了解决这个问题，我们依然可以使用 std::lock_guard()，只是在使用它的时候，需要再向它传入一个参数 std::adopt_lock
                //该参数可以让 lock_guard 在调用构造函数的时候不执行 mutex.lock()，这样的话就不会重复对一个 mutex 调用 lock()，也依然能自动帮我们 unlock()
                std::lock_guard<std::mutex> autoMutexA_read(listAMutex, std::adopt_lock);
                if (!listA.empty())
                {
                    //读取 listA
                    std::cout << listA.front() << std::endl;
                    listA.pop_front();  //扔掉最旧数据
                }
                else
                {
                    --s;
                    std::cout << "list empty" << std::endl;
                }
                //由于使用了 std::lock_guard<std::mutex> autoMutex_read(mutex, std::adopt_lock)，所以不用再手动 unlock()
                //listAMutex.unlock();
            #endif
        }
    }
};



//本节主调函数
void critical_section_learning()
{
    DataIOListModel diolm_1;
    std::thread criticalSectionTestThread_1(&DataIOListModel::multiLockTestWrite, &diolm_1);
    std::thread criticalSectionTestThread_2(&DataIOListModel::multiLockTestRead, &diolm_1);
    criticalSectionTestThread_1.join();
    criticalSectionTestThread_2.join();
}
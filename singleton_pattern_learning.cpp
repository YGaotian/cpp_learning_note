#include "header_learning.h"
#include <thread>
#include <mutex>


class SingletonClass
{
public:
    //要写 static 的原因是在创建类实例的时候需要通过 SingletonClass::getInst() 的方法来调用类成员函数
    //如果是普通类成员函数的话必须要写 特定类实例.成员函数() 才能调用以创建类实例，但这样就不是单例了
    static SingletonClass* getInst()
    {
        if (m_singleInst == nullptr)
        {
            m_singleInst = new SingletonClass;
            //一个静态类成员，用于在被析构时释放new出来的单例对象的内存，由于是静态成员对象，所以生命周期是整个程序运行周期，只有程序退出时才会被析构
            static ReleaseClass cleaner;
        }
        return m_singleInst;
    }
    //有参重载
    static SingletonClass* getInst(int n)
    {
        if (m_singleInst == nullptr)
        {
            m_singleInst = new SingletonClass(n);
            static ReleaseClass cleaner;
        }
        return m_singleInst;
    }

public:
    //释放实例指针内存类
    class ReleaseClass
    {
    public:
        ~ReleaseClass()
        {
            //确保new出来的单例类的匿名实例会被释放
            //我们要手动实现释放资源的操作是因为，如果我们需要在单例类实例被释放的时候，对外部资源进行释放，或者比如要保存并关闭外部的文件
            //靠程序退出系统自动帮我们回收资源清理垃圾的做法是无法实现我们的需求的，所以我们在这里可以自己手动实现我们想要的操作
            if (SingletonClass::m_singleInst)
            {
                delete m_singleInst;
                m_singleInst = nullptr;
                std::cout << "destructed" << std::endl;
            }
        }
    };

private:
    SingletonClass()
    {
        m_singleInt = 0;
    }
    SingletonClass(int n) : m_singleInt(n) {}

public:
    int m_singleInt;

private:
    static SingletonClass* m_singleInst;
};

//初始化自身实例指针
SingletonClass* SingletonClass::m_singleInst = nullptr;

void singleThreadSingleton()
{
    SingletonClass* sc_1 = SingletonClass::getInst(3);
    SingletonClass* sc_2 = SingletonClass::getInst();
    std::cout << sc_1 << std::endl;
    std::cout << sc_2 << std::endl;
    std::cout << "para: " << sc_2->m_singleInt << std::endl;
}



/*-----------------------------------------------------------------------------------------------------------
上面的代码中因为我们是单线程，并且只读，所以没有什么问题，如果我们要多线程操作，可能会引发问题
比如我有两个线程，这两个线程中都要调用 SingletonClass::getInst() 函数，不注意的话可能会觉得没什么问题
但如果程序执行到判断的时候发现 m_singleInst 是 nullptr 之后，还没来得及创建 SingletonClass 实例，就跳到另一个线程上了
这时候程序继续执行到判断，发现 m_singleInst 依然是 nullptr, 那么这时候就会创建 SingletonClass 实例，如果这时候又跳回之前的线程
就会继续创建 SingletonClass 实例，这样的话本应是单例的对象就变成了多个，所以我们需要对创建单例对象的操作加“保护锁”
-----------------------------------------------------------------------------------------------------------*/

class MultiThread_Singleton
{
public:
    //实例对象创建函数
    static void createInst()
    {
        m_multiThreadSingleInst = new MultiThread_Singleton;
        static MultiThread_ReleaseClass cleaner;    //自动回收单例实例对象的类的实例，因为是静态的，所以生命周期是整个程序运行周期
    }

    /*---------------------------------------以下两种方法都能保证多线程操作的时候不会重复创建单例实例对象---------------------------------------*/
    //方法一
    //  单例实例化函数，使用互斥量和双重锁定来手动保护单例模式的版本
    static MultiThread_Singleton* getInst()
    {
        if (m_multiThreadSingleInst == nullptr) //两次判断指针是否为空的操作称为双重锁定，是为了防止每次调用 getInst() 都创建一个互斥量，以提高运行效率
        {   
            std::unique_lock<std::mutex> autoMutex_singleton(constructorLock_mutex);    //防止因线程跳转导致的对单例对象实例的多次创建
            if (m_multiThreadSingleInst == nullptr)
            {
                createInst();
            }
        }
        return m_multiThreadSingleInst;
    }

    //方法二
    //  单例实例化函数，使用 std::call_once() 函数模板和一个 std::once_flag 结构类型的标记来自动保护单例模式的版本，call_once() 能保证一个函数只被调用一次
    static MultiThread_Singleton* returnInst()
    {
        std::call_once(CALL_ONCE_FLAG, createInst); //std::call_once() 第一个参数是 once_flag 标记，用来记录想调用的函数是否被调用过，第二个参数是要调用的函数名
        return m_multiThreadSingleInst;
    }
    /*------------------------------------------------------------------------------------------------------------------------------*/

public:
    //释放实例指针内存类
    class MultiThread_ReleaseClass
    {
    public:
        ~MultiThread_ReleaseClass()
        {
            if (MultiThread_Singleton::m_multiThreadSingleInst)
            {
                delete m_multiThreadSingleInst;
                m_multiThreadSingleInst = nullptr;
                std::cout << "multiThread_destructed" << std::endl;
            }
        }
    };

private:
    MultiThread_Singleton()
    {
        std::cout << "More than one thread is trying to construct a singleton instance, but only one will succeed" << std::endl;
    }

private:
    static std::mutex constructorLock_mutex;   //互斥锁
    static std::once_flag CALL_ONCE_FLAG;   //给 std::call_once() 用的 std::once_flag 标记
    static MultiThread_Singleton* m_multiThreadSingleInst;  //单例实例指针
};

//初始化自身实例指针
MultiThread_Singleton* MultiThread_Singleton::m_multiThreadSingleInst = nullptr;
//静态类成员互斥量的定义，并不是声明，声明在类内部，因为静态成员不能在类中定义，所以定义写在外面
std::mutex MultiThread_Singleton::constructorLock_mutex;
//静态类成员标记的定义，并非声明
std::once_flag MultiThread_Singleton::CALL_ONCE_FLAG;

//线程入口函数
void constructSingleton()
{
    //通过调用手动保护单例创建过程的函数来创建实例
    ///MultiThread_Singleton* mts_1 = MultiThread_Singleton::getInst();
    //通过调用自动保护单例创建过程的函数来创建实例
    MultiThread_Singleton* mts_2 = MultiThread_Singleton::returnInst();
}

void multiThreadConstructSingleton()
{
    //两个线程，一起调用构建单例对象实例的函数
    std::thread singletonCreateThread_1(constructSingleton);
    std::thread singletonCreateThread_2(constructSingleton);
    singletonCreateThread_1.join();
    singletonCreateThread_2.join();
}


//本节主调函数
void singleton_pattern_learning()
{
    singleThreadSingleton();
    //由于加了保护锁，所以不会允许创建多个单例对象实例的情况发生
    multiThreadConstructSingleton();
}
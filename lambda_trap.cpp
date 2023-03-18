#include "header_learning.h"
#include <functional>

class LambdaTrapTest
{
public:
    LambdaTrapTest(int a) : mTest(a)
    {
        std::cout << "LambdaTrapTest created" << std::endl;
    }
    ~LambdaTrapTest()
    {
        mTest = 0;
        std::cout << "LambdaTrapTest destoryed" << std::endl;
    }

public:
    int mTest;
};

namespace LAMBDA_TRAP
{
    std::vector<std::function<void(int)>> Fvec;

    void trigger_trap()
    {
        LambdaTrapTest ltt(323);
        LambdaTrapTest* lttp = &ltt;
        Fvec.push_back([&](int c)
        {
            lttp->mTest += c;
            std::cout << ltt.mTest << std::endl;
        });
    }

    class LambdaInClass
    {
    public:
        void trap()
        {
            Fvec.push_back([=](int c) mutable
            {
                member += c;
                std::cout << member << std::endl;
            });
        }

        void trapSolved()
        {
            auto memberCopy = member;
            Fvec.push_back([=](int t) mutable
            {
                memberCopy += t;
                std::cout << memberCopy << std::endl;
            });
        }

        void lambdaWithStaticLocalVar()
        {
            Fvec.push_back([](int u)
            {
                    std::cout << smember << std::endl;
            });
            smember++;
        }

    public:
        int member = 90;
        static int smember;
    };

    int LambdaInClass::smember = 50;
}



void lambda_additional_analysis()
{
    using namespace LAMBDA_TRAP;
    trigger_trap();
    //由于ltt是在trigger_trap函数中定义的局部对象，所以上一行代码运行完之后，ltt就已经被释放了，相应的ltt.mTest也应该被释放了，所以就不应该再被使用了
    //然而lambda表达式捕获的却是ltt的引用，也就是说，下一行代码对一个已经被释放了的内存赋了值，这会产生难以预料的后果
    Fvec[0](28);

    //lambda表达式的形参列表可以用auto来自动推断形参类型，也只有lambda表达式允许这种写法，这是从c++14开始的新写法

    LambdaInClass* lic = new LambdaInClass();
    lic->trap();
    delete lic;
    //尽管我们在类成员函数的lambda中使用了=，希望按值捕获并使用类成员member的副本，但是在实际调用时却发现打印出来的member依然是乱码，也就是说这里的member随着成员函数trap的结束而销毁了
    Fvec[1](8);
    //lambda表达式捕获变量的这一概念，是只针对于在定义lambda表达式的作用域内可见的、非静态的局部变量（包括形参）的，而member是类成员变量，并不属于非静态局部变量
    //成员变量实际上是不能也不是被捕获到的，捕获列表中写一个 = 等价于写一个 this，这种写法的真正含义其实是，按值捕获类的this指针，因此与写 this 没有差别，那在lambda内部使用的成员对象自然不是副本

    //解决方法就是在lambda表达式定义之前创建一个成员函数内的成员对象副本，这样的话在lambda表达式中按值捕获副本即可，就不会因为成员对象随着类实例销毁而变得无法使用
    LambdaInClass* lic2 = new LambdaInClass();
    lic2->trapSolved();
    delete lic2;
    Fvec[2](666);

    //generalized lambda capture，广义lambda捕获，c++14新特性，也可以用来解决上面的捕捉类成员的问题，就是将捕获列表里的 = 改成类似给一个临时变量赋值的语句，相当于将创建副本的步骤集成进了捕获列表
    ///lambda表达式需要这么写：[tempValue = member](int k) { tempValue += k; std::cout << tempValue << std::endl; }

    //在前面我们讲到，lambda表达式是不捕获静态局部变量的，但是在lambda_learning.cpp一节我们也说过，静态局部变量是可以在lambda中使用的，它存储在静态存储区，生命周期一直持续到程序结束
    //因此，我们在lambda表达式中如果使用了静态局部变量，那我们用的就是它本身，而不是副本，同时，由于它不是被lambda表达式捕获的，所以lambda中得到的静态局部变量的值是lambda调用时的值
    LambdaInClass* lic3 = new LambdaInClass();
    lic3->lambdaWithStaticLocalVar();
    delete lic3;
    Fvec[3](20);    //结果是51
    
}
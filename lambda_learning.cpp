#include "header_learning.h"

class TestType4Lambda
{
public:
    TestType4Lambda() = default;
    TestType4Lambda(const TestType4Lambda&)
    {
        std::cout << "copy" << std::endl;
    }
    TestType4Lambda(const TestType4Lambda&&) = delete;

public:
    int m = 4;
};

class WhateverExampleClass
{
protected:
    int whatever = 10000;

public:
    void whateverFunc()
    {
        auto whateverLambda = [this]
        {
            ++whatever;
        };
        whateverLambda();
        std::cout << whatever << std::endl;
    }

    void whateverFunc_2(int y)
    {
        auto whateverLambda = [this, y]
        {
            std::cout << y << std::endl;
            std::cout << whatever << std::endl;
        };
        whateverLambda();
    }

    void whateverFunc_3(int x)
    {
        int a = 3, b = 4, c = 7;
        auto lambda = [=, &x]
        {
            //a++;  报错，a是按值捕获的
            x++;
            std::cout << a << b << c << x << std::endl;
        };
        lambda();
    }
};

//lambda表达式用来定义一个匿名函数，且可以捕获一定范围内的变量，与普通函数不同的是，lambda可以定义在函数体内部
void lambda_learning()
{
    //定义一个lambda表达式，开头必须要有一对方括号，称为捕获列表，后面是圆括号，圆括号是用来接受形参的，再之后是后置返回类型，最后是花括号，里面写上函数体，范例如下
    auto lmd = [](int a = 777) -> int
    {
        a += 1;
        return a;
    };  //注意要有分号结尾
    //调用方式就像普通的函数调用一样
    std::cout << lmd(235) << lmd() << std::endl;
    //如果一个lambda没有参数，参数列表(xxx)就可以省略不写。如果返回类型比较简单，那可以不写后置返回类型，编译器会自动推断，也就是说如下这种写法也是合法的lambda表达式
    auto lambdaBrief = [] { return "hello"; };
    std::cout << lambdaBrief() << std::endl;


    //捕获列表是lambda用来捕获一定范围内的变量的，范围是什么呢？
    //在此，先在函数内定义一个局部变量和一个静态变量
    int localVariable = 10;
    static int staticVariable = 20;

    //捕获列表[]为空的lambda无法返回定义在相同函数内的局部变量，其实就是说捕获列表为空就是不捕获当前作用域内的任何变量，静态变量除外，当前作用域之外的变量是可以捕获到的
    auto captureListLambda_1 = []
    {
        ///return localVariable;  //报错
        return staticVariable;    //正常
    };

    //捕获列表中有个取址符，像这样：[&]，就是捕获当前及外部作用域内的所有变量，并按引用传递至lambda函数体内部使用，这里的外部作用域不包括外部作用域内的另一个函数或子作用域中定义的变量，后同
    auto captureListLambda_2 = [&]
    {
        std::cout << localVariable << std::endl;
        localVariable++;
    };
    captureListLambda_2();
    std::cout << localVariable << std::endl;

    TestType4Lambda tt4l;
    //捕获列表中有个等号，像这样：[=]，就是捕获当前及外部作用域内的所有变量，并按值传递，生成副本在lambda函数体中使用，也就是说只能读取变量的值，但是不能修改它
    auto captureListLambda_3 = [=]
    {
        std::cout << localVariable << std::endl;
        ///return ++localVariable;   //报错，这里的localVariable不是可修改的左值，其实是个const int
        std::cout << tt4l.m << std::endl;   //确实发生了拷贝，即生成了副本
    };
    captureListLambda_3();

    //捕获列表中是this：[this]一般用于类中，表示该lambda拥有与类成员函数相同的访问权限，如果使用了[=]或[&]，则默认就拥有[this]的能力，说白了[this]就是让lambda可以使用当前类的所有成员函数和成员变量
    WhateverExampleClass wec;
    wec.whateverFunc();

    //捕获列表中是一个或多个用逗号分隔的变量名：[arg1, arg2, arg3]，就是按值捕获这些变量，并且不捕获其他变量。如果需要按引用捕获，可以这么做：[&arg]
    //光有一个this只是能捕获类的成员而已，它并不能使lambda可以捕获到lambda所在的成员函数中的变量，因为成员函数中的变量并不是类的成员
    //因此可以在lambda的捕获列表中写上成员函数内定义的变量名或者成员函数的形参名，那为什么不用=或&呢，因为这么做就会捕获所有的变量，如果变量比较多，这么做会产生大量的开销
    wec.whateverFunc_2(777);

    //捕获列表中用等号开头，后面接&xxx：[=, &argA]表示按引用捕获argA，并按值捕获其余所有变量。捕获列表中开头的位置表示的是默认的捕获方式
    wec.whateverFunc_3(678);

    //还有一种是开头用引用，之后的是变量名：[&, argName1, argName2]，显然是默认按引用捕获所有变量，除了argName1和argName2是按值捕获的

    //lambda表达式在定义的时候就已经开始捕获变量了，因此如果定义了一个按值捕获变量的lambda表达式，在定义完成后没有立即调用，而是先改变了变量的值的话，调用lambda时所使用的依然是变量原先的值
    {
        int xVar = 909;
        auto lambdaXVar = [=]   //当程序跑到这一行时，就已经捕获了变量，而不是等到lambda调用时才捕获
        {
            std::cout << "xVar = " << xVar << std::endl;
        };
        xVar++;
        lambdaXVar();   //打印结果为xVar = 909，不是910
        std::cout << "The actual value of xVar is " << xVar << std::endl;
    }

    //上面说过，按值捕获变量得到的其实是个const副本，而我们以前学过mutable关键字，它使得被修饰的变量可以在常函数中被重新赋值，常量对象的成员变量如果也是用mutable修饰的，也仍然可以被重新赋值
    //在lambda表达式中，我们也可以使用mutable，这样就可以在lambda的函数体中修改按值捕获的变量
    {
        int yVar = 999;
        auto lambdaYVar = [=]() mutable    //因为要写mutable，所以即使这个lambda不需要任何参数，也要把括号写上，mutable必须写在参数列表括号的后面，函数体花括号的前面
        {
            yVar = 90909;
            std::cout << "yVar is " << yVar << std::endl;
        };
        lambdaYVar();
    }

    //不捕获任何变量的lambda表达式可以转换为一个函数指针，注意，捕获列表不为空的lambda不行
    using intFuncPtr = int(*)();
    intFuncPtr lambdaFP = []
    {
        return 666;
    };
    std::cout << lambdaFP() << std::endl;
}


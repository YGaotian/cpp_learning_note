#include "header_learning.h"
#include <functional>

class Functor4Save
{
public:
    Functor4Save()
    {
        m_intl = 999;
    }
    Functor4Save(int l)
    {
        m_intl = l;
    }
    void operator()(int i)
    {
        std::cout << i + m_intl << std::endl;
    }

public:
    int m_intl;
};

void printOrigin(int a)
{
    std::cout << a << std::endl;
}

void printSth(int)
{
    std::cout << "An integer is received" << std::endl;
}

void printSth(std::string)
{
    std::cout << "A string is received" << std::endl;
}

void stlFunction_learning()
{
    Functor4Save f4s1(21);
    Functor4Save f4s2(35);
    std::map<std::string, Functor4Save> functorMap;
    functorMap.insert({ "functor1", f4s1 });
    functorMap.insert({ "functor2", f4s2 });
    functorMap["functor"](55);  //给了一个不存在的键，调用了默认构造函数，然后执行了默认的仿函数实例对象
    functorMap["functor1"](10);
    functorMap.at("functor2")(30);
    //以上的代码表明了map可以将函数对象，也就是仿函数存起来，只需要将仿函数的类型作为键值对中的值即可接受函数对象
    //而在调用时，根据下标运算符或是at()中的键调用相对应的仿函数，如果给了map一个并不存在的键，那么会调用默认构造函数，构造一个默认的仿函数对象，然后进行调用
    //所以默认构造函数很重要，是一定要有的，如果没有为仿函数创建默认构造函数，也没有合成的默认构造函数，那么将它们存入map就会报错
    //我们也可以给map一个不存在的键，并为它赋值，这样的行为就可以代替用insert方法
    functorMap["functor3"] = Functor4Save(100);
    functorMap["functor3"](80);
    std::cout << std::endl;

    //如果想将一个void(int)类型的函数的指针存入这个map，我们的键值对中的值应该写void(*)(int)
    //而上述的仿函数其实也是无返回值且接受一个int参数的，但我们却无法直接将它存入这个函数指针map，因为仿函数毕竟与函数指针类型不同
    std::map<std::string, void(*)(int)> functionMap;
    functionMap["function"] = printOrigin;
    functionMap["function"](123);
    Functor4Save f4s3(64);
    ///functionMap.insert({ "functor", f4s3 });    //无法这么做，会报错
    //如果要实现这样的目的，我们可以借助类模板std::function来将我们的仿函数包装成一个function类型，这个类模板定义在头文件functional中
    //类模板参数是我们所希望包装成为的 函数的 类型，或者说返回值类型与特征标，和packaged_task的类模板参数一样
    //比如说这里的仿函数是一个无返回值且接受一个int参数的对象，那么我们就想把它包装成一个无返回值且接收一个int参数的function类对象
    std::function<void(int)> f4s_Function = f4s3;
    //std::function不仅可以接收仿函数，还可以接收函数指针
    std::function<void(int)> printOrigin_Function = printOrigin;
    //上面两个包装好的function对象都可以像函数一样直接调用
    f4s_Function(300);
    printOrigin_Function(212121);

    //这样的话我们就可以直接将std::function<void(int)>作为键值对中的值来创建一个map，这个map将能够同时存储仿函数和函数指针
    std::map<std::string, std::function<void(int)>> callableMap;
    //下一行代码演示了另一种生成键值对的方法，就是通过map的value_type来生成合适的pair对象，无需手动指定想要生成的pair的键值对类型
    //如果想生成string-function类型的pair，只需要将实际的string对象和function对象实例作为参数传入value_type即可，事实上这种方法要写的代码还是有点多的，感觉没必要
    callableMap.insert(std::map<std::string, std::function<void(int)>>::value_type("functor", f4s_Function));
    callableMap["function"] = printOrigin_Function;

    //通过map调用函数和仿函数
    callableMap["functor"](500);
    callableMap.at("function")(777);

    //但是如果一个函数有重载版本，那就会导致无法将它用function模板包装起来，这可能是由于模板内部的处理机制导致了二义性问题的产生
    ///std::function<void(int)> printSth_Function = printSth;   //报错
    //解决方法是用函数指针指向这个函数，然后将函数指针包装起来
    void (*printSthVI_ptr)(int) = printSth;
    std::function<void(int)> printSth_Function = printSthVI_ptr;
    printSth_Function(1);
}
/*--------------------------------------------------------------------------------------------------------------------------
异常处理使用try尝试执行操作，如果遇到错误则使用throw抛出异常，抛出异常后使用catch来捕获异常并处理异常
throw后面需要写一个想抛出的异常对象，异常是个类对象，需要初始化，对于runtime_error来说，需要使用一个string或C风格字符串去初始化它
catch像个函数调用，它要接住抛出来的异常，所以需要圆括号，括号中要写上希望接受的异常形参，就像这样：catch(runtime_error errobj)
c++标准库提供的几个异常类分别定义在4个头文件中: stdexcept（含有runtime_error等）
                                          exception（含有最通用的异常类exception，只报告异常发生，不提供其他信息）
                                          new（含有bad_alloc）
                                          type_info（含有bad_cast）
--------------------------------------------------------------------------------------------------------------------------*/

#include <stdexcept>
#include "header_learning.h"

bool isZero(int& i)
{
    try
    {
        if (i + 1 != 1)
        {
            throw std::runtime_error("The input is not zero!");    //对于runtime_error以外的异常类来说，可能并不使用字符串来初始化
                                                                   //比如exception，bad_alloc，bad_cast只能被默认初始化，不能指定初始值
                                                                   //但是对于其他异常类来说则相反，必须使用字符串来初始化，不能默认初始化
        }
        else
        {
            std::cout << "The input is zero" << std::endl;
            return true;
        }
    }
    catch(const std::runtime_error& err)    //const和&似乎是可选的
    {
        std::cout <<err.what() << "\nMake input be zero? Y/N: ";    //每个标准库异常类都定义了一个名为what的成员函数，runtime_error的what函数用于返回关于异常的文本信息，即初始化时传入的字符串
                                                                    //对于没有提供初始值的异常类来说，what返回的内容由编译器决定
        char r;
        std::cin >> r;
        if (r == 'Y' or r == 'y')
        {
            i = 0;
            return true;
        }
        else
            return false;
    }
}

int divideAB(int a, int b)
{
    try
    {
        if (b == 0)
            throw std::runtime_error("arg 2 is 0!");
        return a / b;
    }
    catch (std::exception err)  //std::exception是许多标准库异常类型（包括runtime_error）的父类，所以可以接收std::runtime_error，但runtime_error会被切掉一部分，捕获到的只有继承于基类的部分
                                //但如果这里的err是引用类型，则由于runtime_error是exception的子类，所以子类会绑定到基类上（详见virtual_in_class.cpp一节）
                                //也就是说发生了派生类向基类的隐式类型转换，子类不会被切掉一部分
    {
        std::cout << err.what() << std::endl;
    }
    catch (std::runtime_error err)  //这个catch与上一个catch都是匹配try中的throw的，但是只有第一个匹配的catch会被执行，所以匹配不代表最佳匹配，以后写代码应该将最佳匹配放在前面
    {
        std::cout << err.what() << " --runtime_error" << std::endl;
    }
    catch (...)    //接受所有异常
    {
        std::cout << "Unidentified exception" << std::endl;
    }
}
//栈解旋|栈展开：检查与当前try块对应的catch子句，如果没找到，则向外层的函数或外层的try寻找对应的catch子句的过程叫栈展开，在这个过程中，所有在栈上的资源都会被释放，称为栈解旋，英文都是stack unwinding
//在上述过程中，如果找到了对应的catch，则使用这个catch处理异常，否则一直向外逐层寻找，如果一直找不到，最终就会调用标准库的terminate函数终止程序，这样是不安全的

//由于在栈展开地过程中，栈上的资源都会被释放，也就是说析构函数一定会被调用，所以我们应该使用类来控制资源的分配，并且析构函数不应该抛出自己无法处理的异常
//因为栈展开的过程就会调用析构函数，如果析构函数无法处理自己的异常，最终程序会调用terminate，因此，如果析构函数要执行某个可能抛出异常的操作，则这些操作应该放在一个try里，并在析构函数内部得到处理

//不要throw一个数组或者函数，因为这实际上是在throw一个指针，而指向局部对象的指针被抛出后，局部对象会在程序推出当前语句块时自动销毁，这时抛出的指针将成为野指针
//因此如果抛出一个指针是必须的，那么抛出指针要求在任何对应的处理代码存在的地方，指针所指的对象都必须存在


class BeThrown
{
public:
    BeThrown() = default;
    BeThrown(const BeThrown& b)
    {
        std::cout << "copy" << std::endl;
    }
};

//throw后面不写明异常对象的两种情况
void throwInCatch(int a)
{
    try
    {
        if (a != 10 && a != 50)
            throw std::string("It's not 10! ");
        else if (a == 50)
            throw;          //如果这里没有写明任何类型的异常而仅仅只是throw，那么就会抛出任何catch都捕获不到的异常，即使是catch(...)也不行，这样就会直接导致程序调用终止函数
        else
        {
            std::cout << "It's 10." << std::endl;
            throw BeThrown();
        }
    }
    catch (std::string& str)
    {
        std::cout << str << "Why not make it be 10?" << std::endl;
        throw;  //在一个catch语句块中，也可以再次throw，如果我们希望即使处理了异常，也让外层知道异常发生，就可以在一个catch中再次throw
                //这里因为已经捕获到异常了，所以直接写throw就可以将此处的异常原封不动地继续向外传递，这样的空throw语句只能出现在catch和catch语句直接或间接调用的函数之内，否则会导致terminate的调用
                //注意，不管捕获形参是什么类型，此处的空throw向外抛出的都是上一个throw抛来的异常对象，就是说若此处的捕获形参不是引用类型而是普通类型，那么在catch中对异常对象做的任何修改都是在改动副本
                //而副本是不会被throw到外侧的，因此如果希望在catch中为异常对象做修改并向外抛出改动过的对象，就应该将捕获形参的类型改为引用
    }
    catch (std::exception& err)
    {
        std::cout << err.what() << std::endl;
    }
    catch (BeThrown)    //如果在一个catch中无需使用抛出的异常对象的话，圆括号中可以不写捕获形参的名字，只要写上需要捕获的类型即可，这样的话就不会发生任何对象拷贝
                        //catch的捕获类型也可以是左值引用，但不能是右值引用，且必须是完全类型，也就是已经完成定义的类型，只有声明没有定义的类型称为不完全类型，因为尚不清楚这个类型包含哪些成员
    {
        std::cout << "!!!" << std::endl;
    }
    catch (...)
    {
        std::cout << "unidentified exception" << std::endl;
    }
}

int constructMember(int a)
{
    if (a == 0)
        throw std::string("0 is unacceptable.");
    return a;
}

//函数测试块演示类
class FunctionTryBlock                                          //异常经常发生在构造对象的时候，对于构造函数来说，在进入自己的函数体之前会先执行构造函数初始化列表，此时函数体还未生效
{                                                               //因此如果try在函数体内，那么函数体内的try和catch语句就也都未生效，如果此时初始化列表抛出了异常，就无法被函数体内的catch处理了
public:                                                         //但我们可以使用函数测试块（函数try语句块），这样的话我们就可以写出既能处理函数体，也能处理构造函数初始化列表的catch了
    FunctionTryBlock() = default;                               //写法是这样的：try写在构造函数的形参列表后面，初始化列表的冒号前面，然后catch写在函数体花括号之后
    FunctionTryBlock(int i) try : mi(constructMember(i))
    {
        //构造函数的函数体
    }
    catch (const std::string& err)                      //对于构造函数try块来说，所有从属的catch都必须以抛异常终止，如果没有这么做，就会隐式地自动以 throw; 来重抛，所以在外层必须再次catch一次
    {                                                   //构造函数的try块对应的catch中不允许return，但析构函数的try块对应的catch中允许使用return，且catch的尾部也会自动以 throw; 重抛
        std::cout << err << std::endl;                  //对于其他所有函数，如果返回值为void（可有cv限定符），则catch末尾等同于 return; 否则行为未定义
    }                                                   ///函数try块主要用于构造函数，是为了处理构造函数初始化列表的异常，其他的函数很少需要使用函数测试块

public:
    int mi;
};

//异常说明符noexcept可以告诉编译器一个函数不会抛出异常，但如果这个函数依然含有throw语句，编译是可以通过的，那在运行时如果这个函数抛出了异常，程序就会调用terminate终止运行，以确保遵守noexcept
//noexcept接受一个可选的bool形参，noexcept(true)表示不抛出异常，noexcept(false)表示可能抛出异常
//noexcept还可以用作运算符，用于确定给定的表达式是否会抛出异常，假设函数afunc使用了noexcept，那么noexcept(afunc())返回true，表示afunc函数不抛出异常，否则返回false。noexcept运算符不会求其运算对象的值
///void f() noexcept(noexcept(g()));    //表示如果g不抛出异常，那么f也不抛出异常，反之亦然
//noexcept函数可以被普通的函数指针所指，指向该函数的指针是可能抛出异常的，与所指的函数互不干扰，但如果函数指针声明为noexcept，那这个指针就只能指向noexcept的函数
//如果一个类的一个虚函数声明为了noexcept，则它的子类的对应的虚函数也必须是noexcept的



void exception_handling_learning()
{
    int input = 0;
    std::cout << isZero(input) << std::endl;
    divideAB(2, 0);

    //对于new来说，一旦一个程序用光了所有它可用的内存，new表达式就会失败，默认情况下会抛出bad_alloc异常，我们可以用定位new阻止它抛出异常
    ///int* p = new (nothrow) int;  //使用了nothrow参数的定位new表达式如果分配内存失败，就会返回空指针，而不是bad_alloc

    try
    {
        throwInCatch(10);    //可以试试改成50
    }
    catch (const std::string&)
    {
        std::cout << "Ok, I'll consider it." << std::endl;
    }

    //try语句不一定要自己手动throw异常，如果我们写的代码能通过编译，但在运行时出现错误，只要我们调用的函数内部封装好了会抛出异常的代码，那我们只要写了能捕获对应类型异常的catch，就可以对这个异常进行处理

    //很多情况下程序抛出的表达式类型来自于某个继承体系，如果throw表达式解引用一个基类指针，而该指针实际指向的是派生类对象，则抛出的对象依然是基类类型，来自于派生类部分的成员会被截掉
    //也就是说，决定异常对象具体类型的是编译时的静态类型，而不是运行时的动态类型

    //异常处理的catch语句中，绝大多数的类型转换都是不受支持的，只有三种是允许的：非const到const，派生类到基类，数组或函数到指针

    //函数测试块的效果演示
    try
    {
        FunctionTryBlock ftb(0);
    }
    catch (std::string) {} //再次catch，以接收函数try块中的catch所重抛的对象
}
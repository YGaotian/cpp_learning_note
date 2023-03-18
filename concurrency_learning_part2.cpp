#include "header_learning.h"
#include <thread>

//线程的初始函数
//由于线程的构造函数默认是按值传递，对于在构造线程时向线程入口函数传入的参数，线程的构造函数会调用一些函数模板，对其类型进行退化处理，比如去除const状态，使引用类型变成值类型，即可强制按值传递
//所以这里的形参类型是const int&，在下面的线程创建时形参类型会变成int，此处如果不写const会报错
//若确实想要按引用传递，可以使用std::ref将左值引用包装起来，ref生成的是一个reference::wrap包装器，创建线程并传参的时候，遇到这个类型会脱去这个外层包装，使内部的引用暴露出来，以实现按引用传递
void myThreadInitialFunc_3(const int& i)
{
    std::cout << "i is " << & i << std::endl;
}

void myThreadInitialFunc_4(const std::string& c)   
{
    std::cout << c.c_str() << std::endl;
}

void myThreadInitialFunc_5(int& k)   
{
    k += 10;
}

void myThreadInitialFunc_6(std::shared_ptr<int> poi)
{
    *poi /= 2;
}

class MyThreadTestClass
{
public:
    MyThreadTestClass()
    {
        std::cout << "构造函数调用 " << std::endl;
    }
    MyThreadTestClass(const MyThreadTestClass& mt)
    {
        std::cout << "拷贝构造函数调用 " << std::endl;
    }
    void echo(int in)
    {
        std::cout << "member function called: " << in << std::endl;
    }
};

void concurrency_learning_part2()
{
    int threadFuncTestNum = 10;
    //初始函数中的参数类型是const int&，但是运行的时候发现实际上thread给我们的引用做了点手脚，使得函数里接到对象与上面创建的int对象实际上不是同一个，并不拥有同样的地址
    //也就是说，这里实际上是值传递，所以即使主线程执行完毕，子线程依然不会受影响
    std::thread myThread_4(myThreadInitialFunc_3, threadFuncTestNum);
    myThread_4.detach();
    std::cout << "threadFuncTestNum： " << &threadFuncTestNum << std::endl;
    //但是如果初始函数接收的是一个指针类型的参数，那么就不会按值传递，收到的和传入的是同一个对象，所以在使用detach的时候，如果使用指针作为参数，就一定会有问题
    //那我们如何将一个char[]传入线程的初始函数呢，char[]其实是指针，如果还要用detach的话，我们必须保证接收到的和函数实际使用的不是同一个指针，而是按值传递的
    //我们可以通过在主线程中显式类型转换的方式，将char[]转换为临时的string对象，这样的话实际接收到的就是另一个对象了，但是注意不能用隐式类型转换，因为不能保证主线程结束前，在子线程里，初始函数中发生的隐式类型转换已经完成
    char CH[] = "hello ";
    std::thread myThread_5(myThreadInitialFunc_4, std::string(CH)); //将临时对象作为参数传给线程
    myThread_5.detach();

    for (int i = 0; i < 101; ++i)
        std::cout << "|";
    std::cout << std::endl;

    //不管是主线程还是子线程，每个线程都有一个id，我们可以通过标准库函数 std::this_thread::get_id() 来获取当前线程的id

    //在前面的注释中写到，如果要将引用传给线程，必须使用const，但是即使这样，子线程中使用的依然不是我们传入的原对象，而是一个副本，也就是说按值传递的，那如果我们确实想在子线程中使用引用，我们就还是应该使用std::ref
    std::thread myThread_6(myThreadInitialFunc_5, std::ref(threadFuncTestNum));
    myThread_6.join();
    std::cout << threadFuncTestNum << std::endl;

    //将智能指针传递给线程
    std::shared_ptr<int> shr_pi = std::make_shared<int>(4096);  //如果用unique_ptr，下面传递参数的时候就得使用move，而且之后都不能再使用已经被移动的unique_ptr了
    std::thread myThread_7(myThreadInitialFunc_6, shr_pi);
    myThread_7.join();
    std::cout << *shr_pi << std::endl;

    //类成员函数也可以作为线程的入口
    MyThreadTestClass mttc;
    //对于成员函数，我们必须先将函数地址传入，再传入这个成员函数所属的那个类实例对象，再然后才是函数的参数
    //此处既可以按值传递也可以按引用传递，因为这里的形参类型是个universal reference模板类型，可以传递任何类型的参数，所以可以直接将实参用std::ref包裹起来按引用传递
    //这里的函数调用的实际上相当于 MyThreadTestClass::echo(mttc)，这个mttc被视为this指针，但是此处会发生拷贝，mttc被拷贝到临时对象
    std::thread myThread_8(&MyThreadTestClass::echo, mttc, 20); //此处可以将&mttc传入，就不会有拷贝构造的发生，效果等同于使用ref(mttc)，但是如果这么做，之后就绝对不能使用detach
    //然而普通函数传参的时候不能写&xxx，为什么上面就可以呢，经测试，发现 &xxx 的类型其实是 xxx 的类型所对应的指针类型，也就是说普通函数传参的时候不能写&xxx，不是语法的问题，而是因为传的值类型不匹配
    //回想一下确实，一般形参的类型要么是值类型，要么是引用类型，如果是指针类型，我们传入的实参也基本上都是一个指针变量，而不是直接传&xxx。所以上面传了一个&mttc，就是把指针传了进去，产生的效果也就相当于用std::ref传一个引用进去
    myThread_8.join();

    std::cout << "concurrency_learning part 2 ended " << std::endl;
}
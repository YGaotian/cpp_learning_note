#include "header_learning.h"
#include <functional>

//在之前的章节中已经简要地介绍过了functional头文件和function函数模板的使用
//但是function也有做不到的事情，比如说类成员函数就无法用function来包装起来，因为访问类成员函数需要类实例的参与

//之前还讲了std::bind<>的作用，可以将可调用对象和参数绑定在一起，bind与function不同，它可以绑定类成员函数指针，bind绑定完后返回一个可调用的对象，也可以用function包装起来

void func4Binder_1(int a, int b, int c)
{
    std::cout << a << b << c << std::endl;
}

void func4Binder_2(int& numref1, int& numref2, int& numref3)
{
    numref1++;
    numref2++;
    numref3++;
}

class MemberFunction4BinderClass
{
public:
    MemberFunction4BinderClass()
    {
        std::cout << "construct" << std::endl;
    }
    MemberFunction4BinderClass(const MemberFunction4BinderClass& mc)
    {
        std::cout << "copy" << std::endl;
    }
    void memberFunction(int a)
    {
        std::cout << "print a: " << a << std::endl;
    }

public:
    int member = 0;
};

void deep_in_binder()
{
    auto bindedFunction_1 = std::bind(func4Binder_1, std::placeholders::_1, 12, 25);
    bindedFunction_1(2001);   //因为使用了placeholders，所以我们在调用函数的时候需要手动传入第一个参数，第二第三个参数已经绑定好了，就无需再次传参
    //注意，上面的代码中，placeholder::_1或placeholders::_2真正重要的是_1或_2，是序号，而不是位置，不管_1在第一个参数的位置上还是第二第三个参数的位置上
    //placeholders::_1 所代表的永远都是调用时传入的第一个参数，相同地，placeholders::_2永远都代表调用时传入的第二个参数
    //举个例子，如果我们写的是 biFunc = std::bind(oriFunc, placeholders::_2, placeholders::_1)
    //则这两种调用的结果是一样的： biFunc(A, B) <=> oriFunc(B, A)
    auto bindedFunction_2 = std::bind(func4Binder_1, std::placeholders::_2, std::placeholders::_1, 18);
    bindedFunction_2(706, 197);

    //bind对于预先绑定的参数实际上是按值传递的，也就是说如果将引用绑定到函数上，那么实际上会产生一个副本，在调用的时候不会对任何预先绑定的引用对象进行修改
    //因此对于需要接受引用为参数的函数而言，不论如何都是不会收到预绑定的对象的引用的，我们只能手动将对象在调用的时候传入，这样才能收到引用
    int anum = 10, bnum = 20, cnum = 30;
    int& bnumref = bnum;
    std::bind(func4Binder_2, std::placeholders::_1, bnumref, cnum)(anum);   //bnumref是个引用，但预绑定使得它生成了副本，所以bnum不会被改变，cnum也不会按引用传递
    std::cout << "anum: " << anum << " bnum: " << bnum << " cnum: " << cnum << std::endl;

    //演示一下绑定成员函数的方法
    MemberFunction4BinderClass mf4bc;
    auto bindedMemberFunc_1 = std::bind(&MemberFunction4BinderClass::memberFunction, &mf4bc, 32);   //这里和向线程传递函数的情况类似，也是传入成员函数的地址，然后将类实例传入
                                                                                                    //也可以直接传 &inst，这样就不会发生拷贝
    bindedMemberFunc_1();
    
    //介绍一种神奇的写法，bind绑定的函数可以用function来接，然而bind不仅仅可以绑定函数，还可以绑定成员变量（普通变量不行），然后将这个成员变量用function来接，也就是说将它当作一个成员函数绑定起来
    std::function<int&(void)> intMemberAsFunction = std::bind(&MemberFunction4BinderClass::member, &mf4bc);    //注意这里要传入类实例对象的引用，否则就会生成副本，而且会生成两次
                                                                                                               //第一次是调用时会生成临时副本，第二次是bind内部处理完后需要返回临时对象的副本
                                                                                                               //因此后续的任何操作都是在副本上进行的，无法影响到原来的member
    //上面的代码将int类型的member当作一个成员函数用std::function保存起来了，function将这个int对象当作一个返回值类型为int&，不接受任何参数的可调用对象，我们可以像下面这样改变member的值
    intMemberAsFunction() = 2222;
    std::cout << intMemberAsFunction() << " == " << mf4bc.member << std::endl;

    //如果将一个临时对象给bind，那么就会调用一次构造函数生成临时对象，bind运行完后还会再调用一次拷贝构造函数生成临时对象的副本并返回
    auto tempBindedFunc = std::bind(MemberFunction4BinderClass());
}
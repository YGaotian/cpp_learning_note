#include "header_learning.h"
#include <boost/type_index.hpp>
#include <functional>

//decltype可以返回操作数的数据类型，它的类型推断也发生在编译期，decltype并不真正计算表达式的值

class someclass
{
public:
    int qint;
};

double returnDouble()
{
    std::cout << "return double" << std::endl;
    return 1234.567;
}


auto autoTypeFunc(int& i)
{
    i *= 2;
    return i;
}

decltype(auto) declAutoTypeFunc(int& i)
{
    i *= 2;
    return i;
}

void decltype_learning()
{
    const decltype(1) constint = 125;   //decltype()括号中可以是右值，它推导出传入的参数的数据类型
    decltype(constint) cint = 251;  //decltype(constint)的结果就是const int，如果decltype的括号中是一个变量，则变量的const属性不会被丢弃，这与auto不一样
    const int& constintRef = constint;
    decltype(constintRef) ciref = constintRef;  //如果decltype()括号中是个引用，则const与&都不会被丢弃
                                                //也就是说auto看的是等号右边的值代表的内容的类型，而decltype是看操作对象本身的类型
    //decltype还能将类成员用作操作对象
    decltype(someclass::qint) scint = 12;
    someclass scinst;
    decltype(scinst.qint) scinstInt = 13;
    auto&& scinstRef = scinst;  //scinstRef是someclass &类型，因为有引用折叠
    someclass scinst2;
    decltype(scinstRef) && scinst2Ref = scinst2;    //scinst2Ref是 someclass & 类型，因为scinstRef是 someclass & 类型，遇到&&又发生了引用折叠，所以依然是someclass &类型
    std::cout << boost::typeindex::type_id_with_cvr<decltype(scinst2Ref)>().pretty_name() << std::endl;

    //decltype的的括号中也可以是一个表达式
    decltype(constintRef + 1) k = 90;   //constintRef是个引用类型，但是 constintRef + 1 就变成了一个表达式，这个表达式的结果是一个整数类型，所以k是int类型，可以被赋值
    int w = 122;
    int* wptr = &w;
    ///decltype(*wptr) e = 12;  //报错
    decltype(*wptr) e = w;  //为什么上面的会报错，而这一行却是正常的呢，因为wptr是一个指针，而*wptr是个可以被赋值的表达式，所以*wptr是个左值
                            //如果一个表达式可以作为赋值语句等号左边的值，那么对该表达式使用decltype返回的就是个引用，所以decltype(*wptr)得到的是一个int&类型，而不是w变量本身的类型int
    std::cout << &w << " " << &e << std::endl;
    //如果在变量的外面加上一个括号，那么这就变成了一个表达式，用decltype就会推断为引用类型
    decltype((w)) r = w;

    //decltype中还可以放入函数调用
    decltype(returnDouble()) doubleVar = 123.456;   //这么做会推断出函数返回值的类型，也就是double，但是实际上这里的函数并不会真正的被调用，因为类型是编译期就推断出来的
    //decltype也可以直接放入函数名，这样推断出来的就是对应的可调用对象类型了
    decltype(returnDouble) rdCallable;   //注意，推断出来的并不是函数指针类型，比如这里的类型是double(void)，并不是double(*)(void)，所以不能接returnDouble
    //如果我们想要用decltype推导出来的类型来接函数，我们可以使用std::function<>类模板
    std::function<decltype(returnDouble)> rdFunction = returnDouble;
    rdFunction();

    //decltype也可以与auto相结合使用，函数的尾置返回类型就是其中的一种应用
    /// template <typename T>
    /// auto func(T arg) -> decltype(arg) {}
    //还有另一种使用，是形如这种形式的：decltype(auto)。当我们用auto来推导函数的返回值类型的时候，auto会推断出值类型，因为auto推断函数返回值类型实际上相当于用auto去推断return后面的对象
    //这一点已经在auto_learning.cpp一节解释过，那么也就是说推断结果就是个单纯的值类型，而非引用类型，对于一个函数，由于返回的不是引用，因此函数调用的结果就是个无法取得地址的临时对象，也就是右值
    //因此像autoTypeFunc这样的函数，本来可能是想返回传入的实参的引用，这样的话就是一个左值，是可以被赋值的，但是因为用的auto来推断函数的返回类型，因此返回的是一个右值，无法被赋值
    int integernum = 12;
    /// autoTypeFunc(integernum) = 10;  //报错
    //如果希望这个函数返回左值，应该手动的将返回类型写为左值引用
    //我们也可以换一种写法，就是使用decltype(auto)
    declAutoTypeFunc(integernum) = 10;  //decltype(auto) func()就相当于将函数中return后面的东西带入到auto的位置，如果是return x，那么函数名前面就是decltype(x)
                                          //这样的话不管x是什么类型，都可以通过decltype原封不动地推导出来，这也是符合decltype的推导规则的，decltype(auto)是 c++ 14 新增的
    std::cout << integernum << std::endl;
    //类似的，decltype(auto)也可以用于变量声明中，作用与上面一样
    //甄别：如果在函数里创建了一个局部对象local，并且写了 return(local)，如果函数使用的是decltype(auto)，那么就会将这个局部对象的引用返回出来，如果这时还像上面的代码一样，对这个函数调用进行了赋值
    //此时就是在向一个已经释放掉的内存上赋值，这种行为产生的后果是不可预料的
}
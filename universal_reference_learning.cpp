#include "header_learning.h"

//万能引用是用在模板中的技术，它的写法像右值引用，T&&，T与&&不能分开，否则就是右值引用了，比如说vector<T>&&就不是万能引用，万能引用也称作未定义引用
template <typename T>
void printUniversalRef(T&& arg)
{
    std::cout << arg << " at " << &arg << std::endl;
}

template <typename T>
class templateClass4Ref
{
public:
    void testFunc(T&& i)
    {

    }
};

void universal_reference_learning()
{
    int&& intRRef = 10;
    std::cout << &intRRef << std::endl;
    printUniversalRef(intRRef);
    printUniversalRef(22222);
    int intLVal = 100;
    std::cout << &intLVal << std::endl;
    printUniversalRef(intLVal);
    int& intLRef = intLVal;
    std::cout << &intLRef << std::endl;
    printUniversalRef(intLRef);
    //可以发现，万能引用可以同时接收左值与右值，左值引用与右值引用
    //万能引用仅用于类型推导中，且写作T&&，auto也存在万能引用的概念，后续再谈

    //如果在形参的万能引用前面加上const，那么它就不再是一个万能引用类型了（仅针对形参类型而言，传入的实参中有const没关系），const T&&就是一个右值引用，打回了原形

    //万能引用T&&实际上就是右值引用，只是在类型推导时它也能接收左值和左值引用，所以万能引用并不是一种新的引用类型

    //类模板的成员函数中的T&&并不是万能引用
    int testIntVar = 777;
    templateClass4Ref<int> tc4r;
    ///tc4r.testFunc(testIntVar);    //报错
    tc4r.testFunc(10);  //可行，因为10是右值，而testFunc函数的参数类型T&&变成了右值引用int&&，而不是万能引用
    //发生以上的现象的原因是，类模板templateClass4Ref的这个成员函数不是函数模板，所以没有发生参数类型推导，类型模板参数在实例化类的时候就已经确定，万能引用只在发生类型推导时可用
}
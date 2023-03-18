#include "header_learning.h"

void what_are_callable_objects()
{
    //Callable objects 是指可调用对象，比如函数，函数指针。还有一些其他的，比如仿函数(functor)
    //仿函数是指具有operator()成员函数的类对象，it is something that performs a function
    //C++中的仿函数是通过重载()运算符实现的，仿函数又称为函数对象(function object)：能行使函数功能的类
    FunctorClass functorC;
    functorC(31);   // 一个仿函数调用

    //除了上述的几个，还有一些可调用对象，比如，可被转换为函数指针的类对象，还有类成员函数指针
}

void FunctorClass::operator()(int num)
{
    std::cout << "A functor named \"FC " << num << "\" is called!" << std::endl;
}
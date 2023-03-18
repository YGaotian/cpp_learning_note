#include "header_learning.h"

//constexpr可以修饰变量，也可以修饰指针，还可以修饰函数，被constexpr修饰的变量和指针一定是常量，也就是说，constexpr会修饰指针本身，使它无法指向其他地址
//constexpt定义的指针的初始值必须是存放在固定地址的对象，局部对象并不是存放在固定地址的，所以constexpr指针不能指向它们，但是局部静态对象是个例外
int i = 90;
constexpr int* cip = &i;

//constexpr修饰的函数的返回值可以被constexpr修饰的变量去接收，这样的话constexpr修饰的函数的返回值是编译期确定的，所以并不会产生函数调用
//但是如果变量没有用constexpr修饰，或是函数没有用constexpr修饰，就无法在编译期确定返回值
constexpr int constexprFunction(int a, int b)
{
    return a * a + 2 * a * b + b * b;
}

//从cpp17开始，还可以使用constexpr运算符，使一个可以在编译期或运行时确定结果的表达式在编译期确定结果
//下面通过可变参数模板的包展开来演示
template <typename U, typename ...T>
void printAllArg(U first, T... arg)
{
    if constexpr (sizeof...(T))             //这么写就不需要定义函数参数包展开终止函数了，constexpr使得sizeof...(T)可以在编译期间就求出结果，因此通过编译
    {
        std::cout << first << std::endl;
        printAllArg(arg...);
    }
    else
    {
        std::cout << first << std::endl;
    }
}


void constexpr_learning()
{
    constexpr int squareOfAPlusB = constexprFunction(2, 4);
    std::cout << squareOfAPlusB << std::endl;
    printAllArg(1, 2, 3, 33, 443, 556, 789);
}
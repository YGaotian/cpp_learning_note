#include "header_learning.h"

void stlFunctional_learning()
{
    //stl中有一些定义好的函数对象，也就是说仿函数functor，使用之前，要引用头文件 functional
    //比如说plus就是一个仿函数，它是一个类模板
    std::plus<int>();   //创建了一个临时对象，plus可以将传入的两个参数进行加法运算
    std::plus<double> doublePlus;   //创建了一个plus对象实例
    std::cout << doublePlus(12.5, 121.1) << std::endl;
    //标准库中的函数对象可以大致分为以下几大类
    //算术运算类，上面的plus就属于这一类，还有减法除法乘法，取模取反
    //关系运算类，比如大于，小于，大于等于，小于等于，相等，不相等
    //逻辑运算类，逻辑与，逻辑否，逻辑或
    //位运算类，和，或，异或
    std::vector<int> vecIntSort = { 2, 3, 45, 6, 21, 32 };
    std::sort(vecIntSort.begin(), vecIntSort.end(), std::greater<int>());   //使用stl定义好的函数对象作为规则来排序
    std::for_each(vecIntSort.begin(), vecIntSort.end(), printElement);
}
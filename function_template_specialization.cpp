#include "header_learning.h"

//函数模板与类模板类似，也可以特化，但是它只能全特化，偏特化是不被支持的
//泛化版本，就是普通的函数模板
template<typename T1, typename T2>
void mySpecializationTemplateFunction(T1& a, T2& b)
{
    std::cout << "泛化的函数模板 " << a << " and " << b << std::endl;
}

//全特化版本
template<>
void mySpecializationTemplateFunction(int& a, double& b)    //因为泛化版本这里的形参类型都是引用，所以特化版本也必须是引用
{                                                           // 特化版本是要跟着泛化版本来的，特化是只特化类型模板参数，而不是函数形参的类型，就是说，只替换T1和T2这种typename的参数
    std::cout << "全特化的 int，double 函数模板： " << a << " and " << b << std::endl;
}

//模板特化版本不参与函数的重载决策过程，因此在和函数重载一起使用的时候，可能出现不符合预期的结果
// 因此标准C++禁止了函数模板的偏特化

//如果函数模板的全特化和函数重载一起使用，如果有全特化的类型模板参数与函数重载的形参类型刚好一致的话，编译器会选择使用重载的函数，而不是特化的函数模板

void function_template_specialization()
{
    int a = 666;
    int b = 233;
    int& a_ref = a;
    int& b_ref = b;
    double c = 246;
    double& c_ref = c;
    //泛化的函数模板调用
    mySpecializationTemplateFunction(a_ref, b_ref);
    //特化的函数模板调用
    mySpecializationTemplateFunction(a_ref, c_ref);
}
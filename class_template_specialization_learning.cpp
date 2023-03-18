#include "header_learning.h"

//泛化版本的类模板，也就是普通的类模板
template<typename T1, typename T2>
class MySpecializationTemplateClass
{
public:
    MySpecializationTemplateClass()
    {
        std::cout << "泛化版本构造 " << std::endl;
    }
    ~MySpecializationTemplateClass()
    {
        std::cout << "泛化版本析构 " << std::endl;
    }

public:
    void printSth()
    {
        std::cout << "泛化版本print " << std::endl;
    }
};



//特化，就是具体化，是指对特定类型版本的模板做具体的实现
// 必须先有泛化的类模板，才能有特化版本的类模板
// 全特化，就是所有模板参数都做具体化的实现
template<>  //因为是全部特化，所以<>里面什么都不用写
class MySpecializationTemplateClass<int, int>   //这里直接写上具体的参数类型
{
public:
    MySpecializationTemplateClass()
    {
        std::cout << "全特化版本<int, int>构造 " << std::endl;
    }
    ~MySpecializationTemplateClass()
    {
        std::cout << "全特化版本<int, int>析构 " << std::endl;
    }

public:
    void printSth()
    {
        std::cout << "全特化版本<int, int>版本print " << std::endl;
    }
};

//全特化类中的某一特定成员函数
template<>
void MySpecializationTemplateClass<double, double>::printSth()
{
    std::cout << "全特化版本<double, double>版本print " << std::endl;
}



//偏特化
//只特化某几个模板参数的偏特化，是对于参数数量而言的
template<typename T2>                           //这里只特化形参T1，T2的参数可以随便给
class MySpecializationTemplateClass<int, T2>
{
public:
    MySpecializationTemplateClass()
    {
        std::cout << "偏特化版本<int, T2>构造 " << std::endl;
    }
    ~MySpecializationTemplateClass()
    {
        std::cout << "偏特化版本<int, T2>析构 " << std::endl;
    }

public:
    void printSth()
    {
        std::cout << "偏特化版本<int, T2>版本print " << std::endl;
    }
};

//只特化模板参数的类型的偏特化，是对于参数的类型范围而言的
template<typename T1, typename T2>                           //这里是对参数类型范围的偏特化，所以typename T1, typename T2都写上
class MySpecializationTemplateClass<T1*, T2>                 //这里先只特化T1的范围，要一起特化T2也没问题，T1*是T1的子集，所以说范围上比T1小，其他的例子还有const T1，T1&，还有T1&&等
{
public:
    MySpecializationTemplateClass()
    {
        std::cout << "偏特化版本<T1*, T2>构造 " << std::endl;
    }
    ~MySpecializationTemplateClass()
    {
        std::cout << "偏特化版本<T1*, T2>析构 " << std::endl;
    }

public:
    void printSth()
    {
        std::cout << "偏特化版本<T1*, T2>版本print " << std::endl;
    }
};



void class_template_specialization()
{
    MySpecializationTemplateClass<char, int> mstc_0;            //实例化了一个泛化版本的对象
    mstc_0.printSth();                                          //调用了泛化版本类实例的成员函数
    MySpecializationTemplateClass<int, int> mstc_1;             //实例化了一个int，int特化版本的对象
    mstc_1.printSth();                                          //调用了int，int特化版本类实例的成员函数
    MySpecializationTemplateClass<double, double> mstc_2;       //实例化了一个泛化版本的对象
    mstc_2.printSth();                                          //调用了泛化版本类实例的double，double特化版本的成员函数
    std::cout << std::endl;

    MySpecializationTemplateClass<int, double> mstc_3;          //实例化了一个只特化某几个模板参数的偏特化对象
    mstc_3.printSth();                                          //调用了只特化第一个模板参数的偏特化版本类实例的成员函数
    MySpecializationTemplateClass<char*, int> mstc_4;           //实例化了一个对模板参数范围偏特化的对象
    mstc_4.printSth();                                          //调用了对模板参数范围偏特化的类实例的成员函数
    MySpecializationTemplateClass<const char*, int> mstc_5;     //如果实例化一个 const T1* 版本的对象，但是并没有符合的偏特化版本，那就会变成实例化 T1* 的版本
    mstc_5.printSth();                                          // 因为 const T1* 也属于 T1* 的子集
    std::cout << std::endl;
}

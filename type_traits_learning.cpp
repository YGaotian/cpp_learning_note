#include "header_learning.h"

//类型萃取是一种运用在泛型编程中的技术，意思就是提炼出对象的类型信息，c++11开始，标准库里提供了很多类型萃取的接口，是一些类模板

template <typename T>
void traitsDemonstrate(const T& obj)
{
    std::cout << "is_class: " << std::is_class<T>::value << std::endl;                                  //是否为类类型
    ///std::cout << "is_pod: " << std::is_pod<T>::value << std::endl;    是否是普通类（与C兼容的数据类型）：没有构造/析构/移动/拷贝函数或运算符，无虚函数或虚基类，且布局有序
    ///                                                                  布局有序--非静态的成员访问级别相同，都为public/private/protected
    ///                                                                         --如果有父类，则当前类的第一个成员不能是父类类型，非静态成员只能存在于父类或子类其中之一内
    ///                                                                  cpp20已弃用
    //上面的可以用is_standard_layout代替
    std::cout << "is_standard_layout: " << std::is_standard_layout<T>::value << std::endl;
    std::cout << "is_default_constructible: " << std::is_default_constructible<T>::value << std::endl;  //是否有默认构造函数
    std::cout << "is_move_constructible: " << std::is_move_constructible<T>::value << std::endl;        //是否有移动构造函数
    std::cout << "has_virtual_destructor: " << std::has_virtual_destructor<T>::value << std::endl;
}

void type_traits_learning()
{
    Myclass mmm;
    traitsDemonstrate(mmm);
    std::cout << std::endl;
    int aaaaa = 10;
    traitsDemonstrate(aaaaa);
    std::cout << std::endl;
    Dog ddd;
    traitsDemonstrate(ddd);
    std::cout << std::endl;
    FunctorClass fffff;
    traitsDemonstrate(fffff);
    std::cout << std::endl;
}

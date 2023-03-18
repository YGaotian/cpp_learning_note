#include "header_learning.h"
#include <boost/type_index.hpp>

template <typename T>
void print_type_template_parameter(T& arg)
{
    using boost::typeindex::type_id_with_cvr;
    auto tiwc = type_id_with_cvr<T>();              //得到自动推导出来的类型
    std::cout << "T is  : " << tiwc.pretty_name() << std::endl;   //打印人类可读的类型
    std::cout << "arg is: " << type_id_with_cvr<decltype(arg)>() << std::endl;
}

template <typename T>
void print_const_T_ref(const T& arg)
{
    using namespace boost::typeindex;
    std::cout << "T  : " << type_id_with_cvr<T>().pretty_name() << std::endl;
    std::cout << "arg: " << type_id_with_cvr<decltype(arg)>().pretty_name() << std::endl;
}

template <typename T>
void print_pointer(T* arg)
{
    using namespace boost::typeindex;
    std::cout << "T  : " << type_id_with_cvr<T>().pretty_name() << std::endl;
    std::cout << "arg: " << type_id_with_cvr<decltype(arg)>().pretty_name() << std::endl;
}

template <typename T>
void print_universal_ref(T&& arg)
{
    using namespace boost::typeindex;
    std::cout << "T  : " << type_id_with_cvr<T>().pretty_name() << std::endl;
    std::cout << "arg: " << type_id_with_cvr<decltype(arg)>().pretty_name() << std::endl;
}

template <typename T>
void print_just_value(T arg)
{
    using namespace boost::typeindex;
    std::cout << "T  : " << type_id_with_cvr<T>().pretty_name() << std::endl;
    std::cout << "arg: " << type_id_with_cvr<decltype(arg)>().pretty_name() << std::endl;
}

void func4Transfer(int, double, float, char) {}



//本节主调函数
void understand_type_deduction_with_boost_library()
{
    //普通引用的情况
    int i = 202;
    print_type_template_parameter(i);
    const int a = 101;
    const int u = 303;
    const int& ur = u;
    print_type_template_parameter(a);   //const左值传入模板，T是const int，arg是const int &
    print_type_template_parameter(ur);  //const左值的引用传入模板，T依然是const int，arg依然是const int &
    //综上所述，函数模板的形参若是引用类型T&，则如果传入引用类型的实参，它的引用会被直接忽略掉，也就是说，T不是引用，其他的修饰符不动

    std::cout << std::endl;

    //如果将const 左值引用作为函数模板的形参的类型，即const T&，并向内传入const左值引用类型的实参，那么T会被推导成非const左值的类型，arg依然是const左值引用类型
    print_const_T_ref(ur);  //传入的参数是const int &，推导出来的结果会忽略const 和 &，于是T是int，arg的类型依然是const int &
    print_const_T_ref(u);   //传入的参数是const int，推导出来的结果会忽略const

    std::cout << std::endl;

    //如果将指针作为函数模板的形参类型，并传入指针，会得到与上述相似的结果
    int valint = 648;
    const int* valintPtr = &valint;
    print_pointer(&valint);
    print_pointer(valintPtr);
    //但是有一点不同的是不能将int类型的参数传进去，因为函数的形参类型是指针，不接受非指针的对象传入

    //总结，类型模板参数推导会保证函数最终得到的实际参数类型，是与函数形参列表中的类型一致的，也就是说推导出来的T是正常地与各种符号或关键字结合在一起的，不会出现重复的修饰词
    //  如果函数的参数类型仅仅是T，那么传入的实参类型是什么，T最终就是什么
    //  如果函数的参数类型是T与修饰词结合的，比如const T&，那么传入的实参类型如果是const int&，那么T最终就会被推导为int，const与&会被函数形参类型中的const与&接替
    //  其他的关键词或符号的替换规则也是一样的
    std::cout << std::endl;


    //万能引用的情况
    const int q = 2001;
    const int& qLref = q;
    print_universal_ref(q);     //传入左值，则推导出来的类型为左值的引用，所以T是const int&，arg也是const int&类型，原本的&&不见了，是因为发生了引用折叠，后续再讲
    print_universal_ref(qLref); //传入左值引用，推导出来也为左值引用，所以T是const int&，arg也是const int&类型
    std::cout << std::endl;

    //向万能引用传入一个右值
    print_universal_ref(101);     //传入右值，推导出来T为左值，arg为右值引用类型int&&，因为实际上万能引用并不是一种引用类型，它是仅在发生类型推导时才会既能接收
                                  //左值和左值引用，又能接收右值的右值引用
    int&& Rref = 303;
    print_universal_ref(Rref);    //传入右值引用，推导出来T为左值引用，arg也是左值引用，这是因为右值引用本身是个左值对象，在right_value_reference.cpp一节曾经讲过这一点
    std::cout << std::endl;

    //向万能引用传入一个地址
    std::cout << "传入&xxx的情况" << std::endl;
    print_universal_ref(&q);    //向万能引用传入了&q，通常说&xxx得到的就是xxx的地址，但实际上取址符作用于一个左值对象，会返回指向该对象的一个指针，这个指针是个右值，是个常量数值
                                //所以 &q 遇到万能引用时，T被解释为指针类型，T&&是一个指针类型的右值引用

    //向万能引用传入一个指针
    const int* qptr = &q;
    print_universal_ref(qptr);    //然而一个通常的指针类型的对象是左值，或许可以这么理解，int a = 1，这里的1是整数，a是整数类型的变量（或者说对象），整数1是右值，整数变量a是左值
                                  //那么相同的，int* qptr = &q，这里 &q 是指针，qptr是指针类型的变量（或者说指针类型的对象），所以指针 &q 是右值，指针变量 qptr 是左值
                                  //因此当我们向万能引用传入一个指针时，实际上是指传入一个指针类型的变量，是左值，T推导为指针类型的左值引用，引用折叠发生，&&消失，arg就是指针类型的左值引用类型
    std::cout << std::endl;


    //仅仅是值类型的情况
    const int p = 1225;
    const int& pref = p;
    //左值和左值引用都被推断为左值，如果有const关键字修饰，const会被忽略，因为是按值传递的，收到的都是副本
    print_just_value(p);
    print_just_value(pref);
    std::cout << std::endl;
    //我们可以将指针传递进去，这样T就会被推导为指针类型，对于指针类型来说，所指对象的const属性不会被忽略
    const int* pptr = &p;
    print_just_value(pptr);
    const int* const pptrConst = &p;    //第一个const用来修饰指针指向的对象，即常量的指针，意思是指向不可修改对象的指针，所以这个const会保留，第二个const修饰指针，即指针类型的常量，它会被忽略
    print_just_value(pptrConst);     //因为是按值传递，此处的值是个指针，也就是说传入的指针被复制了一份，那么指针的const属性丢失
    //由于数组名是首地址，所以推导出来也是指针类型，结论与上面int类型的指针是一致的
    const char cstr[10] = "hello";
    print_just_value(cstr);
    std::cout << std::endl;


    //普通引用类型的形参接受数组的情况
    const char ccstr[10] = "world";
    //因为是按引用传递，所以此次的T的类型不会被推断为指针，而是整个数组本身的类型，即数组类型
    print_type_template_parameter(ccstr);   //T推导出来是const char[10]，arg的类型就是const char(&)[10]，也就是const char数组类型的对象的引用，
    std::cout << std::endl;


    //函数名作为实参传递的情况
    //按值传递
    print_just_value(func4Transfer);    //由于函数名其实就是函数的地址，可以赋给指针，所以此处按值传递时T会被推导为相应类型的函数的指针，即void (*) (int, double, float, char)
                                           //   arg的类型正是推导出来的T类型
    //按引用传递
    print_type_template_parameter(func4Transfer);   //由于是按引用传递，所以T被推导为相应的函数类型，而arg则是T&，才是引用类型，即函数的引用void (&) (int, double, float, char)


    ///总结
    ///类型推断时，实参的类型如果含有&，则推断出来的T本身是不含&的，也就是说&会被忽略，左值引用会被视为左值，如果函数是按引用传递的，那么参数列表中的参数类型是T&，这一整个就是引用类型
    ///万能引用的情况中，左值实参与右值实参推断出来的结果T不同，传入左值或左值引用都会推断为左值引用，因为是按引用传递。传入右值，T就推断为传入的值的类型，而因为是按引用传递，所以参数类型就是右值的引用T&&
    /// 传入右值引用，T与参数类型就是左值引用，因为右值引用本身是左值，此处又是按引用传递的
    ///按值传递的实参，如果含有const，则const不起作用，因为会生成一个非const的临时对象来接传入的值，但是如果传入的是指向const对象的指针，则推断出来的T依然是指向const对象的指针类型
    ///数组或函数名作为实参会被推断为指针，除非函数模板是按引用传递，则传入数组或函数名，T会被推断为对应类型的引用
}
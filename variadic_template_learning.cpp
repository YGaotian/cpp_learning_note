#include "header_learning.h"

//可变数目的参数被称为参数包
// 参数包有两种，分别是模板参数包（表示零或多个模板参数）和函数参数包（表示零或多个函数参数）

//typename... 指出接下来的参数表示零个或多个类型的列表（就是模板参数包）
// 在模板参数列表中，一个类型名后面跟...表示零个或多个 给定类型 的 非类型参数 的列表

//可变参函数模板
// 如果在函数的参数列表中，一个参数的类型是 模板参数包（就是<typename... T>里的 T），那么此参数就是一个函数参数包
template<typename... T>    //typename... 指出接下来的参数表示零个或多个类型的列表，所以调用的时候可以传入不同数量和不同类型的实参
void variadicTemplateFunc1(const T&... args)   //因为args的参数类型是 T（模板参数包），所以 args 是一个 函数参数包
{
    //sizeof...运算符可以返回一个常量表达式，表示包中元素的个数
    std::cout << sizeof...(args) << std::endl;
    std::cout << sizeof...(T) << std::endl;
}

//包扩展（包展开）
// 我们可以通过递归的方式将传进来的参数包进行展开
// 为了结束递归，我们还得先定义一个当函数参数包展开完毕的时候，variadicTemplateFuncExpand 接收不到任何参数的函数版本
//递归终止函数
void variadicTemplateFuncExpand()
{
    std::cout << "包展开完毕 " << std::endl;
}

template<typename T, typename... U>
void variadicTemplateFuncExpand(const T& firstArg, const U&... restArgs)    //每次递归调用时，都将函数参数列表前后拆分为一个参数和一个参数包
{
    std::cout << firstArg << std::endl;
    //在restArgs后面写上...来触发扩展操作，restArgs...称为模式，就是告诉编译器我们希望如何展开剩下的参数列表
    // 我们可以把模式改成func(restArgs)...，这样的话展开后就等价于 func(arg_A),func(arg_B),func(arg_C),...,func(arg_N)
    // 但是如果这样写 func(restArgs...)，就可能不对，因为这样展开后等价于 func(arg_A, arg_B, arg_C, ..., arg_N)，如果func没有与之相应的函数重载的话就会报错
    variadicTemplateFuncExpand(restArgs...);
}



//可变参类模板
//主模板定义
template<typename... T>
class VariadicTemplateClass1{};

//我们可以通过递归继承的方式展开可变参数类模板
// 此处是一个模板的偏特化，将原本的模板参数包偏特化为第一个类型模板参数为 K 和剩下的一包类型模板参数 U
template<typename K, typename... U>
class VariadicTemplateClass1<K, U...> : private VariadicTemplateClass1<U...>    //此处通过私有递归继承，每次都将参数列表分为参数 K 和参数包 U
{
public:
    VariadicTemplateClass1(){}
    //光递归继承是无法展开参数包的，因为继承了自己作为父类后，父类没有实例化的话就不存在，所以父类还要调用构造函数，但默认构造函数不接受任何参数，所以要调用有参构造函数
    // 所以说我们要在写有参构造函数的时候对父类传参，将剩余的一包参数传入父类的构造函数，这样每次递归的时候才会调用有参构造函数，来展开参数包
    // 我们已知递归到最后restArgs的元素数量是0，而因为每一次递归都是继承，先有父类才有子类，所以restArgs列表为空的类对象是最先实例化的，然后才是有一个元素的restArgs
    VariadicTemplateClass1(K firstArg, U... restArgs): VariadicTemplateClass1<U...>(restArgs...)
    {
        std::cout << "VariadicTemplateClass1 " << this << " 实例化了 " << std::endl;
        std::cout << "currentArg: " << firstArg << std::endl;
    }
};


//我们没有定义可变参数模板的空参数列表的偏特化，却依然可以展开模板参数包，但是我们也可以自己实现一个空参数列表的偏特化
// 主模板
template<typename... Q>
class VariadicTemplateClass2 {};

template<typename S, typename... V>
class VariadicTemplateClass2<S, V...> : private VariadicTemplateClass2<V...>
{
public:
    VariadicTemplateClass2() {}
    VariadicTemplateClass2(S firstArg, V... restArgs) : m_obj(firstArg), VariadicTemplateClass2<V...>(restArgs...)
    {
        std::cout << "VariadicTemplateClass2 " << this << " 实例化了 " << std::endl;
        std::cout << "currentArg: " << m_obj << std::endl;
    }
    S m_obj;
};

//空参数列表的偏特化定义
template<>
class VariadicTemplateClass2<>
{
public:
    VariadicTemplateClass2()
    {
        std::cout << "空参数列表的偏特化类模板的构造函数执行，看打印结果，可以证明空参数列表的模板是最先实例化的 " << std::endl;
    }
};


//我们也可以通过递归组合的方式展开类模板
// 组合就是如果有一个类A和一个类B，A中定义了一个B类型的成员，这种关系就叫组合
//主模板定义
template<typename... H>
class VariadicTemplateClass3 {};

//递归组合的特化版本
template<typename F, typename... G>
class VariadicTemplateClass3<F, G...>
{
public:
    VariadicTemplateClass3() {}
    VariadicTemplateClass3(F firstArg, G... restArgs) : m_obj(firstArg), m_vtc3(restArgs...)
    {
        std::cout << "VariadicTemplateClass3 " << this << " 实例化了 " << std::endl;
        std::cout << "currentArg: " << m_obj << std::endl;
    }
public:
    F m_obj;
    VariadicTemplateClass3<G...> m_vtc3;    //因为是组合，所以每次递归都会创建出一个新的VariadicTemplateClass3的实例成员对象，所以每次地址都会有变化
};

//还有一种通过tuple和静态函数和计数器来展开类模板参数包的方法，由于效果和以上两种的区别只是展开的顺序是正序的，要写的东西还多一点，个人感觉没什么意义，所以这里暂且不写
// 还有其他的一些展开参数包的方式，这里不再赘述

void variadic_template()
{
    //可以传入不同数量不同类型的参数
    variadicTemplateFunc1(0, 2.3f, "hello world");
    variadicTemplateFunc1("h");
    std::cout << std::endl;
    variadicTemplateFuncExpand(123, 23.33f, 3.14f, "hello");
    variadicTemplateFuncExpand(1, 2, 3, 4);
    std::cout << std::endl;

    //模板类
    VariadicTemplateClass1<int, double, std::string> vtc_1(1, 2.1418f, "wow");                  //递归继承版本的展开
    std::cout << std::endl;
    VariadicTemplateClass2<double, int, std::string> vtc_2(3.14f, 22, "BOB");                   //递归继承版本的展开，同时还具有自定义的空参数的偏特化版本的类模板定义
    std::cout << std::endl;
    VariadicTemplateClass3<int, int, std::string, std::string> vtc_3(0, 1000, "great", "wall"); //递归组合版本的展开
}
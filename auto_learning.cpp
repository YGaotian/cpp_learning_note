#include "header_learning.h"

//auto可以与指针，引用，const等限定符结合使用，所以auto和模板的类型参数T是类似的，可以看作是一个类型的占位符，auto是在编译期的时候就可以推断类型的，所以它不会影响程序的运行效率
//也因此在使用auto的时候必须立即初始化，否则类型推断不出来

class clx
{
public:
    clx() = default;
    clx(const clx& c)
    {
        std::cout << "clx copy" << std::endl;
    }
};

void auto_learning()
{
    clx classXinst_1;
    const auto& classXinstRef = classXinst_1;   //auto就是clx
    auto classXinst_2 = classXinstRef;  //auto依然是clx，按值传递的时候const属性和引用类型都会被抛弃，也就是说，classXinst_2是一个classXinst_1的副本，会调用拷贝构造函数
    auto& classXinstRef_2 = classXinstRef;  //classXinstRef是const clx &类型，此处的auto被推断为const clx，也就是说&遇到&会发生引用折叠，const会保留
    auto classXinst_3 = new auto(classXinst_2);  //auto可以用于new，此处的第一个auto就是clx*，第二个auto就是clx，同样，也发生了拷贝
    const auto* classXinst3_ptr = &classXinst_1;    //auto是clx

    //用auto也可以用万能引用，情形与类型模板参数T是一模一样的，写为auto&&，也会发生引用折叠
    auto&& classXUniversalRef = classXinst_1;   //可以接左值，万能引用接左值会推导为左值引用，左值引用&遇到&&发生了引用折叠，变成了&，所以classXUniversalRef是clx &类型的

    //auto也可以推断出数组类型，函数指针类型，函数的引用类型

    //变量有多种初始化方式，比如等号赋值，圆括号初始化，花括号初始化列表
    int intValue = 618;             //intValue是个int类型的变量
    double doubleValue = {2.15};    //doubleValue是个double类型的变量
    //auto也同样适用
    auto someInt(12);                               //auto被推导为int类型
    auto someDouble = 3.1415926;                  //auto被推导为double类型
    //但用auto时，如果使用花括号的初始化列表，auto就可能不会被简单地推导为等号右边的值的类型了，因为是花括号，auto会优先被推导为列表类型
    auto something = {2.1828};   //这里auto类型变成了std::initializer_list<double>类型，它是一个表示某种数组的类模板
    auto somethingElse{ 3.33333 };                //然而如果没有用等号，就算使用了花括号，这里的auto却依然可以被推导为double类型
    //于是我们知道，只有当 = 与 {} 一起使用的时候，auto才会推断为initializer_list类型，这个类型可以存多个数据 
    auto somethingNew = { 3.1415926, 2.1818, 3.33333 };
    //这种推导只适合auto，不适合类型模板参数，如果有个函数模板 template <typename T> void tempFunc(T arg)，那么下面这么写的话会报错
    ///tempFunc({12});  //error
    //除非显式指定这个参数是个std::initializer_list类型：
    ///template<typename T>
    ///void tempFunc(std::initializer_list<T> arg);
    //那么 tempFunc({12}) 就是可以正常执行的，因为这里的{12}就会使arg被推断为std::initializer_list<int>类型

    //auto不能放在函数形参的类型上
    ///void func(auto arg); //报错
    //但是auto可以用于推断函数的返回值类型
    ///auto func(); //可行，会根据返回值自动推断出对应类型的右值，因为函数名前的auto实际上相当于用auto来推断return关键字后面的对象的类型，就像 auto anonymous = variable
    ///               如果return后面的对象是个左值引用，因为我们用的是auto来推断，类型推导的结果是符合上面讲的auto推导规则的，也就是说引用和const属性都会被抛弃
    ///               同样地，return后面的对象是个左值引用时，我们使用nuto&来推导，也就是在函数名前写的是auto&，那么推导结果就依然是左值引用类型
    //auto不能用于普通的类成员变量的类型推导，会报错，只能用于类中的静态常量成员，即 static const auto member = xxx; 是合法的。注意因为用了auto，所以该成员必须在类中立即初始化
}
#include "header_learning.h"
#include "class_template_learning.hpp"

//对于类模板和函数模板，我们都可以为其添加上默认参数，下面演示函数模板的默认参数的一种用法案例
// 对于模板的默认参数来说，和普通的函数的默认参数是一样的，一旦某个形参有了默认值，那么这个形参之后的所有形参都要有默认值
template<typename X, typename F=FunctorClass>    //FunctorClass 是在前面 what_are_callable_objects 一节中，介绍仿函数时定义的一个类
void default_param_tempfunc(const X &n, F func=F())  //函数模板将 FunctorClass 作为第二个类型模板参数的默认值，所以在函数的特征标里面，形参func的缺省值是 F()
{                                                       // 意思就是调用 FunctorClass 的构造函数，生成了一个 FunctorClass 的实例对象
    func(n);    //仿函数的调用
}

void default_param_of_templates()
{
    //函数模板使用缺省参数的时候<>可以省略
    default_param_tempfunc(31);
    //对于类模板来说，实例化的时候<>不能省略
    MyList<>myDefaultList{};
}
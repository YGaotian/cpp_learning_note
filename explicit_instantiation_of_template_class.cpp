#include "header_learning.h"
#include "class_template_learning.hpp"
#include "function_template_explicit_instantiation.hpp"

//因为类模板仅在代码中出现对该模板类的使用的时候，才会被实例化，而每个编译单元都是互相独立的，互相不会看见对方的内容
    //也就是说，在a.cpp中如果实例化了MyTemplateClassA<int>，在b.cpp中是看不到的，就会再次实例化一遍
    //如果有成百上千个cpp文件，有许许多多的对MyTemplateClassA<int>的实例化，必定会引起庞大的开销，所以我们可以对我们所需版本的类模板进行显式实例化
    //这样，只需要一个cpp文件里对它进行显式实例化定义，其余的cpp文件只要对它进行显式实例化声明即可
extern template class MyTemplateClassA<double>;    //这里是显式实例化的声明，应写在所有需要的.cpp文件的开头，定义部分在the_definition_part_of_explicit_instantiation.cpp内
extern template class MyTemplateClassA<int>;    //这里是显式实例化声明了一个int版本的类模板，int版本的定义在前一节the_template_function_in_template_class.cpp中，是隐式实例化的
extern template class MyTemplateClassA<long>;   //这里显式实例化声明了一个long版本的类模板，然而在任何地方都不存在long版本的显式实例化定义，所以下面long版本的tmpClsD无法正常调用，会报错
//但是可以在本文件内直接显式实例化定义一个类模板，就不用再声明了，比如像下面一行这样
//template class MyTemplateClassA<long>;

//如果是显式实例化定义函数模板，则是template 返回类型 函数名(类型 形参); 比如 template void funcA(double x);
//显式实例化声明和类模板类似，也是在前面再加一个extern
extern template void explicit_instantiation_of_function_template(int i);    //此处是函数模板的显式实例化声明，显式实例化定义在the_definition_part_of_explicit_instantiation.cpp中



void explicit_instantiation_of_template_class()
{
    MyTemplateClassA<double> tmpClsB;
    tmpClsB.tmplFunc(33.3f);
    // MyTemplateClassA<int> tmpClsC;
    // tmpClsC.tmplFunc(242);
    //报错，尽管有对 template class MyTemplateClassA<long> 的声明，但是仍无法执行下列代码，因为任何cpp文件内都没有它的定义
    //MyTemplateClassA<long> tmpClsD;
    //tmpClsD.tmplFunc(300);

    //使用显式实例化的函数模板   
    explicit_instantiation_of_function_template(545);
}
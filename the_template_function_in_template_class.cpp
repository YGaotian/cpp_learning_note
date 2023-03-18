#include "class_template_learning.hpp"
#include "header_learning.h"

void the_template_function_in_template_class()
{
    MyTemplateClassA<int> tmpClsA;
    tmpClsA.tmplFunc(29);   //调用类模板的模板函数
    //类模板的普通成员函数和成员函数模板都是只有为程序所用（代码中出现了对普通成员函数或成员函数模板的调用）的时候才实例化
}
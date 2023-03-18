#include "header_learning.h"

//如果我们想要创建一个变量，类型是std::map<int, 任何想要的类型>，我们也可以创建一个模板来实现，我们称之为模板别名
template<typename T>
using map_int_t = std::map<int, T>;

//再来一个
template<typename T1>
using str_func_pointer = void(*)(T1);

void saySth(std::string str)
{
    std::cout << str << std::endl;
}

void template_alias()
{
    map_int_t<std::string> int_str_map;
    int_str_map.insert({5, "hello"});
    std::cout << int_str_map.at(5) << std::endl;

    str_func_pointer<std::string> sfp = &saySth;
    sfp("something");
}

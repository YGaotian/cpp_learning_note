#include "header_learning.h"

//对于模板来说，模板的参数也可以是一个模板，但是模板定义时模板参数的写法要改变
template<typename T,
         template<class> class Container>    //还可以写另一种，个人感觉容易理解，但是比较长 template<typename U> typename Container
class MyTemplateTemplateParamClass          // 意思就是有第二个参数Container，所以是typename Container，然后这个参数是个模板，所以要在最前面加上template<typename U>
{
public:
    MyTemplateTemplateParamClass()
    {
        for (int i = 0; i < 10; ++i)
            m_iiiii.push_back(i);
    }

public:
    Container<T> m_iiiii;
};

//定义一个模板别名
template<typename T> using Vec_Alias = std::vector<T>;

void template_template_parameter()
{
    //MyTemplateTemplateParamClass<int, std::vector> 无法通过编译，报错提示类模板std::vector与模板参数Container不兼容，就是说编译器无法识别，所以要定义一个模板别名
    MyTemplateTemplateParamClass<int, Vec_Alias> mttpc_1;
    for (auto i : mttpc_1.m_iiiii)
        std::cout << i << std::endl;
}
#include "header_learning.h"
#include <functional>
#include <algorithm>

class Functor4Bind
{
public:
    bool operator()(int i, int j)
    {
        return i < j;
    }
};

void stlAdaptor_learning()
{
    //adaptor适配器有很多种，它的意思就是将一个东西通过某种手段适当改造，使它的行为看起来像另外一种东西，就像一个转换器一样
    //比如容器适配器，将一个双端队列deque的一端封死，就变成了一个堆栈stack，如果将deque的方向改为单向，就变成了一个单向队列queue

    //算法适配器，也叫做绑定器binder
    //在老版本的c++ stl中，有bind1st，bind2nd这两个算法适配器，从c++ 11开始，这两个东西变成了同一个算法适配器，函数模板std::bind<>
    std::vector<int> intVec4Bind = { 13, 11, 23, 25, 32, 89, 877, 65 };
    //此处想统计这一个容器中大于40的元素的个数，可以使用count_if，将一个自定义的函数对象塞进去作为计数规则
    Functor4Bind f4b;
    //std::bind中，第一个参数是可调用对象，之后是一个要绑定的参数列表，可以绑定一个或多个参数，绑定参数的意思就是将可调用对象的参数用已确定的值代替
    //这样的话就不需要在调用可调用对象的时候传入与形参数量相等个数的实参，此处的例子中，就可以将需要传入2个参数的可调用对象适配成一个在调用时只需要传递1个参数的可调用对象
    //未绑定参数就是在调用时仍然需要传入对应实参的形参，在std::bind中，根据需要传递的实参个数，依次使用命名空间 std::placeholders 的占位符 _1, _2, _3... 替换
    //总结上述，此处的std::bind就返回了一个全新的一元谓词
    auto n = std::count_if(intVec4Bind.begin(), intVec4Bind.end(), std::bind(f4b, 40, std::placeholders::_1));
    std::cout << "在这个vector容器中有 " << n << " 个元素是大于40的" << std::endl;

    //迭代器适配器：反向迭代器也是一种适配器
}
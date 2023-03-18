#include "header_learning.h"
#include <algorithm>

void addOne(int& i)
{
    ++i;
}

void printElement(int i)
{
    std::cout << i << std::endl;
}

bool sortRule(int i, int j)
{
    return i > j;
}

void stlAlgorithm_learning()
{
    //stl算法是与迭代器配合使用的全局函数，它们是与迭代器相关，与容器无关的，但是某些数据结构的迭代器与算法之间的兼容性不是很好
    //算法遇到不同种类的迭代器，在内部会有不同的处理方式
    std::vector<int> intVec4Algorithm = { 1, 22, 25, 55, 78 ,13, 18, 33, 6};
    //find算法可以用迭代器指定区间，如果找到元素，则返回首个满足条件的元素的迭代器，否则返回区间右端的迭代器
    auto elementWanted = std::find(intVec4Algorithm.begin(), intVec4Algorithm.begin() + 3, 100);
    if (elementWanted == intVec4Algorithm.begin() + 3)
    {
        std::cout << "没有元素：400\n" << std::endl;
    }

    //find_if可以从给定的起始位置开始向给定的结束位置执行可调用表达式，按照可调用表达式中所写的规则查找，所以这个可调用表达式的返回值类型必须是bool，如果返回true，则表示找到，否则返回false
    //上述的这样一个可调用表达式称之为谓词，具体地重新说一遍，谓词就是一个可调用表达式，它的返回结果是一个可以用作条件的值，标准库算法所使用的谓词可分为两类，即一元谓词与二元谓词
    //一元谓词就是只接受一个参数的可调用表达式，二元谓词则是接受两个参数的可调用表达式，find_if所接受的是个一元谓词，所以如果可调用表达式中多传了参数就会报错
    //然后find_if返回第一个满足条件的元素的迭代器，否则返回一个指向给定的结束位置的迭代器，注意此处的可调用对象不能修改传入的参数，也就是说传入的参数不能是引用类型，但这么做似乎不会报错
    auto result = std::find_if(intVec4Algorithm.begin(), intVec4Algorithm.begin() + 3, [](int value)
        {
            if (value == 25)
            {
                return true;
            }
            return false;
        });
    if (result != intVec4Algorithm.begin() + 3)
        addOne(*result);
    //for_each算法可以指定起始位置与结束位置，在这个区间内对每个迭代器所指的元素执行一个指定的函数
    std::for_each(intVec4Algorithm.begin(), intVec4Algorithm.end(), printElement);
    std::cout << std::endl;

    //sort算法可以帮助我们为一窜元素进行排序，我们可以使用默认的排序方法，从小到大排，也可以自己写一个函数作为自定义规则进行排序，注意这个函数的返回类型必须是bool
    std::sort(intVec4Algorithm.begin(), intVec4Algorithm.end(), sortRule);
    std::for_each(intVec4Algorithm.begin(), intVec4Algorithm.end(), printElement);
    std::cout << std::endl;

    //有些容器不支持全局的sort方法，但是提供了自己的sort
    std::list<int> li = { 1, 3, 5, 2, 4, 6 };
    //std::sort(li.begin(), li.end());  报错
    li.sort(sortRule);
    std::for_each(li.begin(), li.end(), printElement);
}
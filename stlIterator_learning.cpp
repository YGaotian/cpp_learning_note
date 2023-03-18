#include "header_learning.h"

void display(std::output_iterator_tag cate)
{
    std::cout << "output" << std::endl;
}

void display(std::input_iterator_tag cate)
{
    std::cout << "input" << std::endl;
}

void display(std::forward_iterator_tag cate)
{
    std::cout << "forward" << std::endl;
}

void display(std::bidirectional_iterator_tag cate)
{
    std::cout << "bidirectional" << std::endl;
}

void display(std::random_access_iterator_tag cate)
{
    std::cout << "random_access" << std::endl;
}

//通过过滤器（萃取机）将迭代器的种类提取出来并打印的函数
template <typename T>
void display_category(T iter)
{
    typename std::iterator_traits<T>::iterator_category cate;   //这一整个类型就是萃取机，可以直接提取出迭代器的种类
    display(cate);
}

void stlIterator_learning()
{
    //迭代器是有不同的种类的，它们由容器提供
    //迭代器的每个分类都对应了一个结构，这些结构定义在std命名空间中，放在头文件xutility中
    //分类迭代器的依据是每个迭代器能做的操作和移动的特性，迭代器可分为如下几种：
    struct std::output_iterator_tag;           //输出型迭代器，拥有将值写入指定位置（赋值）的能力，支持前置/后置递增（步进）
    struct std::input_iterator_tag;            //输入型迭代器，可以一个一个地读取容器中的元素，支持前置/后置递增，可以与其他的迭代器进行是否相等的判断
    struct std::forward_iterator_tag;          //前向迭代器，在输入型迭代器的基础之上，增加了赋值操作
    struct std::bidirectional_iterator_tag;    //双向迭代器，在前向迭代器的基础上，可以以相反的方向迭代容器
    struct std::random_access_iterator_tag;    //随机访问迭代器，在双向迭代器的基础上，新增了随机访问的能力
                                               //   就是从当前或指定的位置，前进/后退n个元素（iter + n / iter -= n），或是通过索引访问元素（iter[n]）
                                               //   还可以返回两个迭代器之间的距离（iter2 - iter1），或是比较iter1是否在或不在iter2之前/之后（> / >= / < / <=）

    //可以通过代码将每一种容器的迭代器的种类打印出来
    std::vector<std::string>::iterator itv;
    std::list<int>::iterator itl;
    display_category(itv);
    display_category(itl);
}
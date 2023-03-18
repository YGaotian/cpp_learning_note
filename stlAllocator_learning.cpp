#include "header_learning.h"

void stlAllocator_learning()
{
    //分配器也是一个类模板，它和容器结合使用，它是内存的分配器，可以扮演内存池的角色，以减少单纯的多次malloc对内存的浪费，也提高了分配效率
    std::list<int, std::allocator<int>> intList;    //等价于std::list<int>
    //根据stlContainer_learning.cpp一节可知，list的元素的内存是不连续的，所以由此也可以判断，当前c++标准库中的list容器的缺省的分配器并没有使用内存池技术

    //从语法上来讲，我们可以直接使用allocator，但是在实际开发中，allocator通常只用于容器，且极少被手动地显式使用，下面仅作演示
    std::allocator<int> intAlloc;   //创建了一个可以分配int类型对象的内存的分配器
    int* p = intAlloc.allocate(3);  //分配了未被构造的内存，这一块内存的大小可以存下3个int，即12个字节
    for (int pos = 0; pos != 3; pos++)
    {
        p[pos] = (pos + 1) * 2;
    }
    for (int pos = 0; pos != 3; pos++)
    {
        std::cout << p[pos] << std::endl;
    }
    //使用完的内存要释放
    intAlloc.deallocate(p, 3);  //传入指针，以及要释放内存的对象的数量，这个数字应该与分配内存时的数字一样，多了或者少了都可能引起程序崩溃
}
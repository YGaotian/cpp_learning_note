#include "header_learning.h"
#include <deque>
#include <queue>
#include <unordered_set>
#include <forward_list>

class ContainerTestClass
{
public:
    int mi;
    ContainerTestClass(int miarg)
    {
        mi = miarg;
        std::cout << "ContainerTestClass is running, init:" << mi << std::endl;
    }
    ContainerTestClass(const ContainerTestClass& vt)
    {
        mi = vt.mi;
        std::cout << "copy constructor is running" << std::endl;
    }
    ~ContainerTestClass()
    {
        std::cout << "destroy:" << mi << std::endl;
    }
};

//vector 实验函数
void vector_learning()
{
    //从下面的例子可以看出，vector每多一个元素，就会增加一次拷贝构造的调用
    //这是因为vector容器有一个空间的概念，每次push back的时候，空间会不足，所以就会生成一个新的空间，这个空间的大小可以存放已有的元素和新增的元素
    //那么vector就会把原先的vector元素逐一拷贝到新的空间中去，并将新增元素也放进这个空间，然后逐一析构原先的vector元素，所以会调用多次拷贝与析构
    std::vector<ContainerTestClass> ctcvec = {ContainerTestClass(111), ContainerTestClass(222)};
    std::cout << "size = " << ctcvec.size() << std::endl;
    std::cout << "capacity = " << ctcvec.capacity() << std::endl;
    std::cout << std::endl;
    ContainerTestClass ctcInV_1(0);
    ctcvec.push_back(ctcInV_1);
    std::cout << "size = " << ctcvec.size() << std::endl;
    std::cout << "capacity = " << ctcvec.capacity() << std::endl;
    std::cout << std::endl;
    ContainerTestClass ctcInV_2(1);
    ctcvec.push_back(ctcInV_2);
    std::cout << "size = " << ctcvec.size() << std::endl;
    std::cout << "capacity = " << ctcvec.capacity() << std::endl;
    std::cout << std::endl;
    ContainerTestClass ctcInV_3(2);
    ctcvec.push_back(ctcInV_3);
    std::cout << "size = " << ctcvec.size() << std::endl;
    std::cout << "capacity = " << ctcvec.capacity() << std::endl;
    std::cout << std::endl;
    ContainerTestClass ctcInV_4(3);
    ctcvec.push_back(ctcInV_4);
    std::cout << "size = " << ctcvec.size() << std::endl;
    std::cout << "capacity = " << ctcvec.capacity() << std::endl;
    std::cout << std::endl;
    //上面的代码中，size表示当前容器中的元素数量，capacity表示的是空间大小，就是说可以容纳多少元素的大小
    //capacity一定不会比size小，一般会与size相等，但是如果经常向容器中添加元素，那么capacity会智能地变成一个合适的，大于size的数，以避免频繁地发生空间不够的现象
    int count = 0;
    for (auto iter = ctcvec.begin(); iter != ctcvec.end(); iter++)
    {
        if (count == 3)
        {
            std::cout << "erase: " << iter->mi << std::endl;
            ctcvec.erase(iter);
            std::cout << "erased!" << std::endl;
            break;
        }
        count++;
    }
    for (int n = 0; n != 5; n++)
    {
        std::cout << "当前元素 " << ctcvec[n].mi << " 的地址为：" << &ctcvec[n] << std::endl;
    }
    std::cout << std::endl;
    //从上面的代码中可以知道，vector在删除元素的时候，并不会对所有元素逐一调用拷贝和析构函数
    //如果是从vector中间删除的某一个元素的话，后面的元素会直接向前移动一个位置，使内存连续

    //如果要从vector中间插入元素，那么也会导致多次调用元素对应的类型的拷贝与析构函数，但可能会少几次调用，因为vector会有内部的优化处理
    //为了最大程度地提高vector的运行效率，如果我们能提前决定capacity的大小，那么我们就可以手动地事先设置capacity，这样后续增加元素也不会调用多次拷贝与析构
    std::cout << "\n" << std::endl;
    ctcvec.reserve(10);
    std::cout << "\n使用了reverse" << std::endl;
    for (int k = 0; k < 3; k++)
    {
        std::cout << "插入" << k << std::endl;
        ctcvec.push_back(ContainerTestClass(k));
    }
    std::cout << std::endl; 
    for (auto it = ctcvec.begin(); it != ctcvec.end(); it++)
    {
        std::cout << "ctcvec里有元素：" << it->mi << std::endl;
    }
    std::cout << std::endl;
}
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//deque容器是两端开口的队列，可以从两头插入元素，它的元素是分段连续的，也就是说，以每几个元素为一组，它们的内存地址是连续的，每组元素之间是不连续的
void deque_learning()
{
    std::deque<ContainerTestClass> ctcdeq = {};
    for (int a = 0; a < 5; ++a)
    {
        ctcdeq.push_back(ContainerTestClass(a));
    }
    for (int b = 0; b < 5; ++b)
    {
        ctcdeq.push_front(ContainerTestClass(b * 11));
    }

    //print
    for (auto iter = ctcdeq.begin(); iter != ctcdeq.end(); ++iter)
    {
        std::cout << iter->mi << " in ctcdeq is located on: " << &*iter << std::endl;
    }
    std::cout << std::endl;
}
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//与deque类似的还有一个容器，stack，它的元素是后进先出，不能从中间插入元素，deque实际上也包含着stack的功能

//queue是单向的队列，也就是说只能从一端插入元素，它的元素是先进先出的，也是分段连续的，同样，deque也包含了queue的功能
void queue_learning()
{
    std::queue<ContainerTestClass> ctcque = {};
    for (int in = 0; in < 18; in++)
    {
        ctcque.push(ContainerTestClass(in));
    }
    //queue没有迭代器
    for (int o = 0; o < 18; ++o)
    {
        std::cout << ctcque.front().mi << "  所属实例的地址为 " << &(ctcque.front()) << std::endl;
        ctcque.pop();
    }
    std::cout << ctcque.size() << std::endl;
    std::cout << std::endl;
}
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//list是双向链表，内存是不连续的
//list与vector的区别是，list在任意位置插入数据的效率很高，因为不用拷贝生成新的容器
//而vector因为内存是连续的，所以不行，而且当内存不够时，vector需要找一块新的空间，将原来的元素拷贝到新的vector中，然后析构原来的vector，而list不用
//但由于vector内存连续，它的随机访问非常高效，根据第一个元素的地址，可以一下子计算出第任意个元素的地址，list则无法实现
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//forward_list是单向链表，也称为受限链表，它对比起双向链表，少了一个方向的指针，所以向前访问就不方便了，但是也因此能节省一个指针对象的内存空间
void forwardlist_learning()
{
    std::forward_list<ContainerTestClass> ctcflist = {};
    for (int i = 0; i < 10; i++)
    {
        //forward_list只能向头部插入新元素
        ctcflist.push_front(ContainerTestClass(i));
    }
    for (auto iter = ctcflist.begin(); iter != ctcflist.end(); iter++)
    {
        std::cout << iter->mi << " 所属实例的地址为 " << &*iter << std::endl;
    }
    //同样，也只能从头部pop元素
    ctcflist.pop_front();
    std::cout << "now ctcflist's front element's mi is: " << ctcflist.front().mi << std::endl;
}
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//set与map，是关联容器，多数是用红黑树作为内部的数据结构实现的，在这种容器中插入数据，不需要手动指定插入位置，它会根据内部的算法自动选一个位置插入元素，因此插入数据的速度可能略慢
//map的每个元素是一个键值对，每个key是不能相同的，如果一定要将相同的key存入map，我们可以使用multimap来代替普通的map，通过key找value很高效
//而set只有value，没有key，容器内没有重复的元素，如果要存入相同元素，可以使用multiset
void map_learning()
{
    std::map<char, std::string> strmap;
    //我们可以使用模板函数make_pair来生成键值对
    strmap.insert(std::make_pair('a', std::string("hello")));
    //也可以直接按传统的方法，初始化一个pair模板类实例对象
    strmap.insert(std::pair<char, std::string>('b', "world"));
    //可以像下面这样去遍历，iter.end()返回的是容器的最后一个元素之后的地址，也就是超尾
    /// for (auto iter = strmap.begin(); iter != strmap.end(); iter++)
    //也可以直接使用find方法来遍历容器，成员函数find()用来查找第一个“拥有某key”的元素，并返回一个指向该位置的迭代器，如果没找到这样的元素，就返回容器的end()
    //无法用find()查找拥有某特定value的元素，必须改用STL算法如find_if()，或干脆自行写一个循环
    auto iter = strmap.find('b');
    if (iter != strmap.end())
    {
        //first返回当前元素的key，相对地，想要返回当前元素的value可以用second
        std::cout << iter->first << std::endl;
    }
    strmap.insert(std::make_pair('b', "earth"));
    std::cout << strmap.find('b')->second << std::endl;
    //从上面可以看出，对普通的map重复insert具有相同key的值是无效的，第一次之后的所有重复insert的操作都会被忽略
}
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//老版本的c++有hash_map，hase_set，hash_multimap，hash_multiset
//新版本已经不推荐使用了，取而代之的是将hash_前缀改为unordered_前缀的容器，它们是无序容器，不难看出它们内部使用的数据结构是hash表
//这种容器插入数据的时候也不需要人工手动干预，会自动选择合适的位置进行插入

//unordered_set的bucket会根据情况自动扩容，bucket的数量不会少于元素的数量，当元素的数量要超过bucket的时候，bucket就会自动扩容
void unorderedSet_learning()
{
    std::unordered_set<int> uoset = {};
    std::cout <<"bucket count: " << uoset.bucket_count() << std::endl;
    for (int i = 0; i < 10; i++)
    {
        uoset.insert(i);
        std::cout << "insert: " << i << std::endl;
        std::cout <<"bucket count: " << uoset.bucket_count() << std::endl;
    }
    std::cout <<"该容器最大能容纳的bucket数量" << uoset.max_bucket_count() << std::endl;
    for (int n = 0; n < uoset.bucket_count(); n++)
    {
        std::cout << "bucket" << n << " has " << uoset.bucket_size(n) << " elements." << std::endl;
    }
    auto findresult = uoset.find(7);    //由于查找比较费时，所以当容器提供了自己的find方法时，应尽量使用它，因为特定的find效率会相对更高，如果没有，再使用全局的find
    if (findresult != uoset.end())
    {
        std::cout << "element '7' is found." << std::endl;
    }
    //全局find的使用方法演示
    if (find(uoset.begin(), uoset.end(), 12) == uoset.end())
    {
        std::cout << "element '12' is not found" << std::endl;
    }
}



//本节主调函数
void stlContainer_learning()
{
    std::cout << "///////vector learning:" << std::endl;
    vector_learning();

    std::cout << "\n\n\n///////deque learning:" << std::endl;
    deque_learning();

    std::cout << "\n\n\n///////queue learning:" << std::endl;
    queue_learning();

    std::cout << "\n\n\n///////forwardlist learning:" << std::endl;
    forwardlist_learning();

    std::cout << "\n\n\n///////map learning:" << std::endl;
    map_learning();

    std::cout << "\n\n\n///////unordered_set learning:" << std::endl;
    unorderedSet_learning();


}
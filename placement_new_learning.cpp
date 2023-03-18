#include "header_learning.h"
#include <iostream>

// placement new 也叫定位 new，可以在已经分配的内存中初始化一个对象，也就是调用一个对象的构造函数，与传统的 new
// 不同的是，它并不会分配内存

class PlacementNewTestClass
{
public:
    PlacementNewTestClass()
    {
        std::cout << "默认构造函数调用" << std::endl;
        m_pntcINT = 10;
    }

    PlacementNewTestClass(int num)
    {
        std::cout << "有参构造函数调用" << std::endl;
        m_pntcINT = num;
    }

    ~PlacementNewTestClass()
    {
        std::cout << "析构函数调用" << std::endl;
    }

public:
    int m_pntcINT;

public:
    //我们可以重载定位new，当然，不重载也是可以的，这里只是演示一下写法
    //定位new的重载与普通的new的重载是几乎一样的，只是接收的参数还要加一个已经分配好的内存的地址
    //然后返回的是已经接收到的，之前就分配好的内存的地址，在重载的new中并不需要分配内存
    static void* operator new(size_t size, void* ptr)
    {
        std::cout << "override placement new" << std::endl;
        return ptr;
    }
};



//我们还可以自定义自己的new运算符，除了placement new和传统的new会调用构造函数，其余的我们自定义的new不会自动调用构造函数
//我们自定义的new可以不返回任何有效地址，它返回的是nullptr，也就是说，并不会分配内存
//以下这个类是用来演示自定义的new的
class OverrideMyOwnNewClass
{
public:
    OverrideMyOwnNewClass()
    {
        std::cout << "默认构造函数，该函数在自定义的new中是不会被自动调用的" << std::endl;
    }

public:
    //new运算符的第一个参数总是size_t类型的，在调用new时会自动传入实参
    //再之后的参数根据情况，如果是placement new，就需要接收指针
    //如果是传统new，就什么参数也没有，只要使用malloc，然后最后会返回地址即可
    //如果是自定义的new，甚至不想要分配内存，那就可以随便写参数类型，最后返回空指针即可
    static void* operator new(size_t size, int a, int b)
    {
        std::cout << "Custom new operator" << std::endl;
        std::cout << a + b << std::endl;
        return nullptr;
    }
};



void placement_new_learning()
{
    void *ptr4placementNew = (void *)new char[sizeof(PlacementNewTestClass)];
    std::cout << "开辟内存中" << std::endl;
    std::cout << "内存开辟成功，地址为：" << ptr4placementNew << std::endl;
    PlacementNewTestClass* pntc_1 = new (ptr4placementNew) PlacementNewTestClass(123); 
    std::cout << "开辟完成" << std::endl;
    std::cout << pntc_1->m_pntcINT << std::endl;
    std::cout << "初始化了地址：" << pntc_1 << std::endl;
    //delete pntc_1;   //定位new可以用普通的delete来释放，推荐使用这种方法
    pntc_1->~PlacementNewTestClass();
    delete [] (void*)pntc_1;
    /// /////////////////////////////////////////////////////////////////////////////////////

    //此处并不会自动调用OverrideMyOwnNewClass的构造函数
    OverrideMyOwnNewClass* omonc_1 = new(123, 345) OverrideMyOwnNewClass();
}
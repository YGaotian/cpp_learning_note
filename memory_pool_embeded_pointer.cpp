#include "header_learning.h"

/*----------------------------------------------------------------------------------------------------------------------
内存池中需要有一个next指针指向下一个内存块，但是这个指针占了8个字节（64位操作系统VS2022环境），我们可以继续优化，使用嵌入式指针以节省这个浪费
嵌入式指针的工作原理是借用每一块被开辟出来的该类空闲内存的前8个字节，链接住后面空闲的内存块，所以类对象本身的 sizeof 结果不能小于8个字节
一旦某一块内存被分配出去了，那么这个块的前4个字节就不需要再被保留了，此时这4个字节就可以正常使用，用来保存其他的数据
----------------------------------------------------------------------------------------------------------------------*/

//内存池类
class EmbededPtrMemoryPool
{
public:
    void* allocate(size_t size)
    {
        obj* tmpptr;
        if (m_freePos == nullptr)   //如果还没有开辟内存，就申请一大块内存
        {
            std::cout << "create a new memory group" << std::endl;
            size_t newSize = size * m_trunkCount;     //一块大小为本类的 m_trunkCount 倍的字节数
            m_freePos = (obj*)malloc(newSize);        //开辟newSize个字节的内存空间，转为嵌入式指针类型，并让 m_freePos 指向该片内存
            tmpptr = m_freePos;                       //tmpptr 与 m_freePos指向同一个对象的内存，所以后续对 tmpptr 的任何操作就等同于对 m_freePos 的操作
            //将创建出来的内存块链接在一起
            for (int i = 0; i < m_trunkCount - 1; ++i)
            {
                tmpptr->next = (obj*)((char*)tmpptr + size);
                tmpptr = tmpptr->next;  //每次循环tmpptr都向后偏移一个内存块
            }
            tmpptr->next = nullptr;    //经过上面的循环，此时 tmpptr 已经偏移到最后一个内存块了，最后一个内存块的 next 是空指针
        }
        //如果已经开辟过内存，就令 tmpptr 指向最靠前的一块空内存
        tmpptr = m_freePos;             //如果是第一次开辟内存，此时 tmpptr 的指向就被重置到第一个内存块
        m_freePos = m_freePos->next;    //m_freePos 指向这一次的 next，以便下一次 new 时使用
        return tmpptr;
    }

    void deallocate(void* ptr)
    {
        ((obj*)ptr)->next = m_freePos;
        std::cout << "the last empty memory block is:" << m_freePos << std::endl;
        m_freePos = (obj*)ptr;
        std::cout << "recycle " << m_freePos << std::endl;
    }

public:                 //这里应该是 private，但是为了下面的演示代码能够访问到 obj 结构类型，所以写成 public
    struct obj          //这个结构体只是声明在 EmbededPtrMemoryPool 类之内，相当于将这个类当做一个命名空间，它并不是 EmbededPtrMemoryPool 类的成员对象实体
    {                   //所以也就不会增加该类的 sizeof 大小
        obj* next;      //这是一个嵌入式指针
    };

private:
    int m_trunkCount = 5;       //每次分配5倍大小的该类内存
    obj* m_freePos = nullptr;   //指向空闲内存首地址的指针
};

//使用内存池的类
class MemoryPoolUser
{
public:
    //为了凑够8字节而定义的成员对象
    int m_i;
    int m_j;

public:
    static EmbededPtrMemoryPool MAllocator;    //静态成员声明

public:
    static void* operator new(size_t size)
    {
        return MAllocator.allocate(size);
    }

    static void operator delete(void* ptr)
    {
        MAllocator.deallocate(ptr);
    }
};
EmbededPtrMemoryPool  MemoryPoolUser::MAllocator;   //静态成员定义



void memory_pool_with_embeded_pointer()
{
    EmbededPtrMemoryPool epmp;
    std::cout << sizeof(epmp) << std::endl;
    EmbededPtrMemoryPool::obj* embededObj_ptr;
    embededObj_ptr = (EmbededPtrMemoryPool::obj*)&epmp;         //嵌入式指针embededObj_ptr指向了epmp的首地址
    std::cout << sizeof(embededObj_ptr->next) << std::endl;     //指针大小为8字节
    //因为next是obj结构体的第一个成员对象，地址与结构体的首地址重合，所以它的地址就是embededObj_ptr所指对象的首地址（即epmp的首地址），令它指向nullptr，就是将epmp对象的前8个字节置为零
    embededObj_ptr->next = nullptr;
    /// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    MemoryPoolUser* mpu_list[20];
    for (int i = 0; i < 15; ++i)
    {
        mpu_list[i] = new MemoryPoolUser();
        std::cout << mpu_list[i] << std::endl;
        //现在可以覆盖前8个字节的数据
        mpu_list[i]->m_i = 20;
        mpu_list[i]->m_j = 303;
        std::cout << "add result: " << mpu_list[i]->m_i + mpu_list[i]->m_j << std::endl;
    }
    for (int k = 0; k < 15; ++k)
    {
        delete mpu_list[k];
    }
    mpu_list[0] = new MemoryPoolUser();
    mpu_list[0]->m_j = 123;
    std::cout << "THE LATEST MPU'S M_J IS: " << mpu_list[0]->m_j << std::endl;
    delete mpu_list[0];
}
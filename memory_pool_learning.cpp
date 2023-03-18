#include "header_learning.h"

/*--------------------------------------------------------------------------------------------
频繁使用malloc开辟小块内存会造成巨大的资源浪费，可以用内存池来解决这个问题，因为内存池可以减少malloc调用的次数
减少malloc的调用次数，程序的运行效率也会有一定的提升，尽管提升并不会很明显
内存池的实现原理：
    一次性申请一大块内存，之后要用的时候一点一点从申请好的内存中分配出来，当这些内存都用得差不多的时候，如果还需
    要用，就再申请一大块内存，以减少malloc的调用次数
--------------------------------------------------------------------------------------------*/

//内存池类
class ExperimentalMemoryPool
{
public:
    //重载new与delete实现内存池操作
    static void* operator new(size_t size);
    static void operator delete(void* ptr);

public:
    static int m_countNew;  //记录 new 的调用次数
    static int m_countMalloc;   //记录 malloc 的调用次数，因为不需要每次 new 都调用一次 malloc

private:
    ExperimentalMemoryPool* next;
    static ExperimentalMemoryPool* m_freePos;   //指向空闲内存首地址的指针
    static int m_trunkCount;    //每 new 一次可以分配的该类内存的倍数，这个数字越大，需要调用 malloc 的次数就越少，但如果该数字过大了也不合适
};

//类成员初始定义
int ExperimentalMemoryPool::m_countNew = 0;
int ExperimentalMemoryPool::m_countMalloc = 0;
ExperimentalMemoryPool* ExperimentalMemoryPool::m_freePos = nullptr;
int ExperimentalMemoryPool::m_trunkCount = 5;   //每次 new 分配5倍该类的大小作为内存池大小

//类成员new运算符实现
void* ExperimentalMemoryPool::operator new(size_t size)
{
    //一个临时的指针，这个指针最后会被return
    ExperimentalMemoryPool* tmpptr;
    if (m_freePos == nullptr)
    {
        //如果还没有开辟内存，就申请一大块内存
        size_t newSize = size * m_trunkCount;   //一块大小为本类的 m_trunkCount 倍的字节数
        //可以不用 malloc，而是用系统本身的 new 来申请内存，注意这个 new 不是我们重载的 new
        m_freePos = reinterpret_cast<ExperimentalMemoryPool*>(new char[newSize]);   //char 是一个字节，所以 char[newSize] 就是 newSize 个字节
        tmpptr = m_freePos; //tmpptr与m_freePos指向同一个对象的内存，所以后续对tmpptr的任何操作就等同于对m_freePos的操作
        //将创建出来的内存块链接在一起
        for (; tmpptr != &m_freePos[m_trunkCount - 1]; ++tmpptr)    //++使得tmpptr的指向每次在循环中向后偏移一次
        {
            tmpptr->next = tmpptr + 1;
        }
        //经过上面的循环，此时tmpptr已经偏移到最后一个内存块了，最后一个内存块的next是空指针
        tmpptr->next = nullptr;
        ++m_countMalloc;    //malloc计数
    }
    //如果已经开辟过内存，就令tmpptr指向最靠前的一块空内存
    tmpptr = m_freePos;    //如果是第一次开辟内存，此时tmpptr的指向就被重置到第一个内存块
    //m_freePos指向这一次的next，以便下一次new时使用
    m_freePos = m_freePos->next;
    ++m_countNew;    //new计数
    return tmpptr;
}
//类成员delete运算符实现
void ExperimentalMemoryPool::operator delete(void* ptr)
{
    //令所要释放的内存块的next指向最新的空闲内存块
    (static_cast<ExperimentalMemoryPool*>(ptr))->next = m_freePos;
    //令此时指向空闲内存块的指针指向本次所要释放的内存块，这样下次new的时候，就会new在本次所要释放的内存块上，覆盖本次的数据
    //而由于本次内存块的next指向链表尾部的空闲内存块，于是下下次new的时候会继续在链表尾部的空闲内存块上写入数据
    m_freePos = static_cast<ExperimentalMemoryPool*>(ptr);
    /*----------------------------------------------------------------------------------------------------------------
    这里释放内存的代码实际上并没有真的把内存归还给系统，而是继续掌握着这些内存块，留给之后用，如果此时就真的要把这些内存块还给系统，是很麻烦的
    然而只要这些内存块是可以被我们的内存池控制的，就算没有真的释放内存，也不算内存泄漏
    如果之后绝对不会再需要使用内存池了（比如程序即将退出），这时候可以真正地释放掉内存
    但程序退出后所有泄漏的内存都会被操作系统释放，那么此时真的有必要释放内存吗
    通常，操作系统将回收内存，所以不必对其进行回收。但这确实是一个好习惯，并且在某些情况下，它可能会有所作为
    比如将一个程序作为另一个进程的子进程执行，直到父级完成，才可以释放内存。如果父级从未完成，那将是永久性的泄漏
    ----------------------------------------------------------------------------------------------------------------*/
}



void memory_pool_learning()
{
    ExperimentalMemoryPool* emp_1_ptr = new ExperimentalMemoryPool;
    ExperimentalMemoryPool* emp_2_ptr = new ExperimentalMemoryPool;
    delete emp_1_ptr;
    delete emp_2_ptr;
    emp_1_ptr = new ExperimentalMemoryPool;
    for (int i = 0; i < 200; ++i)
    {
        ExperimentalMemoryPool* emp_loop_ptr = new ExperimentalMemoryPool;
        delete emp_loop_ptr;
    }
    std::cout << ExperimentalMemoryPool::m_countMalloc << std::endl;
    std::cout << ExperimentalMemoryPool::m_countNew << std::endl;

}
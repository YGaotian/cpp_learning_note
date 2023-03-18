#include "header_learning.h"

/*---------------------------------------------------------------------------------------------------------------------------------------
    当我们new一个自定义的类对象时，会首先调用 operator new()，然后根据对象的大小调用malloc分配内存，再调用构造函数
如果构造函数是编译器自动合成的，当我们用的是不带括号的 new CLASSNAME，那成员对象存储的则是随机的数据，并没有被初始化
如果我们使用了 new CLASSNAME()，则编译器会帮我们将对象成员所含的随机数据默认清零，但如果我们为类添加了自定义的默认构造函数，那么就会按照我们定义好的行为去执行
    当我们delete一个自定义类对象的时候，delete不仅仅会调用free，还会在此之前先调用析构函数，然后调用 operator delete()，最后才是free
free是最后被调用的
    我们new出来的对象，占用的内存大小并不仅仅是相应类型的字节大小，在这块内存的前面还包含着记录这块内存有多大的数据，debug信息(程序的release版本可能没有这些信息)，
在这块内存的尾部记录着内存尾标记信息以及其他的一些必要信息等，如果new出来的东西是比较大的数组，那么总体占用的内存大小当然也会超过数组长度*数组类型对应的字节大小
在释放数组内存时，影响的也不仅仅是数组本身的内存大小，而是还包含着数组前后的一大片内存。所以说，如果开辟连续的内存，前后加一些额外的内存空间还算合理，但如果频繁地
开辟小块内存，每个小内存的前后都包含着额外的内存占用的话，就会造成巨大的浪费
---------------------------------------------------------------------------------------------------------------------------------------*/

//定义一个类，在这个类中要重载new和delete运算符
class OverrideNewAndDel
{
public:
    //new与delete运算符都不是跟着类对象的，而是属于类类型本身的，所以应该是static，这两个运算符的重载代码基本写法一般都是固定的
    static void* operator new(size_t size)   //new 的参数是要分配的内存大小，size_t是无符号整型的类型别名，new 运算符的返回值是个指针，所以返回类型是 void*
    {
        OverrideNewAndDel* onad = (OverrideNewAndDel*)malloc(size);
        std::cout << "override new called" << std::endl;
        return onad;
    }

    static void operator delete(void* ptr)  //delete 运算符的参数是要释放内存的指针，所以参数类型是 void*
    {
        std::cout << "override delete called" << std::endl;
        free(ptr);
    }
    //对于new数组和delete数组，需要重载专用的运算符 new[] 和 delete[]，但是除了这点不同，其他的和普通的new与delete的写法一模一样
    //并不需要在重载代码中写new几次，delete几次的操作，当我们调用 new[] 和 delete[] 的时候，会自动执行多次构造和析构函数，但new[]与delete[]只会执行一次
    //编译器能知道应该构造或析构几次的原因是我们在 new[N] 的时候传入了 N，它就是需要重复的次数，这个信息会与整个数组一起存储在的相邻地址中，所以整个对象的大小会比数组本身大小多出4个字节
};



//本节主调函数
void reacquaint_new_and_delete()
{
    OverrideNewAndDel* onadptr = new OverrideNewAndDel;
    delete onadptr;
    //如果我们有了重载的new和delete，却想调用默认的new和delete，我们可以加上作用域限定
    OverrideNewAndDel* op = ::new OverrideNewAndDel();
    ::delete op;
}
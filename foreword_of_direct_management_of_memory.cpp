#include "header_learning.h"

void foreword_of_direct_management_of_memory()
{
    //我们可以把auto和new放在一起使用
    int * ptr_int_1 = new int(222);
    auto ptr_int_2 = new auto(ptr_int_1);   //这里将ptr_int_1的类型自动推断了出来，并用ptr_int_1的初始化了ptr_int_2
    std::cout << ptr_int_2 << std::endl;    //是个地址，因为ptr_int_2是指向指针的指针
    //如果释放ptr_int_1，ptr_int_2也会被释放，因为它们指向了同一块内存
    //delete ptr_int_1;
    //但如果先释放ptr_int_2的话，ptr_int_1并不会被释放，所以还要再次手动释放一下ptr_int_1
    delete ptr_int_2;
    delete ptr_int_1;
    //一个好习惯：释放完内存的指针，可以指向空指针
    ptr_int_1 = nullptr;
    ptr_int_2 = nullptr;

    //以上对内存直接管理的方式，非常容易让人误操作，一旦忘记释放内存，或释放一个内存多次，程序都不会如期望的那样运行
    // 所以我们有新的指针工具来帮助程序员自动释放内存，那就是智能指针，请看后续章节
}
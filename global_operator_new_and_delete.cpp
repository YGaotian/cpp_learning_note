#include "header_learning.h"

#ifdef overloadNEWandDelete

void* operator new(size_t size)
{
    return malloc(size);
}

void* operator new[](size_t size)
{
    std::cout << "overloaded new[]" << std::endl;
    return malloc(size);
}

void operator delete(void* ptr) noexcept
{
    free(ptr);
}

void operator delete[](void* ptr) noexcept
{
    std::cout << "overloaded delete[]" << std::endl;
    free(ptr);
}
#endif


void override_global_operator_new_and_delete()
{ 
    int * aintarray = new int[3]{11, 22, 33};
    std::cout << aintarray[2] << std::endl;
    delete [] aintarray;
}
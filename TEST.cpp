#include "header_learning.h"
#include <future>
#include <thread>

class testref
{
public:
    testref() {}
    testref(const testref& tr)
    {
        std::cout << "copy called" << std::endl;
    }
    testref(testref&& trv) noexcept
    {
        std::cout << "move called" << std::endl;
    }
    //如果不加friend，这个运算符的重载就不能写在类定义里，要写在全局区，就是重载了全局的<<运算符，否则会报错
    friend std::ostream& operator<<(std::ostream& os, const testref&)
    {
        os << "testref received";
        return os;
    }
};

class threadFunctor
{
public:
    void operator()()
    {
        std::cout << "operator() is running" << std::endl;
    }

    threadFunctor() = default;
    threadFunctor(const threadFunctor&)
    {
        std::cout << "threadFunctor copied" << std::endl;
    }
    threadFunctor(const threadFunctor&&) noexcept
    {
        std::cout << "threadFunctor moved" << std::endl;
    }
};

void handlingtestref(testref& ir)
{
    std::cout << "working..." << std::endl;
    std::cout << ir << std::endl;
}

void test()
{
    testref tr;
    testref& trref = tr;
    testref* trptr = &tr;
    std::vector<testref> vin;
    std::cout << &std::ref(tr).get() << std::endl;
    std::cout << &tr << " " << &trref << std::endl;
    handlingtestref(std::ref(tr));
    threadFunctor tf;
    std::thread tfthread(std::move(tf));
    tfthread.join();
}
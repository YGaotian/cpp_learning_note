#include "header_learning.h"
#include <boost/type_index.hpp>

template <typename T>
void print_universal_ref(T&& arg)
{
    using namespace boost::typeindex;
    std::cout << "T  : " << type_id_with_cvr<T>().pretty_name() << std::endl;
    std::cout << "arg: " << type_id_with_cvr<decltype(arg)>().pretty_name() << std::endl;
}

void reference_collapsing()
{
    int exampleLValue = 10086;
    int& exampleLValueRef = exampleLValue;
    int&& exampleRValueRef = 136516;
    print_universal_ref(exampleLValue);
    print_universal_ref(exampleLValueRef);
    print_universal_ref(76797);
    print_universal_ref(exampleRValueRef);
    std::cout << std::endl;
    //左值引用&和右值引用&&是一种类型，但右值引用对象本身的类型是左值引用&
    //万能引用并不是一种类型，而是一种表示该函数的参数既可以接收左值或左值引用，也可以接收右值类型的标志，本质是来告诉编译器这个函数的参数是按引用传递的
    //当我们将左值或左值引用传给万能引用的时候，T会被推断为左值引用，所以T是xxx&，而作为万能引用的标志&&遇到T中的&就会发生折叠，则xxx& &&折叠成xxx&，于是arg被推断为xxx&类型
    //当我们将右值传给模板，T会被推断为左值类型，因为实际T&&就是右值引用，所以T是xxx，&&遇到xxx，就是xxx的右值引用类型，则arg被推断为xxx&&类型，这其中并没有发生引用折叠
    //如果传入右值引用，则实参本身是左值类型的，于是T会被推断为左值引用xxx&，同样，&&遇到T中的&变成了& &&，然后折叠成了&，即xxx& &&折叠为xxx&，所以arg被推断为xxx&类型

    //引用折叠规则，具体如下：
    //  当&&一旦遇到左值引用&，就会折叠成&，不管是& &&还是&& &，情况都一样
    //  只有&&遇到右值引用&&时，才会折叠成&&
    //  当&遇到&变成了& &，会折叠成&
    //一言以蔽之，就是当两个右值引用相遇时，会折叠成右值引用，除此之外任何引用相遇都会折叠成左值引用，引用相遇的情况也就是指出现了一个引用的引用
    //我们不能直接创建引用的引用，这是不合法的，但是在函数模板使用万能引用时的类型推导中，引用的引用会被推导出来，此时编译器就会使用引用折叠解决这个问题
    //不仅如此，我们还可以通过类型别名间接创建引用的引用，因此在这种情况下也会发生引用折叠，引用折叠规则是move之类的标准库设施可以正确工作的基础
}


template<typename F, typename Q>
void callerTemplate(F func, Q&& arg)
{
    std::cout << "original arg is: " << arg << std::endl;
    func(arg);
    std::cout << "then arg is: " << arg << std::endl;
}

void factoryFunc_1(int& ag)
{
    ag += 100;
}

void basic_forwarding()
{
    //转发的概念就是指我们创建一个函数模板，这个模板接受一个回调函数，函数模板将所接受的其他参数传入回调函数中，这个过程就是转发
    //如果我们的函数模板接收的参数是普通的值类型，我们的回调函数接收的参数也是值类型，那么一切都工作得很完美
    //而如果我们的回调函数接受参数的是引用，由于上述的函数模板并不按引用传值，那么就会导致回调函数并没有使用原本的实参，我们希望将原本的实参原封不动地转发给回调函数
    //因此，我们需要用到万能引用，它能够接受任何类型（左值/左值引用/右值）的参数，从而我们能得到并使用原始的数据
    int numericVariable = 2000;
    callerTemplate(factoryFunc_1, numericVariable);
    std::cout << std::endl;
}


//但是这样还不完美，因为如果factoryFunc的参数类型是右值引用，也就是说需要接收一个右值，那么当我们向callerTemplate传入右值时，实参到函数模板中会被推断为右值引用
//而在模板内部，参数再传给回调函数时，由于右值引用对象本身还是左值，就无法绑定到回调函数的右值引用类型的参数上去了
//因此，我们需要使用新的技术，即完美转发，这可以让我们的函数模板接受任意类型的实参，并将实参按原样转发给目标函数，其中的左值/右值/引用/const都不会被改变
//完美转发需要用到std::forward，它是专为转发而创造的函数模板，如果它接收到的参数本身原来是左值，它就返回左值，如果原来是右值，它就返回右值
//所以其实forward只对实参原本的类型是右值的情况有用
template<typename Ftype, typename Qtype>
void perfectCallerTemplate(Ftype func, Qtype&& arg)
{
    //使用完美转发forward，可将左值或右值原原本本地传入目标函数
    func(std::forward<Qtype>(arg));
    //打印一下arg看看，传入的参数类型经过普通的转发变成了左值
    ::print_universal_ref(arg);
    //打印一下经过forward完美转发的arg看看，发现它确实将传进来的参数的类型还原为了右值
    ::print_universal_ref(std::forward<Qtype>(arg));
}

void factoryFunc_2(int&& ag) 
{
    std::cout << "this function received a rvalue and now is working normally" << std::endl;
}

void perfect_forwarding()
{
    perfectCallerTemplate(factoryFunc_2, 90);
}



//本节主调函数
void reference_collapsing_and_perfect_forwarding()
{
    reference_collapsing();
    basic_forwarding();
    perfect_forwarding();
}
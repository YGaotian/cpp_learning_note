#include "header_learning.h"
#include "class_template_learning.hpp"

//除了在类模板的模板形参中需要，还有一些其他的场合也需要使用typename
// 比如说，当类声明中，如果有使用到typedef，那么typedef所定义的对象，就称之为类的类型成员
// 在class_template_learning一节中，我们在hpp文件里定义了一个MyList类的迭代器对象 MLIterator
// 它是由typedef所定义的，typedef T* MLIterator，那么这就是一个类型成员
// 不过我们还没有具体为这个迭代器对象写具体实现，那么现在下面开始写具体实现


template<typename T, int size>    //MLIterator是迭代器的类型，要写在前面，但是MLIterator是类中声明的，它是一个类型成员，所以也需要使用类名::来限定
MyList<T, size>::MLIterator MyList<T, size>::lstBegin()    
{                                                          	
    //但是光是使用类型::去限定类型成员有时是不够的，比如T::MLIterator，由于在编译期并不知道T到底是什么，所以无法确定T::MLIterator到底是类成员对象还是类的类型成员
    //如果是个类型，我们需要在开头加上typename，来告诉编译器MLIterator是一个类型成员，否则编译会失败
    typename T::MLIterator iter;
}


void occasion_to_use_typename()
{
    std::cout << "::除了用来访问普通类成员，类成员函数，还可以用来访问类中定义的类型成员。\n"
                << "在c++编译器中，一旦遇到::运算符，之后的对象会被默认地认为是类成员对象，\n"
                << "要使这个对象被理解为一个类型，就要用typename" << std::endl;
}
#include "header_learning.h"
#include <stdarg.h>

//能够接受非固定个数参数的函数称为可变参数函数
//我们可以借助标准库类模板initializer_list来实现这一功能，该类型可以使用的前提是所有实参的类型都相同
//initializer_list可以理解为某种类型的值的数组或列表，一旦它被初始化之后，里面的元素都是常量，就无法被修改了，有点类似python的元组，我们用它来接受形参

void variadic_function_1(std::initializer_list<std::string> initlist)
{
    for (auto iter = initlist.begin(); iter != initlist.end(); iter++)
    {
        std::cout << *iter << std::endl;
    }
    std::cout << "Total " << initlist.size() << " arguments received" << std::endl;
}

class TestElement4VariadicFunction
{
public:
    TestElement4VariadicFunction() = default;
    TestElement4VariadicFunction(const TestElement4VariadicFunction& tevf)
    {
        std::cout << "copied" << std::endl;
    }
};


//除了上面讲的方法，还有一种实现了可变参数函数的工具，即省略号形参：...
//省略号形参是C语言的写法，应该仅用于C与C++交接部分的函数
//省略号形参无法处理自定义类型的参数，它只能处理简单的类型，如int，char*等
//使用省略号形参的函数，它的参数是存储在线性连续的栈空间中的，而且这样的函数必须至少有一个普通参数，这样就能通过这个普通的参数对后续的所有参数寻址，得到它们的值与类型
//为了使用省略号形参，需要先引入头文件 stdarg.h
void getAll(double num, ...)    //可以不写逗号
{
    //我们需要使用一些定义好的宏
    va_list ls;    //va_list是char*的类型别名
    va_start(ls, num);  //指定va_list列表的起始参数为num，因为可变参数函数中所有参数的地址都是连续的，所以后续的参数都可以从起始参数num开始寻址
                        //如果参数列表中含有多个已知的形参，则va_start的第二个参数应该传入函数的最后一个已知参数，也就是...前面的那一个参数，以指定它为可变参数列表的起始参数
    for (int i = 0; i < num; ++i)
    {
        std::cout << va_arg(ls, double) << std::endl;   //va_arg的第一个参数是可变参数列表，第二个参数是所有参数的类型，每次调用va_arg都会使得它的结果向后移一位，所以不要用它去做条件判断
                                                        //否则会使得同一次循环中，va_arg的结果向后偏移多次。va_arg对类型的要求十分严格，它一开始指向的结果是可变参数列表中的第二个
                                                        //就是说，函数调用时传入的第一个参数可以是参数列表的长度，用于指定循环次数，而从第二个参数开始，类型必须与形参类型关键字一致，如果写了double，
                                                        //那传入的参数就必须是x.x，比如3.0，绝不能写3，此处不存在隐式类型转换，并且从第二个参数一直到最后一个参数的数目必须与第一个参数写明的数字一致
                                                        //如果少了，多出来的循环就会打印出乱码
    }
    //用完后需要把va_list对象给释放掉
    va_end(ls);
}
//使用字符串类型的情形
void printAsIntPlusOne(const char* str...)
{
    va_list ls;
    va_start(ls, str);
    for (int i = 0; i < atoi(str); i++)    //atoi是c函数，用于将字符串中的数字转为整形
    {
        std::cout << 1 + atoi(va_arg(ls, const char*)) << std::endl;
    }
    va_end(ls);
}



void variadic_function_learning()
{
    //若要向initializer_list形参传递一个参数序列，必须先把序列放在一个花括号中
    variadic_function_1({"hello", "world", "hello", "you"});

    //拷贝一个initializer_list或者为其赋值，都不会拷贝其中的元素，也就是说两个initializer_list是共享相同的元素的
    TestElement4VariadicFunction tevf1;
    TestElement4VariadicFunction tevf2;
    std::initializer_list<TestElement4VariadicFunction> TEinitList{ tevf1, tevf2 };
    std::cout << "拷贝initializer_list：" << std::endl;
    std::initializer_list<TestElement4VariadicFunction> TEinitList_2 = TEinitList;  //并没有引起列表内元素的拷贝构造
    std::cout << "拷贝赋值完成" << std::endl;

    //省略号形参
    getAll(9, 2.3, -3.4, 3.2, 1.0, 4.2, 6.0, 5.5, 6.4, 8.8);
    printAsIntPlusOne("5", "1", "2", "42", "27", "12");
}

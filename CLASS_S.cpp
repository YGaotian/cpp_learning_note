#include "CLASS_S.h"
#include "CLASS_P.h"			//必须将该头文件包含进来，才能在该文件中访问 class P 及其成员，如果仅仅是在函数定义之前写上class P，只是告诉编译器存在P这个类型，但依然不能访问P::number这个私有成员
								//我们在头文件CLASS_S.h中可以这么做是因为我们只是声明了void S::changeSNumValue(const P& p)，没有写要对P的成员进行访问的操作

void S::changeSNumValue(const P& p)
{
	sNum = p.number;			//要在class P声明中将该函数声明为友元类成员函数，才可在当前函数中访问 class P 的私有成员number
}
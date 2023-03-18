#pragma once
#include "CLASS_S.h"

class P
{
	friend void S::changeSNumValue(const P& p);			//在当前文件中必须将头文件"CLASS_S.h"包含进来，才可以将void S::changeSNumValue(const P& p)声明为友元
														//如果仅仅只是在class P前声明class S;只是告诉编译器有S这个类，编译器并不知道类S中是否存在changeSNumValue(const P& p)
private:
	int number = 100;
};
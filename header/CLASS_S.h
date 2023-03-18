#pragma once

//因为在类S中声明的成员函数要用到const P& p，所以要先声明一下有class P;
class P;
class S
{
public:
	int sNum = 0;
public:
	void changeSNumValue(const P& p);
};
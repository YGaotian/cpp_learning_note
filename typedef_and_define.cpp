#include "header_learning.h"

void typedef_and_define()
{
	//通过使用类型别名关键字typedef，num被定义为了int的类型别名，且该定义语句需要加分号结尾，别名在原名后
	//typedef int num;
	//num number = 10.2;
	//num number2 = -100;
	//std::cout << number << std::endl;
	//std::cout << number2 << std::endl;
	//通过宏定义预处理器#define，dflt被定义为double，该定义语句无需分号结尾，且别名在原名前
	#define dflt double
	dflt df = 2.1718;
	std::cout << df << std::endl;
	dflt dint = 12;
	std::cout << dint << std::endl;
	//define还可以定义其他对象的别名
	#define maxint 10
	int maxnum = maxint;
	std::cout << maxnum << std::endl;
}
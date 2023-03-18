#include "header_learning.h"

//使用auto和->的形式将返回类型写在函数头之后，可以使得函数的定义与声明看起来更易读
auto returnInt() -> int;
auto returnInt() -> int
{
	return 255;
}

void trailing_return_func()
{
	std::cout << returnInt() << std::endl;
}
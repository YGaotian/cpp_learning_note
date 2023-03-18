#include "header_learning.h"

void vector_usage()
{
	std::vector <int> vec(5);//vector固定长度定义，此时vec中所有值都为整型值0
	//vector可以动态更改长度，元素个数可以与声明中的不同
	vec = { 1, 3, 4, 5, 6, 7};
	std::cout << vec.at(5) << " and " << vec[2] << std::endl;//可以使用at方法取索引对应的元素，也可以使用[idx]
	//std::cout << vec[-2] << std::endl;//意思是指针从vec首元素向前偏移两位，即*(vec-2)，语法没问题，但这样是不安全的，所以编译器帮我们禁止了越界操作
	//也可以固定长度赋值初始化
	std::vector <int> vec2(5, 12);//5是长度，12是每个元素的值
	for (auto k : vec2)
	{
		std::cout << k << std::endl;
	}
	//也可以不指定长度直接初始化
	std::vector <std::string> strvec = { "asd", "fgh" };
	for (auto i : strvec)
	{
		std::cout << i << std::endl;
	}
	//最后，来一个拷贝构造看看
	std::vector <std::string> strvec2(strvec);//也可以写strvec2 = strvec
	for (auto e : strvec2)
	{
		std::cout << e << std::endl;
	}
}

void array_usage()
{
	std::array <double, 5> arr = { 2.1, 3.22, 6.54, 7.1, 3.14 };//array可以在声明时初始化
	//array不支持更改长度，如果初始化时元素个数与声明中的不同会报错
	std::cout << arr[2] << " and " << arr.at(4) << std::endl;//可以使用at方法取索引对应的元素，也可以使用[idx]
	//std::cout << arr[-3] << std::endl;//同样，编译器帮我们禁止了操作，但语法没有问题
}

void array_vector_compare()
{
	vector_usage();
	array_usage();
	//最后再来试试数组，可以使用负数索引进行越界操作，编译器不会阻止
	int intarr[3] = { 1,2,3 };
	std::cout << intarr[-1] << std::endl;
}
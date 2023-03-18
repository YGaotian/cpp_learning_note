#include "header_learning.h"

//以前学过函数指针，复习一下如何定义一个函数指针
int (*ip)(std::string str);			//一个指向返回类型为int且接收一个string形参的函数的函数指针，该函数指针的变量名为ip
//上面这种方法比较传统，如果现在有一个函数returnFuncPtr()，返回类型就是这种函数指针类型，那么该如何表示这个函数的返回类型呢
//int (*ip)(std::string str) returnFuncPtr(){}			//这里本意是想把返回类型写为int (*ip)(std::string str)，但是这样报错了
//那么我们可以用typedef来实现，为 int (*)(std::string str) 这种函数指针类型定义一个别名
typedef int (*ip_def)(std::string);			//这样就为一个指向“返回类型为int且接收一个string形参的函数”的函数指针定义了别名，别名为ip_def
//可以使用ip_def这个别名作为函数的返回类型
int string2int(std::string str)
{
	return 666;
}
ip_def returnFuncPtr()
{
	return string2int;
}

//上面的别名定义也可以使用using来实现，using的语法更加易读
using fp_def = float(*)(int);			//将别名的定义变成了像是赋值的样子，其中(*)表示这是一个指针类型，而float是这个指针指向的函数的返回值类型，最后的(int)表示函数接受一个int参数
										//	等号左边的fp_def就是这个指针类型的别名
float int2float(int in)
{
	return in + 0.01f;
}
fp_def returnIntAsFloatFuncPtr()
{
	return int2float;
}

//下面定义的是一个用来测试上述别名定义的方法是否确实有效可行的函数
void testPtrFunc()
{
	std::cout << returnFuncPtr()("ok") << std::endl;
	std::cout << returnIntAsFloatFuncPtr()(130) << std::endl;
}

void TypeConvertClass::printTheWords(std::string word)
{
	std::cout << "I love " << word << std::endl;
}

TypeConvertClass::operator sayFunc_ptr()
{
	return printTheWords;
}

void convert_class_member_to_function_pointer()
{
	testPtrFunc();
	
	TypeConvertClass tcc_3(5);
	tcc_3("China");			//这不是拷贝构造函数，这里是将类对象的名字当做函数名了，因为TypeConvertClass没有接收string参数的构造函数，但是有将本类对象转换为一个函数指针的类型转换运算符，这里满足了转换的条件
							//所以其实上面这一行是等同于tcc_3.operator TypeConvertClass::sayFunc_ptr()("China");的，同时，由于函数指针的行为与函数是类似的，还记得吗，而(*函数指针)表示的是函数本身
							//所以也可以写成(*tcc_3)("China");
	//最后，要注意，如果该类有一个拷贝构造函数，且类型转换运算符接收的形参的类型，也是 const TypeConvertClass& 的话，就会先调用拷贝构造函数，然后类型转换运算符会不正常地被调用
}
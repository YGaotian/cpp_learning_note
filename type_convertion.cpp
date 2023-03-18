#include "header_learning.h"

//在此我们创建一个新的类，并继承Aclass
class Bclass :public Aclass{};

void convert_type_learning()
{
	//不同于c风格类型转换int(value)或(int)value，c++风格类型转换有四种，要使用关键字
	//静态类型转换static_cast，功能与c风格类型转换相似，可对相似的数据类型进行转换类型
	//static_cast在编译阶段转换类型，且可以将子类转成父类
	double dn = 6.3324;
	int in;
	in = static_cast<int>(dn);
	std::cout << in << std::endl;
	Bclass Bcl;
	Aclass Acl = static_cast<Aclass>(Bcl);
	std::cout << Acl.intB << std::endl;
	//我们还可以对void*进行类型转换
	void* v_ptr;
	int numk = 6060;
	v_ptr = static_cast<void*>(&numk);
	int* num_ptr = static_cast<int*>(v_ptr);
	std::cout << *num_ptr << std::endl;
	//但是不能与void*之外的指针进行互相转换
	/* no can do
	int i = 100;
	int* iptr = &i;
	double* dptr = static_cast<double*>(iptr);
	*/

	//dynamic_cast
	//用于将父类转换成子类

	//const_cast
	//将const指针或引用转换成普通指针或引用
	const int cstval = 10;
	const int& cstval_ref = cstval;
	int& val_ref = const_cast<int&>(cstval_ref);
	val_ref = 203;
	//const的引用转换为普通引用后，对其赋值，编译器不会报错，但实际上这种行为的后果是未定义的，原值可能并不会被更改
	//但输出引用，得到的可能会是更改后的值，因此不要对由const的指针或引用转换得到的普通指针或引用进行赋值
	std::cout << val_ref << "and" << cstval << std::endl;
	//如果将一个变量的地址赋给一个常量指针，再将常量指针转换为普通指针，再对其赋值，是可以的
	int var = 12023;
	const int* const cst_ptr_cst = &var;
	int* var_ptr = const_cast<int*>(cst_ptr_cst);
	*var_ptr = 888;//assignment succeeded
	std::cout << var << "and" << *var_ptr << std::endl;

	//reinterpret_cast
	//重新解释一个对象的类型，能将对象的类型转换成毫不相干的另一种类型，是一种危险的类型转换
	int aval = 306;
	int* aval_ptr = &aval;
	std::string astr = reinterpret_cast<char*>(aval_ptr);//not safe
	std::cout << astr << std::endl;
}
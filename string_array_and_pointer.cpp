#include "header_learning.h"

void strArray_with_pointer()
{
	std::string str = "hello";
	char chstr[6] = "world";
	char* chstr_ptr = chstr;
	//char数组的数组名是字符串第一个字符的元素的地址，cout<<chstr理应得到字符串首元素的地址，而字符串常量表示的实际就是字符串的地址，也即字符串首元素的地址，所以cout<<chstr的显示结果也就是字符串本身
	std::cout << chstr << std::endl;
	//可以通过强制类型转换来验证它的确是地址的另一种显示
	std::cout << "chstr's address: " << (int*)chstr << std::endl;
	//看看我们刚才得到的地址是否就是char数组的地址，直接对char数组的数组名取地址，就得到了它的地址十六进制数字，会发现和刚才的地址是一样的
	std::cout << "chstr's address: " << &chstr << std::endl;
	//首元素地址，与数组地址的数值结果相同
	std::cout << "chstr[0]'s address: " << (int*)&chstr[0] << std::endl;
	//若对char数组chstr解引用，得到的便是字符串的首元素
	std::cout << *chstr << std::endl;
	std::cout << *(chstr+1) << std::endl;
	//string其实是类似的，若取string的第二个元素的地址，会得到第二个元素的地址以字符串常量显示的形式，但实际它确实还是地址，可以将它转换成int*看看
	std::cout << &str[1] << std::endl;
	std::cout << (int*)&str[1] << std::endl;

	//但是string与char数组不同的是，对string取地址&str，会直接得到代表整个string的地址，它与string的第一个元素的地址不同的不只是其代表的含义，连数值结果也不同
	std::cout << &str << std::endl;	//string对象的地址
	std::cout << "(int*)&str[0] is: " << (int*)&str[0]
		<< " ; &str[0] is: " << &str[0] << std::endl;	//string对象首元素的地址，会以字符串常量的方式显示，所以用int*进行强制类型转换
	//而且string不支持直接用string对象名+1进行偏移取值操作，必须使用string对象名[idx]的方式
	//std::cout << str+1 << std::endl;//CANNOT DO
	//并且，由于对string取地址会得到string本身的地址，而不是string首元素的地址，所以&str+1也不行，会将指针的指向向str末尾元素偏移一个位置，对它解引用也无法得到这一块内存上的值
	//但是我们依然可以强制使用指针算数进行对string对象中的元素的访问，虽然这么做有点自讨苦吃，我们先获取string的第一个元素，并对其取地址，即&str[0]，再使用指针算术进行偏移，最后再解引用取值
	std::cout << *(&str[0]+1) << std::endl;

	//因为字符串是个常量，假设chr_ptr是一个指针，若它不是常量指针，就不能将一个字符串常量赋给chr_ptr，所以必须在声明chr_ptr的时候在最前面加上const
	const char * chr_ptr;
	chr_ptr = "hello world";
	//可以像使用字符串一样使用指针chr_ptr
	std::cout << chr_ptr << std::endl;
	std::cout << chr_ptr[1] << std::endl;

	//string指针则不能直接指向字符串，需要在字符串前面加上强制类型转换，将其转换为string*
	std::string* str_ptr = (std::string*)"another world";
	//无法使用指针string*直接访问其指向的字符串常量中的元素，应先将其类型转换为char*并使用[idx]的方式
	std::cout << ((char*)str_ptr)[1] << std::endl;
}
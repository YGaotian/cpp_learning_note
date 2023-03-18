#include "header_learning.h"

/*
详细内容请看头文件中的类定义
*/

Myclass::Myclass() :c_numE(200)
{
	//c_numE = 200;const成员不可以在构造函数中以赋值的方式初始化，必须要使用构造函数初始化列表
	//默认构造函数如果什么都不做，可以直接写Myclass(){};或者也可以写成Myclass() = default;除此之外的其他非特殊的成员函数不能写成这种形式
	//如果想禁用默认构造函数，可以写成Myclass() = delete;这样就无法使用默认构造函数创建类对象了
	numA = numB = numC = numD = 1;
	//sumOfAllNums = numA + numB + numC + numD;
	std::cout << "默认构造函数 " << std::endl;
}
Myclass::Myclass(int anum, int bnum, int cnum, int dnum)
	:numA(anum), numB(bnum), numC(cnum), numD(dnum), c_numE(200)//构造函数初始化列表，等同于在函数体内为每个成员变量赋值，但效率更高
{
	//numA = anum;
	//numB = bnum;
	//numC = cnum;
	//numD = dnum;
	//注意，在构造函数初始化列表中，不应该使用成员变量初始化成员变量，比如这样 :numA(anum),numB(numA)
	//因为numA是否有值取决于类声明中成员变量声明的先后顺序，如果numA在numB之后声明，即使在初始化列表中
	//numA(anum)写在numB(numA)前面，在numB(numA)这里，numA依然还没有被赋值，numB就不能正确地使用numA的值来被初始化
	//sumOfAllNums = numA + numB + numC + numD;
	std::cout << "四个参数的构造函数 " << std::endl;
}
Myclass::Myclass(int anum) :c_numE(200)
{
	numA = anum;
	numB = numC = numD = 0;
	//sumOfAllNums = numA + numB + numC + numD;
	std::cout << "单个参数的构造函数 " << std::endl;
}
Myclass::Myclass(const Myclass& myc)
	:numA(myc.numA), numB(myc.numB), numC(myc.numC), numD(myc.numD), c_numE(myc.c_numE), sumOfAllNums(myc.sumOfAllNums)
{
	//如果不写拷贝构造函数，编译器会自动合成拷贝构造函数，默认根据成员对象的类型，调用该成员类型的拷贝构造函数，为新的类中对应的成员赋值
	//如果自定义了拷贝构造函数，就必须自己手动对所有成员赋值
	std::cout << "拷贝构造函数 " << std::endl;
}
Myclass::~Myclass()
{
	std::cout << "析构函数调用 " << std::endl;
	//析构函数仅用来手动释放我们在类中new出来的对象，普通的成员对象由系统自动为我们回收，如果不自己手动写析构函数，编译器会自动创建一个空的析构函数
}

void introduction_to_class()
{
	//调用单个参数的构造函数
	Myclass mc1 = Myclass(12345);//这一行等号其实并不是赋值，而是重载为了Myclass mc1(12345);所以也可以直接写Myclass mc1(12345);
	mc1.showAllMember();
	//调用具有四个参数的构造函数，但第四个参数使用默认值
	Myclass mc2(12, 23, 34);
	mc2.showAllMember();
	//调用默认构造函数，不加括号
	Myclass mc3;
	mc3.showAllMember();
	//调用了拷贝构造函数
	Myclass mc4 = mc1;//或者Myclass mc4(mc1);
	mc4.showAllMember();

	//我们还可以用一个列表去初始化一个类对象
	Myclass mc5 = { 11,22,33 };//运行一下会发现，这一步调用了接受四个参数的构造函数
	mc5.showAllMember();
	//上面这个操作能被执行的原因是，编译器进行了隐式类型转换，将一个列表转换为了Myclass对象并调用了四个参数的构造函数
	//然后将列表中的三个元素分别作为第一第二和第三个参数传入了构造函数
	//这种初始化方式称为复制列表初始化
	//但是这样做非常容易让人误操作
	//比如我们会用一个数字初始化一个我们自定义的类，只要我们的类定义了单参数的构造函数就不会报错
	//但如果这个构造函数接收的应该是一个int类型值，而我们传入了一个double(3.1415926)呢，值会被截断为int，发生精度丢失
	//为了避免这种情况发生，我们可以在类声明中，在构造函数的声明前加上关键字explicit，告诉编译器如果用一个其他类型的值
	//初始化我们的类对象，程序员必须手动进行显式的类型转换，否则报错，以此达到防止误操作的目的
	Myclass mc6 = Myclass(2.1212);
	mc6.showAllMember();
	/*因为单参数的构造函数声明前加了explicit，所以下面的这种初始化方式无效，因为禁止了隐式类型转换，而这里是将3.1415926隐式的转换为了临时的Myclass对象，之后再赋给mc7，否则是可以通过编译的
	Myclass mc7 = 3.1415926;
	mc7.showAllMember();
	*/
	//但是其实我们仍然可以使用圆括号的方法直接初始化，因为这里是显式地直接调用了Myclass的类型转换构造函数
	Myclass mc8(3.14);
	mc8.showAllMember();
}
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cstring>
#include <fstream>
#include <map>
#include <list>
#include <memory>
#include <thread>
#include <condition_variable>
#include <algorithm>

void const_pointer_and_pointer_const();
void cin_learning();
void cin_getline_learning();
void cin_get_learning();
void cin_with_string();
void string_in_istream();
void new_pointer_learning();
void new_array();
void array_learning();
void pointer_and_array();
void strArray_with_pointer();
void pointer_and_struct();
void array_vector_compare();
void compare_two_char_and_charArray();
void typedef_and_define();
void simple_file_output();
void simple_file_input();
void function_2DArray();
void function_pointer();
void range_based_for();
void nullptr_and_voidptr();
void public_and_private_in_struct();
void trailing_return_func();
void why_we_can_put_class_definition_into_header_files();
void defense_declared_header();
void iterator_fundamental();
void convert_type_learning();
void introduction_to_class();
void const_function_learning();
void mutable_learning();
void this_learning();
void static_learning();
void operator_overload();
void class_inheritance();
void virtual_in_class();
void friend_function();
void friend_class();
void friend_class_member_function();
void RTTI_learning();
void more_about_the_inheritance();
void right_value_reference();
void temporary_object();
void move_constructor();
void inherited_constructor();
void virtual_inheritance();
void type_convert_constructor();
void type_convert_operator();
void convert_class_member_to_function_pointer();
void class_member_function_pointer();
void class_member_variable_pointer();
void function_template();
void class_template();
void occasion_to_use_typename();
void what_are_callable_objects();
void default_param_of_templates();
void the_template_function_in_template_class();
void explicit_instantiation_of_template_class();
void template_alias();
void class_template_specialization();
void function_template_specialization();
void variadic_template();
void template_template_parameter();
void foreword_of_direct_management_of_memory();
void smart_pointer_learning();
void concurrency_learning_part1();
void concurrency_learning_part2();
void concurrency_learning_part3();
void concurrency_learning_part4();
void concurrency_learning_part5();
void concurrency_learning_part6();
void concurrency_learning_part7();
void concurrency_learning_part8();
void concurrency_learning_part9();
void concurrency_learning_part10();
void singleton_pattern_learning();
void critical_section_learning();
void concurrency_learning_part11();
void reacquaint_new_and_delete();
void memory_pool_learning();
void memory_pool_with_embeded_pointer();
void override_global_operator_new_and_delete();
void placement_new_learning();
void stlContainer_learning();
void stlAllocator_learning();
void stlIterator_learning();
void stlAlgorithm_learning();
void stlFunctional_learning();
void stlAdaptor_learning();
void stlFunction_learning();
void universal_reference_learning();
void understand_type_deduction_with_boost_library();
void reference_collapsing_and_perfect_forwarding();
void auto_learning();
void decltype_learning();
void deep_in_binder();
void lambda_learning();
void lambda_additional_analysis();
void variadic_function_learning();
void type_traits_learning();
void constexpr_learning();
void exception_handling_learning();
void How_to_create_enormous_lists();

void test();
//自定义的函数，用于在使用for_each方法的时候代替cout来打印int元素
void printElement(int);

//inline函数的定义应放在头文件中，因为它实质是会在编译阶段将函数内的步骤替换进调用该inline函数的地方，所以不会被重定义
//而普通函数的定义应该放在各自的实现cpp文件中，因为头文件如果被多个cpp文件include，在头文件中的普通函数的定义会被复制到
//多个cpp文件中，从而产生重定义，即使使用了头文件防卫#ifndef等，也是不行的，因为宏定义仅在当前文件内有效，也就是说
//1.cpp定义的宏，在2.cpp中是不存在的，所以1.cpp和2.cpp都会include头文件的内容，头文件防卫仅对头文件中的多重include
//有保护效果
inline void funcaa()
{
	std::cout << "aa" << std::endl;
}

class Aclass
{
	int intA = 666;
public:
	int intB = 777;
	void print_hello();
};

class Myclass
{
public:
	//可突破const限制并被更改的numA
	mutable int numA;
	int numB;
	int numC;
	int numD;
	//声明静态成员变量，不可以初始化，只能在类中声明，定义在static_and_extern.cpp开头
	static int numS;
	const int c_numE;//声明，初始化在introduction_to_class_serious.cpp中，也可以直接在此处const int c_numE = 200来初始化

public:
	/*
    构造函数只能写在public里面，不然系统无法正常构建一个类对象，因为写在私有之中的构造函数无法被外界访问
	构造函数没有返回值，不写返回类型，与类名一致
	如果我们自己不定义构造函数，编译器会帮我们隐式的定义一个默认构造函数，被称为“合成的默认构造函数”，一旦我们定义了任何一个构造函数
	合成的构造函数都不会被创建
	*/
	Myclass();//默认构造函数
	Myclass(int anum, int bnum, int cnum = 0, int dnum = 0);//有四个参数且其中两个参数有默认值的构造函数
	//注意，如果一个函数，它的形参有默认值，那么有默认值的参数必须写在所有无默认值的参数之后
	//默认值只能放在函数声明中，除非该函数没有声明
	explicit Myclass(int anum);//仅有一个参数的构造函数，除非有特殊需求，否则单参数构造函数前都应该加上explicit
		//注意，如果写了接收四个参数且其中有两个参数具有默认值的构造函数，那么就不能再写仅接受两个参数的构造函数，否则编译器
		//将无法分辨实例化类对象时只传入两个参数的操作到底是在调用哪一个构造函数
	//拷贝构造函数第一个参数必须是与类相同类型的const引用，保证不会在拷贝构造函数中修改原对象的值，后续可以有其他参数，但其他参数必须有默认值
	Myclass(const Myclass& myc);//在将一个类对象作为实参传给一个形参是非引用类型的函数时，拷贝构造函数也会被调用
								//在一个函数内创建了一个类对象，并返回的时候，编译器实际上是创建了一个临时对象，将类对象通过拷贝构造函数赋给了临时对象
								//然后将临时对象返回出来，类对象随着函数结束而销毁
	void editMemberValue(int& member, int val);
	void showAllMember() const;//常函数，只能为类声明并定义，无法将普通函数声明为常函数，常函数禁止修改类中的一切成员
	//如果类声明中写了类成员函数的定义，编译器会将该成员函数当成inline一样处理，但是该函数到底会不会被用作inline取决于编译器
	Myclass& _getSelf();
	//静态成员函数
	static void printNumSValue();
	~Myclass();//析构函数
public:
	//拷贝复制运算符重载
	Myclass& operator=(const Myclass& myc);

private:
	mutable int sumOfAllNums;
};

class Canine
{
public:
	Canine();
	Canine(char[10]);
	//写上final表明禁止任何子类重写覆盖该虚函数 void bark()
	virtual void bark() final;
	void move();
	virtual void move(int step);
	void talk();
	//基类的析构函数应该写成虚函数，因为当基类指针指向new出来的子类对象时，用完后我们需要用delete来释放指针指向的内存，但是如果基类的析构函数不是虚析构的
	//那么delete时就只会调用基类的析构函数，子类的析构函数不会被调用，这样new出来的子类对象就不会被释放，造成了内存泄漏，如果基类是虚析构函数，那么就会
	//调用子类和基类的析构函数，完整释放了内存
	virtual ~Canine();
protected://只允许子类和自己访问，private连子类也不能访问
	int legs = 4;
	int tails = 1;
	int ears = 2;
	char likedFood[20] = "not existed yet";
};

class Dog :public Canine			//如果在class Dog后面写上final，会导致Dog类禁止被其他类继承
{
public:
	Dog();
	Dog(char food[10]);

	//因为基类中该函数被声明为final，所以无法在此子类中重写该虚函数
	//void bark();报错：E1850	无法重写“final”函数 "Canine::bark" 

	//在函数声明后面加上override可以有效地防止我们将virtual错误地写在非虚函数的前面，或者说，可以让编译器检查我们在子类中想要重写的方法，是否是在父类中被声明为虚函数的
	//void move(int steps)在父类中被声明为了virtual，所以我们可以在子类的该函数声明后面加上关键字override，这样做还可以保证无需在该函数前再次写上virtual也能保持可读性，告诉阅读者这个是虚函数
	//我们已经了解了final的作用，所以如果我们还希望在这个子类中的void move(int steps)方法不会再被该子类的子类继承并重写覆盖，我们可以在当前子类中对该虚函数做final声明
	void move(int steps) final override;
	//final override和override final是一样的，但前者显然更顺口易读，final和override应该写在const的后面，纯虚标记=0的前面
	//不过值得一提的是，虽然子类Dog将该虚函数声明为final，禁止了Dog类的子类继承自己时重写该虚函数，但我们仍然可以写另一个类，继承最初的基类Canine，并重写覆盖基类中的该虚函数

	//由于在父类中void move()并没有被声明为virtual，所以如果在子类中也有一个该函数，就不能在后面加上override，否则会报错
	//virtual void move() override;//virtual关键字写不写都会报错：E1455	使用“override”声明的成员函数不能重写基类成员

	void talk(char owner[50]);
	void testfunc();
	~Dog() override;
public:
	using Canine::move;
public:
	int id = 110;
private:
	char owner[20] = "not existed yet";
};

class Teddy :public Dog
{
public:
	~Teddy() override;
};

class Human
{
public:
	//纯虚函数声明，纯虚函数无函数定义
	virtual void getBirth() = 0;
	virtual ~Human() = 0;
};

class Man :public Human
{
	//一个类可以让自己的友元访问自己的private和protected成员和方法
	//友元函数的声明，可以写在类声明的任何地方，它不受public或private或protected的影响
	//友元函数的声明并不是真的对某个函数的声明，它只是告诉编译器当前类有一个友元函数void tellMeYourPassword(const Man&)，函数的声明依然要在其他地方做，而且在main.cpp中不能忘了将声明函数的头文件include进来
	friend void tellMeYourPassword(const Man&);
	//友元类的声明，Dude是Man的友元类，友元关系是无法被继承的，同时也不具有传递性，并且友元关系是单向的，如果想让Man成为Dude的友元，还需在Dude类中也声明friend class Man;
	friend class Dude;			//也可以直接这样声明：friend Dude; 但前提是在Man类声明之前需要有这样的前置声明：class Dude; 否则编译器不知道friend Dude的Dude是什么东西，会报错
public:
	char name[20] = "None";
public:
	Man();
	Man(char n[20]);
	//getBirth是一个纯虚函数，子类必须亲自做实现，否则会报错
	void getBirth() override;
	~Man() override;
private:
	void sayPassword() const;
};

class Dude			//是Man类的友元类
{
public:
	void repeatPassword(const Man& m) const;
};

class Ball
{
public:
	double m_ballRadius;
	char m_ballColor[10] = "undefined";
public:
	Ball(double radius);
	Ball(double radius, char color[10]);
	Ball(const Ball& ball);
	virtual ~Ball();
};

class Basketball :public Ball
{
public:
	double m_basketballRadius;
	char m_basketballColor[10] = "undefined";
	double m_basketballWeight;
public:
	Basketball(double radius, char color[10], double weight);
	~Basketball() override;
};

class Flower
{
public:
	int m_petalNum;
public:
	Flower(int petalNum = 3);
	Flower(const Flower& fl);
	virtual ~Flower();
	Flower& operator=(const Flower& fl);
};

class DataA
{
public:
	DataA(int val);
	DataA(const DataA& data);
	virtual ~DataA();
public:
	int m_dataVal = 0;
};

class DataAgrp
{
public:
	DataAgrp(DataA dt);
	DataAgrp(const DataAgrp& dgp);
	DataAgrp(DataAgrp&& dgp) noexcept;			//move constructor
	DataAgrp& operator=(const DataAgrp& dgp);
	DataAgrp& operator=(DataAgrp&& dgp) noexcept;
	virtual ~DataAgrp();
public:
	DataA* m_dataA;
};

//为什么这里使用枚举类而不是常规枚举呢，因为枚举类不允许隐式类型转换，并且严格区分作用域，使用时需要这样做 enumName::enumVal
//而常规枚举默认隐式转换为整型，如果有两个枚举对象，它们拥有相同的枚举值，此时我们使用其中一个枚举值，不需要作用域运算符，结果会导致编译器不知道我们想要用的是哪一个枚举对象中的枚举值
enum class args{apple, orange, banana, lemon};
enum class appearance{beautiful, common, notBad, ugly};
class Mom
{
public:
	float m_feetSize;
	std::string m_hairLen;
	appearance m_appearence;
public:
	Mom();
	Mom(float feetSize, std::string hairLen="long", appearance apr=appearance::notBad);
	virtual ~Mom();
};

class Papa
{
public:
	int m_hair;
	float m_tall;
	args m_arg;
public:
	Papa();
	Papa(int h, float t=100, args arg=args::banana);
	virtual ~Papa();
};

class Kid : public Papa, public Mom			//子类中继承下来的构造函数的调用顺序是根据继承列表中的先后顺序来执行的，也就是说，在这里Papa在前面，所以Papa::Papa先执行
{
public:
	using Papa::Papa;			//没有自己的构造函数，继承直接父类的构造函数，但是只能继承有参构造函数，默认、拷贝、移动构造函数都无法继承。using:使某个对象在当前作用域内可见
								//	这行代码使得编译器自动生成了所有的子类有参构造函数，每一个子类有参构造函数的形参列表与父类的每一个有参构造函数的形参列表都对应相同
								//	即 Kid(int h, float t, args arg) : Papa(h, t, arg) {}  函数体是空的
	using Mom::Mom;				//这里又使得Mom类中的构造函数在子类中可见了，但如果Mom中有一个有参构造函数的形参列表与Papa中的一模一样，这样子类继承之后，是无法通过这样类型的参数实例化的，因为无法确认应调用哪个构造函数
								//	但是如果派生类定义了自己的有参构造函数，且它拥有与基类中的某一个有参构造函数相同的形参列表，那么基类中的这个构造函数不会被派生类继承，而是会被派生类的这个构造函数所覆盖
								//	所以我们需要在子类中定义一个自己的有参构造函数，该构造函数的形参列表与Mom和Papa中形参冲突的那个有参构造函数的形参列表一样，这样就可以覆盖基类中冲突的构造函数，从而使编译能够通过
	//如果父类的有参构造函数的形参列表有默认参数，那么子类中会生成多个有参构造函数，一个是带有所有形参的构造函数，其余的构造函数会相继省略一个默认参数
	//所以我们可以用不同数量的参数实例化子类，具体请看inherited_constructed.cpp
	~Kid() override;
	//对于子类Kid来说，因为我们没有为它定义构造函数，所以编译器会为它自动生成一个默认构造函数（前提是基类中有默认构造函数）
};

class GrandBase
{
public:
	std::string m_grandRank;
public:
	GrandBase();
	GrandBase(std::string rank);
	~GrandBase();
};

//虚继承时，所有的子类都要加virtual，除了继承链中的最后一个类
class FatherBaseA : virtual public GrandBase
{
public:
	std::string m_fatherARank;
	int objID;
public:
	FatherBaseA();
	FatherBaseA(std::string rank, int oid);
	~FatherBaseA();
};

class FatherBaseB : virtual public GrandBase
{
public:
	std::string m_fatherBRank;
public:
	FatherBaseB();
	FatherBaseB(std::string rank);
	~FatherBaseB();
};

//Grandson是继承链中的最后一个类，它不需要再被其他类继承，所以继承父类时不用加virtual
class Grandson : public FatherBaseA, public FatherBaseB
{
public:
	std::string m_grandsonRank;
public:
	Grandson();
	Grandson(std::string rank);
	~Grandson();
};

class TypeConvertClass
{
public:
	using sayFunc_ptr = void(*)(std::string);			//定义一个函数指针类型，该类型是一个指向无返回值且接收一个string形参的函数的指针类型
public:
	int m_intI;
public:
	explicit TypeConvertClass(int i);			//类型转换构造函数，它其实就是一个单形参构造函数
	static void printTheWords(std::string word);			//一个无返回值且接收一个string形参的函数，注意这是一个只属于类型本身的static成员函数
public:
	operator int() const;
	explicit operator double();
	//定义一个类型转换运算符，将本类对象转换为本类的一个成员函数指针
	operator sayFunc_ptr();			//这是一个将类对象转换为类成员的类型转换运算符，但是它只能转换为只属于类型本身的静态成员
};

class MemberFuncPtrClass
{
public:
	void generalMemberFunc(int argInt);
	virtual void virtMemberFunc();
	static void staticMemberFunc();
};

class MemberVarPtrClass
{
public:
	int m_varInt;
	static int m_staticVarInt;
public:
	MemberVarPtrClass();
	virtual ~MemberVarPtrClass();
};

namespace learning
{
	void namespace_learning();
}

class FunctorClass
{
public:
    void operator()(int num);
};
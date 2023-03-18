#include "header_learning.h"

int MemberVarPtrClass::m_staticVarInt = 1220980;

MemberVarPtrClass::MemberVarPtrClass() : m_varInt(602)
{
	std::cout << "MemberVarPtrClass created" << std::endl;
}

MemberVarPtrClass::~MemberVarPtrClass()
{

}

void class_member_variable_pointer()
{
	//类成员变量指针的写法与类成员函数指针是类似的，需要在指针变量名之前加上类名::*，而赋值的时候需要使用&类名::成员变量名
	int MemberVarPtrClass::* m_varInt_ptr = &MemberVarPtrClass::m_varInt;			//这个并不是真正意义上的指针，它并不是指向某一块内存地址，它所表示的是该成员变量与类实例对象之间的偏移量
																					//	值得注意的是，当前MemberVarPtrClass::* m_varInt_ptr的偏移量为4，为什么不是0呢？因为类本身含有一个虚函数
																					//	一旦类中含有虚函数，那么类中就会产生一个虚函数表，而每一个类实例中就都会有一个虚函数表指针
																					//	它与类实例的偏移量为0，大小为4，排在后面一块内存空间的就是当前的该类成员变量指针，所以该指针的偏移量为4
	//如果需要使用该指针，则需要有一个类实例对象
	MemberVarPtrClass mvpc_1;
	(mvpc_1.*m_varInt_ptr)++;			//通过类成员变量指针来修改成员变量的值，等价于mvpc_1.m_varInt++
	std::cout << "mvpc_1: " << mvpc_1.m_varInt << std::endl;

	//那么静态类成员变量如何定义它的指针呢，这和静态类成员函数的指针定义方法是类似的，同样只需在指针名前面加个*即可
	int* m_staticVarInt_ptr = &MemberVarPtrClass::m_staticVarInt;
	*m_staticVarInt_ptr = 5810;
	std::cout << *m_staticVarInt_ptr << " and mvpc_1.m_staticVarInt = " << mvpc_1.m_staticVarInt << std::endl;
}
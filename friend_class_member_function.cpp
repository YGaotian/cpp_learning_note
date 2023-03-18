#include "header_learning.h"
#include "CLASS_P.h"
#include "CLASS_S.h"

void friend_class_member_function()
{
	S sInst;
	P pInst;
	std::cout << sInst.sNum << std::endl;
	sInst.changeSNumValue(pInst);
	std::cout << "changed: " << sInst.sNum << std::endl;
}
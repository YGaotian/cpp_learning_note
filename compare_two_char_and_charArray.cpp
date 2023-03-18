#include "header_learning.h"

void char_compare(char ch_a, char ch_b)
{
	//单个字符可以被直接比较，因为单个字符实际上是整型数值
	if (ch_a == ch_b)
		std::cout << "They are the same." << std::endl;
	else
		std::cout << "They are different." << std::endl;
}

void charArray_compare(char a[], char b[])
{
	//C风格字符串实际上表示的是地址，所以不管怎么比较，哪怕a与b有着相同的字符元素，它们的地址并不相同，所以不可能相等
	if (a == b)
		std::cout << "They are the same." << std::endl;
	else
		std::cout << "They are different." << std::endl;
}

void charArray_Cstyle_compare(char a[], char b[])
{
	//strcmp()接收两个字符串或指针或字符数组名，如果它们相同则返回0，如果第一个按字母顺序（ascii）排在第二个之后则返回负数值，否则返回正数值
	if(!strcmp(a, b))
		std::cout << "They are the same." << std::endl;
	else
		std::cout << "They are different." << std::endl;
}

void two_char_compare()
{
	//字符比较
	char a = 'a';
	char b = 'c';
	char_compare(a, b);
	char k = 'q';
	char r = 'q';
	char_compare(k, r);
}

void two_charArray_compare()
{
	//C风格字符串比较
	char chstr_a[6] = "world";
	char chstr_b[6] = "world";
	charArray_compare(chstr_a, chstr_b);
	char chstr_s[6] = "hello";
	char chstr_f[6] = "";
	charArray_compare(chstr_s, chstr_f);
	//真正可行的比较方法
	charArray_Cstyle_compare(chstr_a, chstr_b);
	charArray_Cstyle_compare(chstr_s, chstr_f);
}

void compare_two_char_and_charArray()
{
	two_char_compare();
	two_charArray_compare();
}
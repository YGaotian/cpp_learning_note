#include "header_learning.h"

void cin_get_learning()
{
	/*
	如果cin.get()读到一个空行，cin会设置一个失效位，接下来的输入都将被阻断，cin.clear()将cin.fail复位为0，也就是说恢复到继续可以输入的状态
	cin.ignore()参数为cin.ignore( int num,char ch)，意思是丢掉输入队列中数据达到num个或遇到ch时停止，不给参数默认为cin.ignore(1,EOF)，即取出并丢掉错误输出前的一个字符
	这两个方法要一起使用，就可以在cin.get()读取到一个空行时，不影响后续的输入，而当读取的是一个有效的行时，行末的换行符将会被丢弃
	不然的话就要使用cin.get(ch, num).get()来读取有效行的末尾留在输入缓冲区中的换行符，以保证后续输入的读取正常，但这种方法依然无法解决输入是一个空行的问题
	*/
	char the_sentence[30];
	char another_sentence[30];
	std::cout << "enter the first sentence:";
	std::cin.get(the_sentence, 31);
	//std::cin.get();
	std::cin.clear();
	std::cin.ignore(); //该代码作用等同于在读取到空行时，恢复可输入状态后再用一次cin.get()，消耗掉之前行末的换行符
	std::cout << "the sentence is:" << the_sentence << std::endl;
	std::cout << "enter another sentence:";
	std::cin.get(another_sentence, 31);
	std::cout << "another sentence is:" << another_sentence << std::endl;
}
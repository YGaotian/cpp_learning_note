#include "header_learning.h"

void simple_file_output()
{
	//创建一个ofstream对象，它与ostream的一个对象cout相似，可以使用<<，endl，这些操作可以用来写入文件，写完之后要记住使用close()来关闭文件
	std::ofstream fout;
	//open()接收一个c风格字符串作为参数，可以是一个字面字符串，也可以是一个存储在数组中的字符串
	fout.open("simple_file_io.txt");
	fout << "s 7.5 hello world!";
	fout.close();
}

void simple_file_input()
{
	//创建一个ifstream对象，它与istream的一个对象cin相似，可以使用get()来读取一个字符，使用getline()来读取一行字符，使用eof()或fail()来判断输入是否成功
	std::ifstream fin;
	//open()接收一个c风格字符串作为参数，可以是一个字面字符串，也可以是一个存储在数组中的字符串
	fin.open("simple_file_io.txt");
	//IMPORTANT!!!检查文件是否被正常打开，如果打开了一个不存在的文件，则终止程序
	if (!fin.is_open())
	{
		std::cout << "cannot find the file." << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "file opend successfully" << std::endl;
	double dnumber;
	double dnumber2;
	char chara[20];
	fin >> dnumber;
	//考虑两种情况，一：读取正常，文件中第一个字符或字符串是数字，则没有任何问题；二：若文件中第一个字符不是数字，fin会设置failbit，停止之后的输入
	//所以需要一个条件判断输入是否正常，如果不正常，就要用clear()方法清除failbit，使得输入可以继续，并通过ignore()方法丢掉刚刚那次输入时获取到的字符，因为这个字符还保留在输入队列中
	if (fin.fail())
	{
		fin.clear();
		fin.ignore(); 
		dnumber = -1;
		std::cout << "An error occurred when getting the value of dnumber, so it is: " << dnumber <<" now." <<std::endl;
	}
	fin >> dnumber2;
	//这次if中的代码不会执行，因为文件中第二组是一个数
	if (fin.fail())
	{
		fin.clear();
		fin.ignore();
		dnumber2 = -1;
		std::cout << "An error occurred when getting the value of dnumber, so it is: " << dnumber2 << " now." << std::endl;
	}
	//循环读入文件中剩余的字符直到文件尾
	while (!fin.eof())
	{
		if (fin.fail())
		{
			fin.clear();
			fin.ignore();
		}
		fin >> chara;//空格会被丢弃
		std::cout << chara;
	}
	fin.close();
	std::cout << std::endl;
	std::cout << dnumber << std::endl;
	std::cout << dnumber2 << std::endl;
	

}
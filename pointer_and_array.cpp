#include "header_learning.h"

void pointer_and_array()
{
	//数组名表示的是数组中第一个元素的地址，即numberArray和&numberArray[0]是一样的，但如果对numberArray取地址，即&numberArray，返回的则是整个数组的地址，这些输出的数值结果是一样的
	int numberArray[3] = {1,42,233};
	std::cout << "numberArray is:" << numberArray << std::endl;
	std::cout << "&numberArray[0] is:" << &numberArray[0] << std::endl;
	std::cout << "&numberArray is:" << &numberArray << std::endl;


    //它们实际上不是一回事，下面看看对各项+1后转为十进制显示的结果
    std::cout << "numberArray+1 is:" << int(numberArray+1) << std::endl;//数组中第一个元素的地址向后偏移一位，即数组中第二个元素的地址
    std::cout << "&numberArray[0]+1 is:" << int(&numberArray[0]+1) << std::endl;//数组中第一个元素的地址向后偏移一位，即数组中第二个元素的地址
    std::cout << "&numberArray+1 is:" << int(&numberArray+1) << std::endl;//数组向后偏移了一个数组的长度的内存地址
    //一个int占四个字节，这个数组包含三个int值，所以占12个字节，将数组整体+1则是偏移了12个字节，将数组内对象+1，则是偏移了4个字节，它们相差12-4=8个字节
    std::cout << "secondElement - firstElement result:" << int(&numberArray[0]+1) - int(&numberArray[0]) << std::endl;
    std::cout << "array difference result:" << int(&numberArray + 1) - int(&numberArray) << std::endl;
    std::cout << "array - firstElement result:" << int(&numberArray + 1) - int(&numberArray[0] + 1) << std::endl;
    std::cout << "\n";

    //数组指针
    //在array_learning中已学习过，这里再次复习一下，以与指针数组作比较
    int(*array_pointer)[3] = &numberArray;
    std::cout << "numberArray's address is:" << &numberArray << std::endl;
    //array_pointer是指向numberArray的指针，它指向numberArray本身，但它的数值结果与numberArray第一个int元素的地址相同
    std::cout << "array_pointer is:" << array_pointer << std::endl;
    //比较一下array_pointer与numberArray第一个int元素的地址，发现它们的数值结果确实相同
    std::cout << "&numberArray[0] is:" << &numberArray[0] << std::endl;
    //可以通过下面这行来验证array_pointer的长度为12字节
    std::cout << int(array_pointer + 1) - int(array_pointer) << std::endl;
    //既然array_pointer的含义是整个数组的地址，那么array_pointer[1]就是说将array_pointer自numberArray中的末元素向后偏移一个数组长度（12字节）的内存地址，它不能被直接使用，所以对它解引用的结果明显不正常
    std::cout << "array_pointer[1] is:" << array_pointer[1] << " with value " << *array_pointer[1] << std::endl;
    //*array_pointer是数组本身，数值结果与数组的第一个int元素的地址一样，但意义不一样
    std::cout << "*array_pointer is:" << *array_pointer << std::endl;
    std::cout << "(*array_pointer)[1] is:" << (*array_pointer)[1] << std::endl;
    std::cout << "&(*array_pointer)[1] is:" << &((*array_pointer)[1]) << std::endl;
    std::cout << "&numberArray[1] is:" << &(numberArray[1]) << " with value " << numberArray[1] << std::endl;
    std::cout << "\n";

	//指针数组
	int* arrayAFirstElement_ptr = &numberArray[0];
	int* arrayASecondElement_ptr = &numberArray[1];
	int* arrayContainsPointer[2] = {arrayAFirstElement_ptr, arrayASecondElement_ptr};
	std::cout << "pointer array is:";
	for (int i = 0; i < 2; ++i)
	{
		std::cout << arrayContainsPointer[i] << " with the value " << *arrayContainsPointer[i] << "    ";
	}
	std::cout << std::endl;
	//         下方是指针数组的第一个指针元素，cout输出的是它指向的地址，即arrayA中1的地址        下方是指针数组的第一个指针元素本身的地址                下方同左侧           下方是整个数组的地址，数值结果同左侧两个，但意义不同
	std::cout << *arrayContainsPointer << " and " << arrayContainsPointer[0] << " and " << &arrayContainsPointer[0] << " and " << arrayContainsPointer << " and " << &arrayContainsPointer << std::endl;
	std::cout << "\n";
	
	//指向指针数组的指针
	//下面这一行，首先通过(*parray_pointer)强调了parray_pointer是一个指针，接着[2]表明了parray_pointer指向的是一个数组，int*表明它所指向的数组的类型是int*
	int * (*parray_pointer)[2] = &arrayContainsPointer;
	//parray_pointer指向了指针数组的地址，它与指针数组的第一个元素的地址数值相同，所以cout << parray_pointer的数值结果与cout << &arrayContainsPointer[0]（第一个指针元素本身的地址）一样，但实际所指对象的意义不同
	std::cout << "parray_pointer is:" << parray_pointer << std::endl;
	std::cout << ">>>" << parray_pointer[0] << " and " << parray_pointer[1] << std::endl;
	//std::cout << 
	//对指向指针数组的指针解引用，我们得到了这个数组本身
	std::cout << "*parray_pointer is:" << *parray_pointer << std::endl;
	//为了验证这一点，假设得到的确实是数组本身，我们已经知道这个数组有两个元素，不妨试试能不能cout数组的两个元素，如果可以，则证明我们的猜测是正确的
	std::cout << (*parray_pointer)[0] << " with value " << *(*parray_pointer)[0] << " and " << (*parray_pointer)[1] << " with value " << *(*parray_pointer)[1] << std::endl;
	//现在我们得到了验证，确实可以，明确的说，指向指针数组的指针就是一个三级指针，它指向数组，而数组名又类似于一个指针，数组内的元素又是一个指针，现在我们还想用指针算术的方法来得到数组中两个指针元素所指对象的实际数值
	//对parray_pointer解引用一次，得到了数组本身，再一次解引用，得到了数组内的指针，第三次解引用则得到了实际的数值
	std::cout << "value 1： " << ***parray_pointer << " and " << "value 2： " << *(**parray_pointer + 1);
}
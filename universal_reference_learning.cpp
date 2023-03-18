#include "header_learning.h"

//��������������ģ���еļ���������д������ֵ���ã�T&&��T��&&���ֿܷ������������ֵ�����ˣ�����˵vector<T>&&�Ͳ����������ã���������Ҳ����δ��������
template <typename T>
void printUniversalRef(T&& arg)
{
    std::cout << arg << " at " << &arg << std::endl;
}

template <typename T>
class templateClass4Ref
{
public:
    void testFunc(T&& i)
    {

    }
};

void universal_reference_learning()
{
    int&& intRRef = 10;
    std::cout << &intRRef << std::endl;
    printUniversalRef(intRRef);
    printUniversalRef(22222);
    int intLVal = 100;
    std::cout << &intLVal << std::endl;
    printUniversalRef(intLVal);
    int& intLRef = intLVal;
    std::cout << &intLRef << std::endl;
    printUniversalRef(intLRef);
    //���Է��֣��������ÿ���ͬʱ������ֵ����ֵ����ֵ��������ֵ����
    //�������ý����������Ƶ��У���д��T&&��autoҲ�����������õĸ��������̸

    //������βε���������ǰ�����const����ô���Ͳ�����һ���������������ˣ�������β����Ͷ��ԣ������ʵ������constû��ϵ����const T&&����һ����ֵ���ã������ԭ��

    //��������T&&ʵ���Ͼ�����ֵ���ã�ֻ���������Ƶ�ʱ��Ҳ�ܽ�����ֵ����ֵ���ã������������ò�����һ���µ���������

    //��ģ��ĳ�Ա�����е�T&&��������������
    int testIntVar = 777;
    templateClass4Ref<int> tc4r;
    ///tc4r.testFunc(testIntVar);    //����
    tc4r.testFunc(10);  //���У���Ϊ10����ֵ����testFunc�����Ĳ�������T&&�������ֵ����int&&����������������
    //�������ϵ������ԭ���ǣ���ģ��templateClass4Ref�������Ա�������Ǻ���ģ�壬����û�з������������Ƶ�������ģ�������ʵ�������ʱ����Ѿ�ȷ������������ֻ�ڷ��������Ƶ�ʱ����
}
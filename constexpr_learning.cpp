#include "header_learning.h"

//constexpr�������α�����Ҳ��������ָ�룬���������κ�������constexpr���εı�����ָ��һ���ǳ�����Ҳ����˵��constexpr������ָ�뱾��ʹ���޷�ָ��������ַ
//constexpt�����ָ��ĳ�ʼֵ�����Ǵ���ڹ̶���ַ�Ķ��󣬾ֲ����󲢲��Ǵ���ڹ̶���ַ�ģ�����constexprָ�벻��ָ�����ǣ����Ǿֲ���̬�����Ǹ�����
int i = 90;
constexpr int* cip = &i;

//constexpr���εĺ����ķ���ֵ���Ա�constexpr���εı���ȥ���գ������Ļ�constexpr���εĺ����ķ���ֵ�Ǳ�����ȷ���ģ����Բ����������������
//�����������û����constexpr���Σ����Ǻ���û����constexpr���Σ����޷��ڱ�����ȷ������ֵ
constexpr int constexprFunction(int a, int b)
{
    return a * a + 2 * a * b + b * b;
}

//��cpp17��ʼ��������ʹ��constexpr�������ʹһ�������ڱ����ڻ�����ʱȷ������ı��ʽ�ڱ�����ȷ�����
//����ͨ���ɱ����ģ��İ�չ������ʾ
template <typename U, typename ...T>
void printAllArg(U first, T... arg)
{
    if constexpr (sizeof...(T))             //��ôд�Ͳ���Ҫ���庯��������չ����ֹ�����ˣ�constexprʹ��sizeof...(T)�����ڱ����ڼ�������������ͨ������
    {
        std::cout << first << std::endl;
        printAllArg(arg...);
    }
    else
    {
        std::cout << first << std::endl;
    }
}


void constexpr_learning()
{
    constexpr int squareOfAPlusB = constexprFunction(2, 4);
    std::cout << squareOfAPlusB << std::endl;
    printAllArg(1, 2, 3, 33, 443, 556, 789);
}
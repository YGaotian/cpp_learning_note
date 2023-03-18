#include "header_learning.h"

void stlAllocator_learning()
{
    //������Ҳ��һ����ģ�壬�����������ʹ�ã������ڴ�ķ����������԰����ڴ�صĽ�ɫ���Լ��ٵ����Ķ��malloc���ڴ���˷ѣ�Ҳ����˷���Ч��
    std::list<int, std::allocator<int>> intList;    //�ȼ���std::list<int>
    //����stlContainer_learning.cppһ�ڿ�֪��list��Ԫ�ص��ڴ��ǲ������ģ������ɴ�Ҳ�����жϣ���ǰc++��׼���е�list������ȱʡ�ķ�������û��ʹ���ڴ�ؼ���

    //���﷨�����������ǿ���ֱ��ʹ��allocator��������ʵ�ʿ����У�allocatorͨ��ֻ�����������Ҽ��ٱ��ֶ�����ʽʹ�ã����������ʾ
    std::allocator<int> intAlloc;   //������һ�����Է���int���Ͷ�����ڴ�ķ�����
    int* p = intAlloc.allocate(3);  //������δ��������ڴ棬��һ���ڴ�Ĵ�С���Դ���3��int����12���ֽ�
    for (int pos = 0; pos != 3; pos++)
    {
        p[pos] = (pos + 1) * 2;
    }
    for (int pos = 0; pos != 3; pos++)
    {
        std::cout << p[pos] << std::endl;
    }
    //ʹ������ڴ�Ҫ�ͷ�
    intAlloc.deallocate(p, 3);  //����ָ�룬�Լ�Ҫ�ͷ��ڴ�Ķ�����������������Ӧ��������ڴ�ʱ������һ�������˻������˶���������������
}
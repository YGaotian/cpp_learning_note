#include "header_learning.h"

void stlFunctional_learning()
{
    //stl����һЩ����õĺ�������Ҳ����˵�º���functor��ʹ��֮ǰ��Ҫ����ͷ�ļ� functional
    //����˵plus����һ���º���������һ����ģ��
    std::plus<int>();   //������һ����ʱ����plus���Խ�����������������мӷ�����
    std::plus<double> doublePlus;   //������һ��plus����ʵ��
    std::cout << doublePlus(12.5, 121.1) << std::endl;
    //��׼���еĺ���������Դ��·�Ϊ���¼�����
    //���������࣬�����plus��������һ�࣬���м��������˷���ȡģȡ��
    //��ϵ�����࣬������ڣ�С�ڣ����ڵ��ڣ�С�ڵ��ڣ���ȣ������
    //�߼������࣬�߼��룬�߼����߼���
    //λ�����࣬�ͣ������
    std::vector<int> vecIntSort = { 2, 3, 45, 6, 21, 32 };
    std::sort(vecIntSort.begin(), vecIntSort.end(), std::greater<int>());   //ʹ��stl����õĺ���������Ϊ����������
    std::for_each(vecIntSort.begin(), vecIntSort.end(), printElement);
}
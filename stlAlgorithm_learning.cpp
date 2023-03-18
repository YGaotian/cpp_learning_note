#include "header_learning.h"
#include <algorithm>

void addOne(int& i)
{
    ++i;
}

void printElement(int i)
{
    std::cout << i << std::endl;
}

bool sortRule(int i, int j)
{
    return i > j;
}

void stlAlgorithm_learning()
{
    //stl�㷨������������ʹ�õ�ȫ�ֺ��������������������أ��������޹صģ�����ĳЩ���ݽṹ�ĵ��������㷨֮��ļ����Բ��Ǻܺ�
    //�㷨������ͬ����ĵ����������ڲ����в�ͬ�Ĵ���ʽ
    std::vector<int> intVec4Algorithm = { 1, 22, 25, 55, 78 ,13, 18, 33, 6};
    //find�㷨�����õ�����ָ�����䣬����ҵ�Ԫ�أ��򷵻��׸�����������Ԫ�صĵ����������򷵻������Ҷ˵ĵ�����
    auto elementWanted = std::find(intVec4Algorithm.begin(), intVec4Algorithm.begin() + 3, 100);
    if (elementWanted == intVec4Algorithm.begin() + 3)
    {
        std::cout << "û��Ԫ�أ�400\n" << std::endl;
    }

    //find_if���ԴӸ�������ʼλ�ÿ�ʼ������Ľ���λ��ִ�пɵ��ñ��ʽ�����տɵ��ñ��ʽ����д�Ĺ�����ң���������ɵ��ñ��ʽ�ķ���ֵ���ͱ�����bool���������true�����ʾ�ҵ������򷵻�false
    //����������һ���ɵ��ñ��ʽ��֮Ϊν�ʣ����������˵һ�飬ν�ʾ���һ���ɵ��ñ��ʽ�����ķ��ؽ����һ����������������ֵ����׼���㷨��ʹ�õ�ν�ʿɷ�Ϊ���࣬��һԪν�����Ԫν��
    //һԪν�ʾ���ֻ����һ�������Ŀɵ��ñ��ʽ����Ԫν�����ǽ������������Ŀɵ��ñ��ʽ��find_if�����ܵ��Ǹ�һԪν�ʣ���������ɵ��ñ��ʽ�жഫ�˲����ͻᱨ��
    //Ȼ��find_if���ص�һ������������Ԫ�صĵ����������򷵻�һ��ָ������Ľ���λ�õĵ�������ע��˴��Ŀɵ��ö������޸Ĵ���Ĳ�����Ҳ����˵����Ĳ����������������ͣ�����ô���ƺ����ᱨ��
    auto result = std::find_if(intVec4Algorithm.begin(), intVec4Algorithm.begin() + 3, [](int value)
        {
            if (value == 25)
            {
                return true;
            }
            return false;
        });
    if (result != intVec4Algorithm.begin() + 3)
        addOne(*result);
    //for_each�㷨����ָ����ʼλ�������λ�ã�����������ڶ�ÿ����������ָ��Ԫ��ִ��һ��ָ���ĺ���
    std::for_each(intVec4Algorithm.begin(), intVec4Algorithm.end(), printElement);
    std::cout << std::endl;

    //sort�㷨���԰�������Ϊһ��Ԫ�ؽ����������ǿ���ʹ��Ĭ�ϵ����򷽷�����С�����ţ�Ҳ�����Լ�дһ��������Ϊ�Զ�������������ע����������ķ������ͱ�����bool
    std::sort(intVec4Algorithm.begin(), intVec4Algorithm.end(), sortRule);
    std::for_each(intVec4Algorithm.begin(), intVec4Algorithm.end(), printElement);
    std::cout << std::endl;

    //��Щ������֧��ȫ�ֵ�sort�����������ṩ���Լ���sort
    std::list<int> li = { 1, 3, 5, 2, 4, 6 };
    //std::sort(li.begin(), li.end());  ����
    li.sort(sortRule);
    std::for_each(li.begin(), li.end(), printElement);
}
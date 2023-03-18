#include "header_learning.h"

void display(std::output_iterator_tag cate)
{
    std::cout << "output" << std::endl;
}

void display(std::input_iterator_tag cate)
{
    std::cout << "input" << std::endl;
}

void display(std::forward_iterator_tag cate)
{
    std::cout << "forward" << std::endl;
}

void display(std::bidirectional_iterator_tag cate)
{
    std::cout << "bidirectional" << std::endl;
}

void display(std::random_access_iterator_tag cate)
{
    std::cout << "random_access" << std::endl;
}

//ͨ������������ȡ��������������������ȡ��������ӡ�ĺ���
template <typename T>
void display_category(T iter)
{
    typename std::iterator_traits<T>::iterator_category cate;   //��һ�������;�����ȡ��������ֱ����ȡ��������������
    display(cate);
}

void stlIterator_learning()
{
    //���������в�ͬ������ģ������������ṩ
    //��������ÿ�����඼��Ӧ��һ���ṹ����Щ�ṹ������std�����ռ��У�����ͷ�ļ�xutility��
    //�����������������ÿ�������������Ĳ������ƶ������ԣ��������ɷ�Ϊ���¼��֣�
    struct std::output_iterator_tag;           //����͵�������ӵ�н�ֵд��ָ��λ�ã���ֵ����������֧��ǰ��/���õ�����������
    struct std::input_iterator_tag;            //�����͵�����������һ��һ���ض�ȡ�����е�Ԫ�أ�֧��ǰ��/���õ����������������ĵ����������Ƿ���ȵ��ж�
    struct std::forward_iterator_tag;          //ǰ����������������͵������Ļ���֮�ϣ������˸�ֵ����
    struct std::bidirectional_iterator_tag;    //˫�����������ǰ��������Ļ����ϣ��������෴�ķ����������
    struct std::random_access_iterator_tag;    //������ʵ���������˫��������Ļ����ϣ�������������ʵ�����
                                               //   ���Ǵӵ�ǰ��ָ����λ�ã�ǰ��/����n��Ԫ�أ�iter + n / iter -= n��������ͨ����������Ԫ�أ�iter[n]��
                                               //   �����Է�������������֮��ľ��루iter2 - iter1�������ǱȽ�iter1�Ƿ��ڻ���iter2֮ǰ/֮��> / >= / < / <=��

    //����ͨ�����뽫ÿһ�������ĵ������������ӡ����
    std::vector<std::string>::iterator itv;
    std::list<int>::iterator itl;
    display_category(itv);
    display_category(itl);
}
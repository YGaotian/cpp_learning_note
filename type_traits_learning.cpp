#include "header_learning.h"

//������ȡ��һ�������ڷ��ͱ���еļ�������˼���������������������Ϣ��c++11��ʼ����׼�����ṩ�˺ܶ�������ȡ�Ľӿڣ���һЩ��ģ��

template <typename T>
void traitsDemonstrate(const T& obj)
{
    std::cout << "is_class: " << std::is_class<T>::value << std::endl;                                  //�Ƿ�Ϊ������
    ///std::cout << "is_pod: " << std::is_pod<T>::value << std::endl;    �Ƿ�����ͨ�ࣨ��C���ݵ��������ͣ���û�й���/����/�ƶ�/��������������������麯��������࣬�Ҳ�������
    ///                                                                  ��������--�Ǿ�̬�ĳ�Ա���ʼ�����ͬ����Ϊpublic/private/protected
    ///                                                                         --����и��࣬��ǰ��ĵ�һ����Ա�����Ǹ������ͣ��Ǿ�̬��Աֻ�ܴ����ڸ������������֮һ��
    ///                                                                  cpp20������
    //����Ŀ�����is_standard_layout����
    std::cout << "is_standard_layout: " << std::is_standard_layout<T>::value << std::endl;
    std::cout << "is_default_constructible: " << std::is_default_constructible<T>::value << std::endl;  //�Ƿ���Ĭ�Ϲ��캯��
    std::cout << "is_move_constructible: " << std::is_move_constructible<T>::value << std::endl;        //�Ƿ����ƶ����캯��
    std::cout << "has_virtual_destructor: " << std::has_virtual_destructor<T>::value << std::endl;
}

void type_traits_learning()
{
    Myclass mmm;
    traitsDemonstrate(mmm);
    std::cout << std::endl;
    int aaaaa = 10;
    traitsDemonstrate(aaaaa);
    std::cout << std::endl;
    Dog ddd;
    traitsDemonstrate(ddd);
    std::cout << std::endl;
    FunctorClass fffff;
    traitsDemonstrate(fffff);
    std::cout << std::endl;
}

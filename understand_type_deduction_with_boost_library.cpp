#include "header_learning.h"
#include <boost/type_index.hpp>

template <typename T>
void print_type_template_parameter(T& arg)
{
    using boost::typeindex::type_id_with_cvr;
    auto tiwc = type_id_with_cvr<T>();              //�õ��Զ��Ƶ�����������
    std::cout << "T is  : " << tiwc.pretty_name() << std::endl;   //��ӡ����ɶ�������
    std::cout << "arg is: " << type_id_with_cvr<decltype(arg)>() << std::endl;
}

template <typename T>
void print_const_T_ref(const T& arg)
{
    using namespace boost::typeindex;
    std::cout << "T  : " << type_id_with_cvr<T>().pretty_name() << std::endl;
    std::cout << "arg: " << type_id_with_cvr<decltype(arg)>().pretty_name() << std::endl;
}

template <typename T>
void print_pointer(T* arg)
{
    using namespace boost::typeindex;
    std::cout << "T  : " << type_id_with_cvr<T>().pretty_name() << std::endl;
    std::cout << "arg: " << type_id_with_cvr<decltype(arg)>().pretty_name() << std::endl;
}

template <typename T>
void print_universal_ref(T&& arg)
{
    using namespace boost::typeindex;
    std::cout << "T  : " << type_id_with_cvr<T>().pretty_name() << std::endl;
    std::cout << "arg: " << type_id_with_cvr<decltype(arg)>().pretty_name() << std::endl;
}

template <typename T>
void print_just_value(T arg)
{
    using namespace boost::typeindex;
    std::cout << "T  : " << type_id_with_cvr<T>().pretty_name() << std::endl;
    std::cout << "arg: " << type_id_with_cvr<decltype(arg)>().pretty_name() << std::endl;
}

void func4Transfer(int, double, float, char) {}



//������������
void understand_type_deduction_with_boost_library()
{
    //��ͨ���õ����
    int i = 202;
    print_type_template_parameter(i);
    const int a = 101;
    const int u = 303;
    const int& ur = u;
    print_type_template_parameter(a);   //const��ֵ����ģ�壬T��const int��arg��const int &
    print_type_template_parameter(ur);  //const��ֵ�����ô���ģ�壬T��Ȼ��const int��arg��Ȼ��const int &
    //��������������ģ����β�������������T&������������������͵�ʵ�Σ��������ûᱻֱ�Ӻ��Ե���Ҳ����˵��T�������ã����������η�����

    std::cout << std::endl;

    //�����const ��ֵ������Ϊ����ģ����βε����ͣ���const T&�������ڴ���const��ֵ�������͵�ʵ�Σ���ôT�ᱻ�Ƶ��ɷ�const��ֵ�����ͣ�arg��Ȼ��const��ֵ��������
    print_const_T_ref(ur);  //����Ĳ�����const int &���Ƶ������Ľ�������const �� &������T��int��arg��������Ȼ��const int &
    print_const_T_ref(u);   //����Ĳ�����const int���Ƶ������Ľ�������const

    std::cout << std::endl;

    //�����ָ����Ϊ����ģ����β����ͣ�������ָ�룬��õ����������ƵĽ��
    int valint = 648;
    const int* valintPtr = &valint;
    print_pointer(&valint);
    print_pointer(valintPtr);
    //������һ�㲻ͬ���ǲ��ܽ�int���͵Ĳ�������ȥ����Ϊ�������β�������ָ�룬�����ܷ�ָ��Ķ�����

    //�ܽᣬ����ģ������Ƶ��ᱣ֤�������յõ���ʵ�ʲ������ͣ����뺯���β��б��е�����һ�µģ�Ҳ����˵�Ƶ�������T������������ַ��Ż�ؼ��ֽ����һ��ģ���������ظ������δ�
    //  ��������Ĳ������ͽ�����T����ô�����ʵ��������ʲô��T���վ���ʲô
    //  ��������Ĳ���������T�����δʽ�ϵģ�����const T&����ô�����ʵ�����������const int&����ôT���վͻᱻ�Ƶ�Ϊint��const��&�ᱻ�����β������е�const��&����
    //  �����Ĺؼ��ʻ���ŵ��滻����Ҳ��һ����
    std::cout << std::endl;


    //�������õ����
    const int q = 2001;
    const int& qLref = q;
    print_universal_ref(q);     //������ֵ�����Ƶ�����������Ϊ��ֵ�����ã�����T��const int&��argҲ��const int&���ͣ�ԭ����&&�����ˣ�����Ϊ�����������۵��������ٽ�
    print_universal_ref(qLref); //������ֵ���ã��Ƶ�����ҲΪ��ֵ���ã�����T��const int&��argҲ��const int&����
    std::cout << std::endl;

    //���������ô���һ����ֵ
    print_universal_ref(101);     //������ֵ���Ƶ�����TΪ��ֵ��argΪ��ֵ��������int&&����Ϊʵ�����������ò�����һ���������ͣ����ǽ��ڷ��������Ƶ�ʱ�Ż���ܽ���
                                  //��ֵ����ֵ���ã����ܽ�����ֵ����ֵ����
    int&& Rref = 303;
    print_universal_ref(Rref);    //������ֵ���ã��Ƶ�����TΪ��ֵ���ã�argҲ����ֵ���ã�������Ϊ��ֵ���ñ����Ǹ���ֵ������right_value_reference.cppһ������������һ��
    std::cout << std::endl;

    //���������ô���һ����ַ
    std::cout << "����&xxx�����" << std::endl;
    print_universal_ref(&q);    //���������ô�����&q��ͨ��˵&xxx�õ��ľ���xxx�ĵ�ַ����ʵ����ȡַ��������һ����ֵ���󣬻᷵��ָ��ö����һ��ָ�룬���ָ���Ǹ���ֵ���Ǹ�������ֵ
                                //���� &q ������������ʱ��T������Ϊָ�����ͣ�T&&��һ��ָ�����͵���ֵ����

    //���������ô���һ��ָ��
    const int* qptr = &q;
    print_universal_ref(qptr);    //Ȼ��һ��ͨ����ָ�����͵Ķ�������ֵ�����������ô��⣬int a = 1�������1��������a���������͵ı���������˵���󣩣�����1����ֵ����������a����ֵ
                                  //��ô��ͬ�ģ�int* qptr = &q������ &q ��ָ�룬qptr��ָ�����͵ı���������˵ָ�����͵Ķ��󣩣�����ָ�� &q ����ֵ��ָ����� qptr ����ֵ
                                  //��˵��������������ô���һ��ָ��ʱ��ʵ������ָ����һ��ָ�����͵ı���������ֵ��T�Ƶ�Ϊָ�����͵���ֵ���ã������۵�������&&��ʧ��arg����ָ�����͵���ֵ��������
    std::cout << std::endl;


    //������ֵ���͵����
    const int p = 1225;
    const int& pref = p;
    //��ֵ����ֵ���ö����ƶ�Ϊ��ֵ�������const�ؼ������Σ�const�ᱻ���ԣ���Ϊ�ǰ�ֵ���ݵģ��յ��Ķ��Ǹ���
    print_just_value(p);
    print_just_value(pref);
    std::cout << std::endl;
    //���ǿ��Խ�ָ�봫�ݽ�ȥ������T�ͻᱻ�Ƶ�Ϊָ�����ͣ�����ָ��������˵����ָ�����const���Բ��ᱻ����
    const int* pptr = &p;
    print_just_value(pptr);
    const int* const pptrConst = &p;    //��һ��const��������ָ��ָ��Ķ��󣬼�������ָ�룬��˼��ָ�򲻿��޸Ķ����ָ�룬�������const�ᱣ�����ڶ���const����ָ�룬��ָ�����͵ĳ��������ᱻ����
    print_just_value(pptrConst);     //��Ϊ�ǰ�ֵ���ݣ��˴���ֵ�Ǹ�ָ�룬Ҳ����˵�����ָ�뱻������һ�ݣ���ôָ���const���Զ�ʧ
    //�������������׵�ַ�������Ƶ�����Ҳ��ָ�����ͣ�����������int���͵�ָ����һ�µ�
    const char cstr[10] = "hello";
    print_just_value(cstr);
    std::cout << std::endl;


    //��ͨ�������͵��βν�����������
    const char ccstr[10] = "world";
    //��Ϊ�ǰ����ô��ݣ����Դ˴ε�T�����Ͳ��ᱻ�ƶ�Ϊָ�룬�����������鱾������ͣ�����������
    print_type_template_parameter(ccstr);   //T�Ƶ�������const char[10]��arg�����;���const char(&)[10]��Ҳ����const char�������͵Ķ�������ã�
    std::cout << std::endl;


    //��������Ϊʵ�δ��ݵ����
    //��ֵ����
    print_just_value(func4Transfer);    //���ں�������ʵ���Ǻ����ĵ�ַ�����Ը���ָ�룬���Դ˴���ֵ����ʱT�ᱻ�Ƶ�Ϊ��Ӧ���͵ĺ�����ָ�룬��void (*) (int, double, float, char)
                                           //   arg�����������Ƶ�������T����
    //�����ô���
    print_type_template_parameter(func4Transfer);   //�����ǰ����ô��ݣ�����T���Ƶ�Ϊ��Ӧ�ĺ������ͣ���arg����T&�������������ͣ�������������void (&) (int, double, float, char)


    ///�ܽ�
    ///�����ƶ�ʱ��ʵ�ε������������&�����ƶϳ�����T�����ǲ���&�ģ�Ҳ����˵&�ᱻ���ԣ���ֵ���ûᱻ��Ϊ��ֵ����������ǰ����ô��ݵģ���ô�����б��еĲ���������T&����һ����������������
    ///�������õ�����У���ֵʵ������ֵʵ���ƶϳ����Ľ��T��ͬ��������ֵ����ֵ���ö����ƶ�Ϊ��ֵ���ã���Ϊ�ǰ����ô��ݡ�������ֵ��T���ƶ�Ϊ�����ֵ�����ͣ�����Ϊ�ǰ����ô��ݣ����Բ������;�����ֵ������T&&
    /// ������ֵ���ã�T��������;�����ֵ���ã���Ϊ��ֵ���ñ�������ֵ���˴����ǰ����ô��ݵ�
    ///��ֵ���ݵ�ʵ�Σ��������const����const�������ã���Ϊ������һ����const����ʱ�������Ӵ����ֵ����������������ָ��const�����ָ�룬���ƶϳ�����T��Ȼ��ָ��const�����ָ������
    ///�����������Ϊʵ�λᱻ�ƶ�Ϊָ�룬���Ǻ���ģ���ǰ����ô��ݣ����������������T�ᱻ�ƶ�Ϊ��Ӧ���͵�����
}
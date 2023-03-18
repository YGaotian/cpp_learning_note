#include "header_learning.h"
#include <boost/type_index.hpp>

template <typename T>
void print_universal_ref(T&& arg)
{
    using namespace boost::typeindex;
    std::cout << "T  : " << type_id_with_cvr<T>().pretty_name() << std::endl;
    std::cout << "arg: " << type_id_with_cvr<decltype(arg)>().pretty_name() << std::endl;
}

void reference_collapsing()
{
    int exampleLValue = 10086;
    int& exampleLValueRef = exampleLValue;
    int&& exampleRValueRef = 136516;
    print_universal_ref(exampleLValue);
    print_universal_ref(exampleLValueRef);
    print_universal_ref(76797);
    print_universal_ref(exampleRValueRef);
    std::cout << std::endl;
    //��ֵ����&����ֵ����&&��һ�����ͣ�����ֵ���ö��������������ֵ����&
    //�������ò�����һ�����ͣ�����һ�ֱ�ʾ�ú����Ĳ����ȿ��Խ�����ֵ����ֵ���ã�Ҳ���Խ�����ֵ���͵ı�־�������������߱�������������Ĳ����ǰ����ô��ݵ�
    //�����ǽ���ֵ����ֵ���ô����������õ�ʱ��T�ᱻ�ƶ�Ϊ��ֵ���ã�����T��xxx&������Ϊ�������õı�־&&����T�е�&�ͻᷢ���۵�����xxx& &&�۵���xxx&������arg���ƶ�Ϊxxx&����
    //�����ǽ���ֵ����ģ�壬T�ᱻ�ƶ�Ϊ��ֵ���ͣ���Ϊʵ��T&&������ֵ���ã�����T��xxx��&&����xxx������xxx����ֵ�������ͣ���arg���ƶ�Ϊxxx&&���ͣ������в�û�з��������۵�
    //���������ֵ���ã���ʵ�α�������ֵ���͵ģ�����T�ᱻ�ƶ�Ϊ��ֵ����xxx&��ͬ����&&����T�е�&�����& &&��Ȼ���۵�����&����xxx& &&�۵�Ϊxxx&������arg���ƶ�Ϊxxx&����

    //�����۵����򣬾������£�
    //  ��&&һ��������ֵ����&���ͻ��۵���&��������& &&����&& &�������һ��
    //  ֻ��&&������ֵ����&&ʱ���Ż��۵���&&
    //  ��&����&�����& &�����۵���&
    //һ���Ա�֮�����ǵ�������ֵ��������ʱ�����۵�����ֵ���ã�����֮���κ��������������۵�����ֵ���ã��������������Ҳ����ָ������һ�����õ�����
    //���ǲ���ֱ�Ӵ������õ����ã����ǲ��Ϸ��ģ������ں���ģ��ʹ����������ʱ�������Ƶ��У����õ����ûᱻ�Ƶ���������ʱ�������ͻ�ʹ�������۵�����������
    //������ˣ����ǻ�����ͨ�����ͱ�����Ӵ������õ����ã���������������Ҳ�ᷢ�������۵��������۵�������move֮��ı�׼����ʩ������ȷ�����Ļ���
}


template<typename F, typename Q>
void callerTemplate(F func, Q&& arg)
{
    std::cout << "original arg is: " << arg << std::endl;
    func(arg);
    std::cout << "then arg is: " << arg << std::endl;
}

void factoryFunc_1(int& ag)
{
    ag += 100;
}

void basic_forwarding()
{
    //ת���ĸ������ָ���Ǵ���һ������ģ�壬���ģ�����һ���ص�����������ģ�彫�����ܵ�������������ص������У�������̾���ת��
    //������ǵĺ���ģ����յĲ�������ͨ��ֵ���ͣ����ǵĻص��������յĲ���Ҳ��ֵ���ͣ���ôһ�ж������ú�����
    //��������ǵĻص��������ܲ����������ã����������ĺ���ģ�岢�������ô�ֵ����ô�ͻᵼ�»ص�������û��ʹ��ԭ����ʵ�Σ�����ϣ����ԭ����ʵ��ԭ�ⲻ����ת�����ص�����
    //��ˣ�������Ҫ�õ��������ã����ܹ������κ����ͣ���ֵ/��ֵ����/��ֵ���Ĳ������Ӷ������ܵõ���ʹ��ԭʼ������
    int numericVariable = 2000;
    callerTemplate(factoryFunc_1, numericVariable);
    std::cout << std::endl;
}


//��������������������Ϊ���factoryFunc�Ĳ�����������ֵ���ã�Ҳ����˵��Ҫ����һ����ֵ����ô��������callerTemplate������ֵʱ��ʵ�ε�����ģ���лᱻ�ƶ�Ϊ��ֵ����
//����ģ���ڲ��������ٴ����ص�����ʱ��������ֵ���ö���������ֵ�����޷��󶨵��ص���������ֵ�������͵Ĳ�����ȥ��
//��ˣ�������Ҫʹ���µļ�����������ת��������������ǵĺ���ģ������������͵�ʵ�Σ�����ʵ�ΰ�ԭ��ת����Ŀ�꺯�������е���ֵ/��ֵ/����/const�����ᱻ�ı�
//����ת����Ҫ�õ�std::forward������רΪת��������ĺ���ģ�壬��������յ��Ĳ�������ԭ������ֵ�����ͷ�����ֵ�����ԭ������ֵ�����ͷ�����ֵ
//������ʵforwardֻ��ʵ��ԭ������������ֵ���������
template<typename Ftype, typename Qtype>
void perfectCallerTemplate(Ftype func, Qtype&& arg)
{
    //ʹ������ת��forward���ɽ���ֵ����ֵԭԭ�����ش���Ŀ�꺯��
    func(std::forward<Qtype>(arg));
    //��ӡһ��arg����������Ĳ������;�����ͨ��ת���������ֵ
    ::print_universal_ref(arg);
    //��ӡһ�¾���forward����ת����arg������������ȷʵ���������Ĳ��������ͻ�ԭΪ����ֵ
    ::print_universal_ref(std::forward<Qtype>(arg));
}

void factoryFunc_2(int&& ag) 
{
    std::cout << "this function received a rvalue and now is working normally" << std::endl;
}

void perfect_forwarding()
{
    perfectCallerTemplate(factoryFunc_2, 90);
}



//������������
void reference_collapsing_and_perfect_forwarding()
{
    reference_collapsing();
    basic_forwarding();
    perfect_forwarding();
}
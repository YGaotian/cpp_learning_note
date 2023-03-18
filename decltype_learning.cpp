#include "header_learning.h"
#include <boost/type_index.hpp>
#include <functional>

//decltype���Է��ز��������������ͣ����������ƶ�Ҳ�����ڱ����ڣ�decltype��������������ʽ��ֵ

class someclass
{
public:
    int qint;
};

double returnDouble()
{
    std::cout << "return double" << std::endl;
    return 1234.567;
}


auto autoTypeFunc(int& i)
{
    i *= 2;
    return i;
}

decltype(auto) declAutoTypeFunc(int& i)
{
    i *= 2;
    return i;
}

void decltype_learning()
{
    const decltype(1) constint = 125;   //decltype()�����п�������ֵ�����Ƶ�������Ĳ�������������
    decltype(constint) cint = 251;  //decltype(constint)�Ľ������const int�����decltype����������һ���������������const���Բ��ᱻ����������auto��һ��
    const int& constintRef = constint;
    decltype(constintRef) ciref = constintRef;  //���decltype()�������Ǹ����ã���const��&�����ᱻ����
                                                //Ҳ����˵auto�����ǵȺ��ұߵ�ֵ��������ݵ����ͣ���decltype�ǿ����������������
    //decltype���ܽ����Ա������������
    decltype(someclass::qint) scint = 12;
    someclass scinst;
    decltype(scinst.qint) scinstInt = 13;
    auto&& scinstRef = scinst;  //scinstRef��someclass &���ͣ���Ϊ�������۵�
    someclass scinst2;
    decltype(scinstRef) && scinst2Ref = scinst2;    //scinst2Ref�� someclass & ���ͣ���ΪscinstRef�� someclass & ���ͣ�����&&�ַ����������۵���������Ȼ��someclass &����
    std::cout << boost::typeindex::type_id_with_cvr<decltype(scinst2Ref)>().pretty_name() << std::endl;

    //decltype�ĵ�������Ҳ������һ�����ʽ
    decltype(constintRef + 1) k = 90;   //constintRef�Ǹ��������ͣ����� constintRef + 1 �ͱ����һ�����ʽ��������ʽ�Ľ����һ���������ͣ�����k��int���ͣ����Ա���ֵ
    int w = 122;
    int* wptr = &w;
    ///decltype(*wptr) e = 12;  //����
    decltype(*wptr) e = w;  //Ϊʲô����Ļᱨ������һ��ȴ���������أ���Ϊwptr��һ��ָ�룬��*wptr�Ǹ����Ա���ֵ�ı��ʽ������*wptr�Ǹ���ֵ
                            //���һ�����ʽ������Ϊ��ֵ���Ⱥ���ߵ�ֵ����ô�Ըñ��ʽʹ��decltype���صľ��Ǹ����ã�����decltype(*wptr)�õ�����һ��int&���ͣ�������w�������������int
    std::cout << &w << " " << &e << std::endl;
    //����ڱ������������һ�����ţ���ô��ͱ����һ�����ʽ����decltype�ͻ��ƶ�Ϊ��������
    decltype((w)) r = w;

    //decltype�л����Է��뺯������
    decltype(returnDouble()) doubleVar = 123.456;   //��ô�����ƶϳ���������ֵ�����ͣ�Ҳ����double������ʵ��������ĺ��������������ı����ã���Ϊ�����Ǳ����ھ��ƶϳ�����
    //decltypeҲ����ֱ�ӷ��뺯�����������ƶϳ����ľ��Ƕ�Ӧ�Ŀɵ��ö���������
    decltype(returnDouble) rdCallable;   //ע�⣬�ƶϳ����Ĳ����Ǻ���ָ�����ͣ����������������double(void)��������double(*)(void)�����Բ��ܽ�returnDouble
    //���������Ҫ��decltype�Ƶ��������������Ӻ��������ǿ���ʹ��std::function<>��ģ��
    std::function<decltype(returnDouble)> rdFunction = returnDouble;
    rdFunction();

    //decltypeҲ������auto����ʹ�ã�������β�÷������;������е�һ��Ӧ��
    /// template <typename T>
    /// auto func(T arg) -> decltype(arg) {}
    //������һ��ʹ�ã�������������ʽ�ģ�decltype(auto)����������auto���Ƶ������ķ���ֵ���͵�ʱ��auto���ƶϳ�ֵ���ͣ���Ϊauto�ƶϺ�������ֵ����ʵ�����൱����autoȥ�ƶ�return����Ķ���
    //��һ���Ѿ���auto_learning.cppһ�ڽ��͹�����ôҲ����˵�ƶϽ�����Ǹ�������ֵ���ͣ������������ͣ�����һ�����������ڷ��صĲ������ã���˺������õĽ�����Ǹ��޷�ȡ�õ�ַ����ʱ����Ҳ������ֵ
    //�����autoTypeFunc�����ĺ����������������뷵�ش����ʵ�ε����ã������Ļ�����һ����ֵ���ǿ��Ա���ֵ�ģ�������Ϊ�õ�auto���ƶϺ����ķ������ͣ���˷��ص���һ����ֵ���޷�����ֵ
    int integernum = 12;
    /// autoTypeFunc(integernum) = 10;  //����
    //���ϣ���������������ֵ��Ӧ���ֶ��Ľ���������дΪ��ֵ����
    //����Ҳ���Ի�һ��д��������ʹ��decltype(auto)
    declAutoTypeFunc(integernum) = 10;  //decltype(auto) func()���൱�ڽ�������return����Ķ������뵽auto��λ�ã������return x����ô������ǰ�����decltype(x)
                                          //�����Ļ�����x��ʲô���ͣ�������ͨ��decltypeԭ�ⲻ�����Ƶ���������Ҳ�Ƿ���decltype���Ƶ�����ģ�decltype(auto)�� c++ 14 ������
    std::cout << integernum << std::endl;
    //���Ƶģ�decltype(auto)Ҳ�������ڱ��������У�����������һ��
    //�������ں����ﴴ����һ���ֲ�����local������д�� return(local)���������ʹ�õ���decltype(auto)����ô�ͻὫ����ֲ���������÷��س����������ʱ��������Ĵ���һ����������������ý����˸�ֵ
    //��ʱ��������һ���Ѿ��ͷŵ����ڴ��ϸ�ֵ��������Ϊ�����ĺ���ǲ���Ԥ�ϵ�
}
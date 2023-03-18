#include "header_learning.h"
#include <functional>

class Functor4Save
{
public:
    Functor4Save()
    {
        m_intl = 999;
    }
    Functor4Save(int l)
    {
        m_intl = l;
    }
    void operator()(int i)
    {
        std::cout << i + m_intl << std::endl;
    }

public:
    int m_intl;
};

void printOrigin(int a)
{
    std::cout << a << std::endl;
}

void printSth(int)
{
    std::cout << "An integer is received" << std::endl;
}

void printSth(std::string)
{
    std::cout << "A string is received" << std::endl;
}

void stlFunction_learning()
{
    Functor4Save f4s1(21);
    Functor4Save f4s2(35);
    std::map<std::string, Functor4Save> functorMap;
    functorMap.insert({ "functor1", f4s1 });
    functorMap.insert({ "functor2", f4s2 });
    functorMap["functor"](55);  //����һ�������ڵļ���������Ĭ�Ϲ��캯����Ȼ��ִ����Ĭ�ϵķº���ʵ������
    functorMap["functor1"](10);
    functorMap.at("functor2")(30);
    //���ϵĴ��������map���Խ���������Ҳ���Ƿº�����������ֻ��Ҫ���º�����������Ϊ��ֵ���е�ֵ���ɽ��ܺ�������
    //���ڵ���ʱ�������±����������at()�еļ��������Ӧ�ķº������������mapһ���������ڵļ�����ô�����Ĭ�Ϲ��캯��������һ��Ĭ�ϵķº�������Ȼ����е���
    //����Ĭ�Ϲ��캯������Ҫ����һ��Ҫ�еģ����û��Ϊ�º�������Ĭ�Ϲ��캯����Ҳû�кϳɵ�Ĭ�Ϲ��캯������ô�����Ǵ���map�ͻᱨ��
    //����Ҳ���Ը�mapһ�������ڵļ�����Ϊ����ֵ����������Ϊ�Ϳ��Դ�����insert����
    functorMap["functor3"] = Functor4Save(100);
    functorMap["functor3"](80);
    std::cout << std::endl;

    //����뽫һ��void(int)���͵ĺ�����ָ��������map�����ǵļ�ֵ���е�ֵӦ��дvoid(*)(int)
    //�������ķº�����ʵҲ���޷���ֵ�ҽ���һ��int�����ģ�������ȴ�޷�ֱ�ӽ��������������ָ��map����Ϊ�º����Ͼ��뺯��ָ�����Ͳ�ͬ
    std::map<std::string, void(*)(int)> functionMap;
    functionMap["function"] = printOrigin;
    functionMap["function"](123);
    Functor4Save f4s3(64);
    ///functionMap.insert({ "functor", f4s3 });    //�޷���ô�����ᱨ��
    //���Ҫʵ��������Ŀ�ģ����ǿ��Խ�����ģ��std::function�������ǵķº�����װ��һ��function���ͣ������ģ�嶨����ͷ�ļ�functional��
    //��ģ�������������ϣ����װ��Ϊ�� ������ ���ͣ�����˵����ֵ�����������꣬��packaged_task����ģ�����һ��
    //����˵����ķº�����һ���޷���ֵ�ҽ���һ��int�����Ķ�����ô���Ǿ��������װ��һ���޷���ֵ�ҽ���һ��int������function�����
    std::function<void(int)> f4s_Function = f4s3;
    //std::function�������Խ��շº����������Խ��պ���ָ��
    std::function<void(int)> printOrigin_Function = printOrigin;
    //����������װ�õ�function���󶼿�������һ��ֱ�ӵ���
    f4s_Function(300);
    printOrigin_Function(212121);

    //�����Ļ����ǾͿ���ֱ�ӽ�std::function<void(int)>��Ϊ��ֵ���е�ֵ������һ��map�����map���ܹ�ͬʱ�洢�º����ͺ���ָ��
    std::map<std::string, std::function<void(int)>> callableMap;
    //��һ�д�����ʾ����һ�����ɼ�ֵ�Եķ���������ͨ��map��value_type�����ɺ��ʵ�pair���������ֶ�ָ����Ҫ���ɵ�pair�ļ�ֵ������
    //���������string-function���͵�pair��ֻ��Ҫ��ʵ�ʵ�string�����function����ʵ����Ϊ��������value_type���ɣ���ʵ�����ַ���Ҫд�Ĵ��뻹���е��ģ��о�û��Ҫ
    callableMap.insert(std::map<std::string, std::function<void(int)>>::value_type("functor", f4s_Function));
    callableMap["function"] = printOrigin_Function;

    //ͨ��map���ú����ͷº���
    callableMap["functor"](500);
    callableMap.at("function")(777);

    //�������һ�����������ذ汾���Ǿͻᵼ���޷�������functionģ���װ�����������������ģ���ڲ��Ĵ�����Ƶ����˶���������Ĳ���
    ///std::function<void(int)> printSth_Function = printSth;   //����
    //����������ú���ָ��ָ�����������Ȼ�󽫺���ָ���װ����
    void (*printSthVI_ptr)(int) = printSth;
    std::function<void(int)> printSth_Function = printSthVI_ptr;
    printSth_Function(1);
}
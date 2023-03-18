#include "header_learning.h"
#include <stdarg.h>

//�ܹ����ܷǹ̶����������ĺ�����Ϊ�ɱ��������
//���ǿ��Խ�����׼����ģ��initializer_list��ʵ����һ���ܣ������Ϳ���ʹ�õ�ǰ��������ʵ�ε����Ͷ���ͬ
//initializer_list�������Ϊĳ�����͵�ֵ��������б�һ��������ʼ��֮�������Ԫ�ض��ǳ��������޷����޸��ˣ��е�����python��Ԫ�飬���������������β�

void variadic_function_1(std::initializer_list<std::string> initlist)
{
    for (auto iter = initlist.begin(); iter != initlist.end(); iter++)
    {
        std::cout << *iter << std::endl;
    }
    std::cout << "Total " << initlist.size() << " arguments received" << std::endl;
}

class TestElement4VariadicFunction
{
public:
    TestElement4VariadicFunction() = default;
    TestElement4VariadicFunction(const TestElement4VariadicFunction& tevf)
    {
        std::cout << "copied" << std::endl;
    }
};


//�������潲�ķ���������һ��ʵ���˿ɱ���������Ĺ��ߣ���ʡ�Ժ��βΣ�...
//ʡ�Ժ��β���C���Ե�д����Ӧ�ý�����C��C++���Ӳ��ֵĺ���
//ʡ�Ժ��β��޷������Զ������͵Ĳ�������ֻ�ܴ���򵥵����ͣ���int��char*��
//ʹ��ʡ�Ժ��βεĺ��������Ĳ����Ǵ洢������������ջ�ռ��еģ����������ĺ�������������һ����ͨ��������������ͨ�������ͨ�Ĳ����Ժ��������в���Ѱַ���õ����ǵ�ֵ������
//Ϊ��ʹ��ʡ�Ժ��βΣ���Ҫ������ͷ�ļ� stdarg.h
void getAll(double num, ...)    //���Բ�д����
{
    //������Ҫʹ��һЩ����õĺ�
    va_list ls;    //va_list��char*�����ͱ���
    va_start(ls, num);  //ָ��va_list�б����ʼ����Ϊnum����Ϊ�ɱ�������������в����ĵ�ַ���������ģ����Ժ����Ĳ��������Դ���ʼ����num��ʼѰַ
                        //��������б��к��ж����֪���βΣ���va_start�ĵڶ�������Ӧ�ô��뺯�������һ����֪������Ҳ����...ǰ�����һ����������ָ����Ϊ�ɱ�����б����ʼ����
    for (int i = 0; i < num; ++i)
    {
        std::cout << va_arg(ls, double) << std::endl;   //va_arg�ĵ�һ�������ǿɱ�����б��ڶ������������в��������ͣ�ÿ�ε���va_arg����ʹ�����Ľ�������һλ�����Բ�Ҫ����ȥ�������ж�
                                                        //�����ʹ��ͬһ��ѭ���У�va_arg�Ľ�����ƫ�ƶ�Ρ�va_arg�����͵�Ҫ��ʮ���ϸ���һ��ʼָ��Ľ���ǿɱ�����б��еĵڶ���
                                                        //����˵����������ʱ����ĵ�һ�����������ǲ����б�ĳ��ȣ�����ָ��ѭ�����������ӵڶ���������ʼ�����ͱ������β����͹ؼ���һ�£����д��double��
                                                        //�Ǵ���Ĳ����ͱ�����x.x������3.0��������д3���˴���������ʽ����ת�������Ҵӵڶ�������һֱ�����һ����������Ŀ�������һ������д��������һ��
                                                        //������ˣ��������ѭ���ͻ��ӡ������
    }
    //�������Ҫ��va_list������ͷŵ�
    va_end(ls);
}
//ʹ���ַ������͵�����
void printAsIntPlusOne(const char* str...)
{
    va_list ls;
    va_start(ls, str);
    for (int i = 0; i < atoi(str); i++)    //atoi��c���������ڽ��ַ����е�����תΪ����
    {
        std::cout << 1 + atoi(va_arg(ls, const char*)) << std::endl;
    }
    va_end(ls);
}



void variadic_function_learning()
{
    //��Ҫ��initializer_list�βδ���һ���������У������Ȱ����з���һ����������
    variadic_function_1({"hello", "world", "hello", "you"});

    //����һ��initializer_list����Ϊ�丳ֵ�������´�����е�Ԫ�أ�Ҳ����˵����initializer_list�ǹ�����ͬ��Ԫ�ص�
    TestElement4VariadicFunction tevf1;
    TestElement4VariadicFunction tevf2;
    std::initializer_list<TestElement4VariadicFunction> TEinitList{ tevf1, tevf2 };
    std::cout << "����initializer_list��" << std::endl;
    std::initializer_list<TestElement4VariadicFunction> TEinitList_2 = TEinitList;  //��û�������б���Ԫ�صĿ�������
    std::cout << "������ֵ���" << std::endl;

    //ʡ�Ժ��β�
    getAll(9, 2.3, -3.4, 3.2, 1.0, 4.2, 6.0, 5.5, 6.4, 8.8);
    printAsIntPlusOne("5", "1", "2", "42", "27", "12");
}

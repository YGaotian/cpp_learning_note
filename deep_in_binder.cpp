#include "header_learning.h"
#include <functional>

//��֮ǰ���½����Ѿ���Ҫ�ؽ��ܹ���functionalͷ�ļ���function����ģ���ʹ��
//����functionҲ�������������飬����˵���Ա�������޷���function����װ��������Ϊ�������Ա������Ҫ��ʵ���Ĳ���

//֮ǰ������std::bind<>�����ã����Խ��ɵ��ö���Ͳ�������һ��bind��function��ͬ�������԰����Ա����ָ�룬bind����󷵻�һ���ɵ��õĶ���Ҳ������function��װ����

void func4Binder_1(int a, int b, int c)
{
    std::cout << a << b << c << std::endl;
}

void func4Binder_2(int& numref1, int& numref2, int& numref3)
{
    numref1++;
    numref2++;
    numref3++;
}

class MemberFunction4BinderClass
{
public:
    MemberFunction4BinderClass()
    {
        std::cout << "construct" << std::endl;
    }
    MemberFunction4BinderClass(const MemberFunction4BinderClass& mc)
    {
        std::cout << "copy" << std::endl;
    }
    void memberFunction(int a)
    {
        std::cout << "print a: " << a << std::endl;
    }

public:
    int member = 0;
};

void deep_in_binder()
{
    auto bindedFunction_1 = std::bind(func4Binder_1, std::placeholders::_1, 12, 25);
    bindedFunction_1(2001);   //��Ϊʹ����placeholders�����������ڵ��ú�����ʱ����Ҫ�ֶ������һ���������ڶ������������Ѿ��󶨺��ˣ��������ٴδ���
    //ע�⣬����Ĵ����У�placeholder::_1��placeholders::_2������Ҫ����_1��_2������ţ�������λ�ã�����_1�ڵ�һ��������λ���ϻ��ǵڶ�������������λ����
    //placeholders::_1 ���������Զ���ǵ���ʱ����ĵ�һ����������ͬ�أ�placeholders::_2��Զ���������ʱ����ĵڶ�������
    //�ٸ����ӣ��������д���� biFunc = std::bind(oriFunc, placeholders::_2, placeholders::_1)
    //�������ֵ��õĽ����һ���ģ� biFunc(A, B) <=> oriFunc(B, A)
    auto bindedFunction_2 = std::bind(func4Binder_1, std::placeholders::_2, std::placeholders::_1, 18);
    bindedFunction_2(706, 197);

    //bind����Ԥ�Ȱ󶨵Ĳ���ʵ�����ǰ�ֵ���ݵģ�Ҳ����˵��������ð󶨵������ϣ���ôʵ���ϻ����һ���������ڵ��õ�ʱ�򲻻���κ�Ԥ�Ȱ󶨵����ö�������޸�
    //��˶�����Ҫ��������Ϊ�����ĺ������ԣ�������ζ��ǲ����յ�Ԥ�󶨵Ķ�������õģ�����ֻ���ֶ��������ڵ��õ�ʱ���룬���������յ�����
    int anum = 10, bnum = 20, cnum = 30;
    int& bnumref = bnum;
    std::bind(func4Binder_2, std::placeholders::_1, bnumref, cnum)(anum);   //bnumref�Ǹ����ã���Ԥ��ʹ���������˸���������bnum���ᱻ�ı䣬cnumҲ���ᰴ���ô���
    std::cout << "anum: " << anum << " bnum: " << bnum << " cnum: " << cnum << std::endl;

    //��ʾһ�°󶨳�Ա�����ķ���
    MemberFunction4BinderClass mf4bc;
    auto bindedMemberFunc_1 = std::bind(&MemberFunction4BinderClass::memberFunction, &mf4bc, 32);   //��������̴߳��ݺ�����������ƣ�Ҳ�Ǵ����Ա�����ĵ�ַ��Ȼ����ʵ������
                                                                                                    //Ҳ����ֱ�Ӵ� &inst�������Ͳ��ᷢ������
    bindedMemberFunc_1();
    
    //����һ�������д����bind�󶨵ĺ���������function���ӣ�Ȼ��bind���������԰󶨺����������԰󶨳�Ա��������ͨ�������У���Ȼ�������Ա������function���ӣ�Ҳ����˵��������һ����Ա����������
    std::function<int&(void)> intMemberAsFunction = std::bind(&MemberFunction4BinderClass::member, &mf4bc);    //ע������Ҫ������ʵ����������ã�����ͻ����ɸ��������һ���������
                                                                                                               //��һ���ǵ���ʱ��������ʱ�������ڶ�����bind�ڲ����������Ҫ������ʱ����ĸ���
                                                                                                               //��˺������κβ��������ڸ����Ͻ��еģ��޷�Ӱ�쵽ԭ����member
    //����Ĵ��뽫int���͵�member����һ����Ա������std::function���������ˣ�function�����int������һ������ֵ����Ϊint&���������κβ����Ŀɵ��ö������ǿ��������������ı�member��ֵ
    intMemberAsFunction() = 2222;
    std::cout << intMemberAsFunction() << " == " << mf4bc.member << std::endl;

    //�����һ����ʱ�����bind����ô�ͻ����һ�ι��캯��������ʱ����bind������󻹻��ٵ���һ�ο������캯��������ʱ����ĸ���������
    auto tempBindedFunc = std::bind(MemberFunction4BinderClass());
}
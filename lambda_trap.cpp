#include "header_learning.h"
#include <functional>

class LambdaTrapTest
{
public:
    LambdaTrapTest(int a) : mTest(a)
    {
        std::cout << "LambdaTrapTest created" << std::endl;
    }
    ~LambdaTrapTest()
    {
        mTest = 0;
        std::cout << "LambdaTrapTest destoryed" << std::endl;
    }

public:
    int mTest;
};

namespace LAMBDA_TRAP
{
    std::vector<std::function<void(int)>> Fvec;

    void trigger_trap()
    {
        LambdaTrapTest ltt(323);
        LambdaTrapTest* lttp = &ltt;
        Fvec.push_back([&](int c)
        {
            lttp->mTest += c;
            std::cout << ltt.mTest << std::endl;
        });
    }

    class LambdaInClass
    {
    public:
        void trap()
        {
            Fvec.push_back([=](int c) mutable
            {
                member += c;
                std::cout << member << std::endl;
            });
        }

        void trapSolved()
        {
            auto memberCopy = member;
            Fvec.push_back([=](int t) mutable
            {
                memberCopy += t;
                std::cout << memberCopy << std::endl;
            });
        }

        void lambdaWithStaticLocalVar()
        {
            Fvec.push_back([](int u)
            {
                    std::cout << smember << std::endl;
            });
            smember++;
        }

    public:
        int member = 90;
        static int smember;
    };

    int LambdaInClass::smember = 50;
}



void lambda_additional_analysis()
{
    using namespace LAMBDA_TRAP;
    trigger_trap();
    //����ltt����trigger_trap�����ж���ľֲ�����������һ�д���������֮��ltt���Ѿ����ͷ��ˣ���Ӧ��ltt.mTestҲӦ�ñ��ͷ��ˣ����ԾͲ�Ӧ���ٱ�ʹ����
    //Ȼ��lambda���ʽ�����ȴ��ltt�����ã�Ҳ����˵����һ�д����һ���Ѿ����ͷ��˵��ڴ渳��ֵ������������Ԥ�ϵĺ��
    Fvec[0](28);

    //lambda���ʽ���β��б������auto���Զ��ƶ��β����ͣ�Ҳֻ��lambda���ʽ��������д�������Ǵ�c++14��ʼ����д��

    LambdaInClass* lic = new LambdaInClass();
    lic->trap();
    delete lic;
    //�������������Ա������lambda��ʹ����=��ϣ����ֵ����ʹ�����Աmember�ĸ�����������ʵ�ʵ���ʱȴ���ִ�ӡ������member��Ȼ�����룬Ҳ����˵�����member���ų�Ա����trap�Ľ�����������
    Fvec[1](8);
    //lambda���ʽ�����������һ�����ֻ������ڶ���lambda���ʽ���������ڿɼ��ġ��Ǿ�̬�ľֲ������������βΣ��ģ���member�����Ա�������������ڷǾ�̬�ֲ�����
    //��Ա����ʵ�����ǲ���Ҳ���Ǳ����񵽵ģ������б���дһ�� = �ȼ���дһ�� this������д��������������ʵ�ǣ���ֵ�������thisָ�룬�����д this û�в������lambda�ڲ�ʹ�õĳ�Ա������Ȼ���Ǹ���

    //�������������lambda���ʽ����֮ǰ����һ����Ա�����ڵĳ�Ա���󸱱��������Ļ���lambda���ʽ�а�ֵ���񸱱����ɣ��Ͳ�����Ϊ��Ա����������ʵ�����ٶ�����޷�ʹ��
    LambdaInClass* lic2 = new LambdaInClass();
    lic2->trapSolved();
    delete lic2;
    Fvec[2](666);

    //generalized lambda capture������lambda����c++14�����ԣ�Ҳ���������������Ĳ�׽���Ա�����⣬���ǽ������б���� = �ĳ����Ƹ�һ����ʱ������ֵ����䣬�൱�ڽ����������Ĳ��輯�ɽ��˲����б�
    ///lambda���ʽ��Ҫ��ôд��[tempValue = member](int k) { tempValue += k; std::cout << tempValue << std::endl; }

    //��ǰ�����ǽ�����lambda���ʽ�ǲ�����̬�ֲ������ģ�������lambda_learning.cppһ������Ҳ˵������̬�ֲ������ǿ�����lambda��ʹ�õģ����洢�ھ�̬�洢������������һֱ�������������
    //��ˣ�������lambda���ʽ�����ʹ���˾�̬�ֲ��������������õľ��������������Ǹ�����ͬʱ�����������Ǳ�lambda���ʽ����ģ�����lambda�еõ��ľ�̬�ֲ�������ֵ��lambda����ʱ��ֵ
    LambdaInClass* lic3 = new LambdaInClass();
    lic3->lambdaWithStaticLocalVar();
    delete lic3;
    Fvec[3](20);    //�����51
    
}
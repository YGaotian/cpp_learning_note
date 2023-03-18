#include "header_learning.h"

class TestType4Lambda
{
public:
    TestType4Lambda() = default;
    TestType4Lambda(const TestType4Lambda&)
    {
        std::cout << "copy" << std::endl;
    }
    TestType4Lambda(const TestType4Lambda&&) = delete;

public:
    int m = 4;
};

class WhateverExampleClass
{
protected:
    int whatever = 10000;

public:
    void whateverFunc()
    {
        auto whateverLambda = [this]
        {
            ++whatever;
        };
        whateverLambda();
        std::cout << whatever << std::endl;
    }

    void whateverFunc_2(int y)
    {
        auto whateverLambda = [this, y]
        {
            std::cout << y << std::endl;
            std::cout << whatever << std::endl;
        };
        whateverLambda();
    }

    void whateverFunc_3(int x)
    {
        int a = 3, b = 4, c = 7;
        auto lambda = [=, &x]
        {
            //a++;  ����a�ǰ�ֵ�����
            x++;
            std::cout << a << b << c << x << std::endl;
        };
        lambda();
    }
};

//lambda���ʽ��������һ�������������ҿ��Բ���һ����Χ�ڵı���������ͨ������ͬ���ǣ�lambda���Զ����ں������ڲ�
void lambda_learning()
{
    //����һ��lambda���ʽ����ͷ����Ҫ��һ�Է����ţ���Ϊ�����б�������Բ���ţ�Բ���������������βεģ���֮���Ǻ��÷������ͣ�����ǻ����ţ�����д�Ϻ����壬��������
    auto lmd = [](int a = 777) -> int
    {
        a += 1;
        return a;
    };  //ע��Ҫ�зֺŽ�β
    //���÷�ʽ������ͨ�ĺ�������һ��
    std::cout << lmd(235) << lmd() << std::endl;
    //���һ��lambdaû�в����������б�(xxx)�Ϳ���ʡ�Բ�д������������ͱȽϼ򵥣��ǿ��Բ�д���÷������ͣ����������Զ��ƶϣ�Ҳ����˵��������д��Ҳ�ǺϷ���lambda���ʽ
    auto lambdaBrief = [] { return "hello"; };
    std::cout << lambdaBrief() << std::endl;


    //�����б���lambda��������һ����Χ�ڵı����ģ���Χ��ʲô�أ�
    //�ڴˣ����ں����ڶ���һ���ֲ�������һ����̬����
    int localVariable = 10;
    static int staticVariable = 20;

    //�����б�[]Ϊ�յ�lambda�޷����ض�������ͬ�����ڵľֲ���������ʵ����˵�����б�Ϊ�վ��ǲ�����ǰ�������ڵ��κα�������̬�������⣬��ǰ������֮��ı����ǿ��Բ��񵽵�
    auto captureListLambda_1 = []
    {
        ///return localVariable;  //����
        return staticVariable;    //����
    };

    //�����б����и�ȡַ������������[&]�����ǲ���ǰ���ⲿ�������ڵ����б������������ô�����lambda�������ڲ�ʹ�ã�������ⲿ�����򲻰����ⲿ�������ڵ���һ�����������������ж���ı�������ͬ
    auto captureListLambda_2 = [&]
    {
        std::cout << localVariable << std::endl;
        localVariable++;
    };
    captureListLambda_2();
    std::cout << localVariable << std::endl;

    TestType4Lambda tt4l;
    //�����б����и��Ⱥţ���������[=]�����ǲ���ǰ���ⲿ�������ڵ����б���������ֵ���ݣ����ɸ�����lambda��������ʹ�ã�Ҳ����˵ֻ�ܶ�ȡ������ֵ�����ǲ����޸���
    auto captureListLambda_3 = [=]
    {
        std::cout << localVariable << std::endl;
        ///return ++localVariable;   //���������localVariable���ǿ��޸ĵ���ֵ����ʵ�Ǹ�const int
        std::cout << tt4l.m << std::endl;   //ȷʵ�����˿������������˸���
    };
    captureListLambda_3();

    //�����б�����this��[this]һ���������У���ʾ��lambdaӵ�������Ա������ͬ�ķ���Ȩ�ޣ����ʹ����[=]��[&]����Ĭ�Ͼ�ӵ��[this]��������˵����[this]������lambda����ʹ�õ�ǰ������г�Ա�����ͳ�Ա����
    WhateverExampleClass wec;
    wec.whateverFunc();

    //�����б�����һ�������ö��ŷָ��ı�������[arg1, arg2, arg3]�����ǰ�ֵ������Щ���������Ҳ��������������������Ҫ�����ò��񣬿�����ô����[&arg]
    //����һ��thisֻ���ܲ�����ĳ�Ա���ѣ���������ʹlambda���Բ���lambda���ڵĳ�Ա�����еı�������Ϊ��Ա�����еı�����������ĳ�Ա
    //��˿�����lambda�Ĳ����б���д�ϳ�Ա�����ڶ���ı��������߳�Ա�������β�������Ϊʲô����=��&�أ���Ϊ��ô���ͻᲶ�����еı�������������Ƚ϶࣬��ô������������Ŀ���
    wec.whateverFunc_2(777);

    //�����б����õȺſ�ͷ�������&xxx��[=, &argA]��ʾ�����ò���argA������ֵ�����������б����������б��п�ͷ��λ�ñ�ʾ����Ĭ�ϵĲ���ʽ
    wec.whateverFunc_3(678);

    //����һ���ǿ�ͷ�����ã�֮����Ǳ�������[&, argName1, argName2]����Ȼ��Ĭ�ϰ����ò������б���������argName1��argName2�ǰ�ֵ�����

    //lambda���ʽ�ڶ����ʱ����Ѿ���ʼ��������ˣ�������������һ����ֵ���������lambda���ʽ���ڶ�����ɺ�û���������ã������ȸı��˱�����ֵ�Ļ�������lambdaʱ��ʹ�õ���Ȼ�Ǳ���ԭ�ȵ�ֵ
    {
        int xVar = 909;
        auto lambdaXVar = [=]   //�������ܵ���һ��ʱ�����Ѿ������˱����������ǵȵ�lambda����ʱ�Ų���
        {
            std::cout << "xVar = " << xVar << std::endl;
        };
        xVar++;
        lambdaXVar();   //��ӡ���ΪxVar = 909������910
        std::cout << "The actual value of xVar is " << xVar << std::endl;
    }

    //����˵������ֵ��������õ�����ʵ�Ǹ�const��������������ǰѧ��mutable�ؼ��֣���ʹ�ñ����εı��������ڳ������б����¸�ֵ����������ĳ�Ա�������Ҳ����mutable���εģ�Ҳ��Ȼ���Ա����¸�ֵ
    //��lambda���ʽ�У�����Ҳ����ʹ��mutable�������Ϳ�����lambda�ĺ��������޸İ�ֵ����ı���
    {
        int yVar = 999;
        auto lambdaYVar = [=]() mutable    //��ΪҪдmutable�����Լ�ʹ���lambda����Ҫ�κβ�����ҲҪ������д�ϣ�mutable����д�ڲ����б����ŵĺ��棬�����廨���ŵ�ǰ��
        {
            yVar = 90909;
            std::cout << "yVar is " << yVar << std::endl;
        };
        lambdaYVar();
    }

    //�������κα�����lambda���ʽ����ת��Ϊһ������ָ�룬ע�⣬�����б�Ϊ�յ�lambda����
    using intFuncPtr = int(*)();
    intFuncPtr lambdaFP = []
    {
        return 666;
    };
    std::cout << lambdaFP() << std::endl;
}


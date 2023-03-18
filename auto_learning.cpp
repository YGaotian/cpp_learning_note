#include "header_learning.h"

//auto������ָ�룬���ã�const���޶������ʹ�ã�����auto��ģ������Ͳ���T�����Ƶģ����Կ�����һ�����͵�ռλ����auto���ڱ����ڵ�ʱ��Ϳ����ƶ����͵ģ�����������Ӱ����������Ч��
//Ҳ�����ʹ��auto��ʱ�����������ʼ�������������ƶϲ�����

class clx
{
public:
    clx() = default;
    clx(const clx& c)
    {
        std::cout << "clx copy" << std::endl;
    }
};

void auto_learning()
{
    clx classXinst_1;
    const auto& classXinstRef = classXinst_1;   //auto����clx
    auto classXinst_2 = classXinstRef;  //auto��Ȼ��clx����ֵ���ݵ�ʱ��const���Ժ��������Ͷ��ᱻ������Ҳ����˵��classXinst_2��һ��classXinst_1�ĸ���������ÿ������캯��
    auto& classXinstRef_2 = classXinstRef;  //classXinstRef��const clx &���ͣ��˴���auto���ƶ�Ϊconst clx��Ҳ����˵&����&�ᷢ�������۵���const�ᱣ��
    auto classXinst_3 = new auto(classXinst_2);  //auto��������new���˴��ĵ�һ��auto����clx*���ڶ���auto����clx��ͬ����Ҳ�����˿���
    const auto* classXinst3_ptr = &classXinst_1;    //auto��clx

    //��autoҲ�������������ã�����������ģ�����T��һģһ���ģ�дΪauto&&��Ҳ�ᷢ�������۵�
    auto&& classXUniversalRef = classXinst_1;   //���Խ���ֵ���������ý���ֵ���Ƶ�Ϊ��ֵ���ã���ֵ����&����&&�����������۵��������&������classXUniversalRef��clx &���͵�

    //autoҲ�����ƶϳ��������ͣ�����ָ�����ͣ���������������

    //�����ж��ֳ�ʼ����ʽ������ȺŸ�ֵ��Բ���ų�ʼ���������ų�ʼ���б�
    int intValue = 618;             //intValue�Ǹ�int���͵ı���
    double doubleValue = {2.15};    //doubleValue�Ǹ�double���͵ı���
    //autoҲͬ������
    auto someInt(12);                               //auto���Ƶ�Ϊint����
    auto someDouble = 3.1415926;                  //auto���Ƶ�Ϊdouble����
    //����autoʱ�����ʹ�û����ŵĳ�ʼ���б�auto�Ϳ��ܲ��ᱻ�򵥵��Ƶ�Ϊ�Ⱥ��ұߵ�ֵ�������ˣ���Ϊ�ǻ����ţ�auto�����ȱ��Ƶ�Ϊ�б�����
    auto something = {2.1828};   //����auto���ͱ����std::initializer_list<double>���ͣ�����һ����ʾĳ���������ģ��
    auto somethingElse{ 3.33333 };                //Ȼ�����û���õȺţ�����ʹ���˻����ţ������autoȴ��Ȼ���Ա��Ƶ�Ϊdouble����
    //��������֪����ֻ�е� = �� {} һ��ʹ�õ�ʱ��auto�Ż��ƶ�Ϊinitializer_list���ͣ�������Ϳ��Դ������� 
    auto somethingNew = { 3.1415926, 2.1818, 3.33333 };
    //�����Ƶ�ֻ�ʺ�auto�����ʺ�����ģ�����������и�����ģ�� template <typename T> void tempFunc(T arg)����ô������ôд�Ļ��ᱨ��
    ///tempFunc({12});  //error
    //������ʽָ����������Ǹ�std::initializer_list���ͣ�
    ///template<typename T>
    ///void tempFunc(std::initializer_list<T> arg);
    //��ô tempFunc({12}) ���ǿ�������ִ�еģ���Ϊ�����{12}�ͻ�ʹarg���ƶ�Ϊstd::initializer_list<int>����

    //auto���ܷ��ں����βε�������
    ///void func(auto arg); //����
    //����auto���������ƶϺ����ķ���ֵ����
    ///auto func(); //���У�����ݷ���ֵ�Զ��ƶϳ���Ӧ���͵���ֵ����Ϊ������ǰ��autoʵ�����൱����auto���ƶ�return�ؼ��ֺ���Ķ�������ͣ����� auto anonymous = variable
    ///               ���return����Ķ����Ǹ���ֵ���ã���Ϊ�����õ���auto���ƶϣ������Ƶ��Ľ���Ƿ������潲��auto�Ƶ�����ģ�Ҳ����˵���ú�const���Զ��ᱻ����
    ///               ͬ���أ�return����Ķ����Ǹ���ֵ����ʱ������ʹ��nuto&���Ƶ���Ҳ�����ں�����ǰд����auto&����ô�Ƶ��������Ȼ����ֵ��������
    //auto����������ͨ�����Ա�����������Ƶ����ᱨ��ֻ���������еľ�̬������Ա���� static const auto member = xxx; �ǺϷ��ġ�ע����Ϊ����auto�����Ըó�Ա����������������ʼ��
}
#include "header_learning.h"
#include <deque>
#include <queue>
#include <unordered_set>
#include <forward_list>

class ContainerTestClass
{
public:
    int mi;
    ContainerTestClass(int miarg)
    {
        mi = miarg;
        std::cout << "ContainerTestClass is running, init:" << mi << std::endl;
    }
    ContainerTestClass(const ContainerTestClass& vt)
    {
        mi = vt.mi;
        std::cout << "copy constructor is running" << std::endl;
    }
    ~ContainerTestClass()
    {
        std::cout << "destroy:" << mi << std::endl;
    }
};

//vector ʵ�麯��
void vector_learning()
{
    //����������ӿ��Կ�����vectorÿ��һ��Ԫ�أ��ͻ�����һ�ο�������ĵ���
    //������Ϊvector������һ���ռ�ĸ��ÿ��push back��ʱ�򣬿ռ�᲻�㣬���Ծͻ�����һ���µĿռ䣬����ռ�Ĵ�С���Դ�����е�Ԫ�غ�������Ԫ��
    //��ôvector�ͻ��ԭ�ȵ�vectorԪ����һ�������µĿռ���ȥ����������Ԫ��Ҳ�Ž�����ռ䣬Ȼ����һ����ԭ�ȵ�vectorԪ�أ����Ի���ö�ο���������
    std::vector<ContainerTestClass> ctcvec = {ContainerTestClass(111), ContainerTestClass(222)};
    std::cout << "size = " << ctcvec.size() << std::endl;
    std::cout << "capacity = " << ctcvec.capacity() << std::endl;
    std::cout << std::endl;
    ContainerTestClass ctcInV_1(0);
    ctcvec.push_back(ctcInV_1);
    std::cout << "size = " << ctcvec.size() << std::endl;
    std::cout << "capacity = " << ctcvec.capacity() << std::endl;
    std::cout << std::endl;
    ContainerTestClass ctcInV_2(1);
    ctcvec.push_back(ctcInV_2);
    std::cout << "size = " << ctcvec.size() << std::endl;
    std::cout << "capacity = " << ctcvec.capacity() << std::endl;
    std::cout << std::endl;
    ContainerTestClass ctcInV_3(2);
    ctcvec.push_back(ctcInV_3);
    std::cout << "size = " << ctcvec.size() << std::endl;
    std::cout << "capacity = " << ctcvec.capacity() << std::endl;
    std::cout << std::endl;
    ContainerTestClass ctcInV_4(3);
    ctcvec.push_back(ctcInV_4);
    std::cout << "size = " << ctcvec.size() << std::endl;
    std::cout << "capacity = " << ctcvec.capacity() << std::endl;
    std::cout << std::endl;
    //����Ĵ����У�size��ʾ��ǰ�����е�Ԫ��������capacity��ʾ���ǿռ��С������˵�������ɶ���Ԫ�صĴ�С
    //capacityһ�������sizeС��һ�����size��ȣ�����������������������Ԫ�أ���ôcapacity�����ܵر��һ�����ʵģ�����size�������Ա���Ƶ���ط����ռ䲻��������
    int count = 0;
    for (auto iter = ctcvec.begin(); iter != ctcvec.end(); iter++)
    {
        if (count == 3)
        {
            std::cout << "erase: " << iter->mi << std::endl;
            ctcvec.erase(iter);
            std::cout << "erased!" << std::endl;
            break;
        }
        count++;
    }
    for (int n = 0; n != 5; n++)
    {
        std::cout << "��ǰԪ�� " << ctcvec[n].mi << " �ĵ�ַΪ��" << &ctcvec[n] << std::endl;
    }
    std::cout << std::endl;
    //������Ĵ����п���֪����vector��ɾ��Ԫ�ص�ʱ�򣬲����������Ԫ����һ���ÿ�������������
    //����Ǵ�vector�м�ɾ����ĳһ��Ԫ�صĻ��������Ԫ�ػ�ֱ����ǰ�ƶ�һ��λ�ã�ʹ�ڴ�����

    //���Ҫ��vector�м����Ԫ�أ���ôҲ�ᵼ�¶�ε���Ԫ�ض�Ӧ�����͵Ŀ��������������������ܻ��ټ��ε��ã���Ϊvector�����ڲ����Ż�����
    //Ϊ�����̶ȵ����vector������Ч�ʣ������������ǰ����capacity�Ĵ�С����ô���ǾͿ����ֶ�����������capacity��������������Ԫ��Ҳ������ö�ο���������
    std::cout << "\n" << std::endl;
    ctcvec.reserve(10);
    std::cout << "\nʹ����reverse" << std::endl;
    for (int k = 0; k < 3; k++)
    {
        std::cout << "����" << k << std::endl;
        ctcvec.push_back(ContainerTestClass(k));
    }
    std::cout << std::endl; 
    for (auto it = ctcvec.begin(); it != ctcvec.end(); it++)
    {
        std::cout << "ctcvec����Ԫ�أ�" << it->mi << std::endl;
    }
    std::cout << std::endl;
}
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//deque���������˿��ڵĶ��У����Դ���ͷ����Ԫ�أ�����Ԫ���Ƿֶ������ģ�Ҳ����˵����ÿ����Ԫ��Ϊһ�飬���ǵ��ڴ��ַ�������ģ�ÿ��Ԫ��֮���ǲ�������
void deque_learning()
{
    std::deque<ContainerTestClass> ctcdeq = {};
    for (int a = 0; a < 5; ++a)
    {
        ctcdeq.push_back(ContainerTestClass(a));
    }
    for (int b = 0; b < 5; ++b)
    {
        ctcdeq.push_front(ContainerTestClass(b * 11));
    }

    //print
    for (auto iter = ctcdeq.begin(); iter != ctcdeq.end(); ++iter)
    {
        std::cout << iter->mi << " in ctcdeq is located on: " << &*iter << std::endl;
    }
    std::cout << std::endl;
}
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//��deque���ƵĻ���һ��������stack������Ԫ���Ǻ���ȳ������ܴ��м����Ԫ�أ�dequeʵ����Ҳ������stack�Ĺ���

//queue�ǵ���Ķ��У�Ҳ����˵ֻ�ܴ�һ�˲���Ԫ�أ�����Ԫ�����Ƚ��ȳ��ģ�Ҳ�Ƿֶ������ģ�ͬ����dequeҲ������queue�Ĺ���
void queue_learning()
{
    std::queue<ContainerTestClass> ctcque = {};
    for (int in = 0; in < 18; in++)
    {
        ctcque.push(ContainerTestClass(in));
    }
    //queueû�е�����
    for (int o = 0; o < 18; ++o)
    {
        std::cout << ctcque.front().mi << "  ����ʵ���ĵ�ַΪ " << &(ctcque.front()) << std::endl;
        ctcque.pop();
    }
    std::cout << ctcque.size() << std::endl;
    std::cout << std::endl;
}
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//list��˫�������ڴ��ǲ�������
//list��vector�������ǣ�list������λ�ò������ݵ�Ч�ʺܸߣ���Ϊ���ÿ��������µ�����
//��vector��Ϊ�ڴ��������ģ����Բ��У����ҵ��ڴ治��ʱ��vector��Ҫ��һ���µĿռ䣬��ԭ����Ԫ�ؿ������µ�vector�У�Ȼ������ԭ����vector����list����
//������vector�ڴ�����������������ʷǳ���Ч�����ݵ�һ��Ԫ�صĵ�ַ������һ���Ӽ�����������Ԫ�صĵ�ַ��list���޷�ʵ��
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//forward_list�ǵ�������Ҳ��Ϊ�����������Ա���˫����������һ�������ָ�룬������ǰ���ʾͲ������ˣ�����Ҳ����ܽ�ʡһ��ָ�������ڴ�ռ�
void forwardlist_learning()
{
    std::forward_list<ContainerTestClass> ctcflist = {};
    for (int i = 0; i < 10; i++)
    {
        //forward_listֻ����ͷ��������Ԫ��
        ctcflist.push_front(ContainerTestClass(i));
    }
    for (auto iter = ctcflist.begin(); iter != ctcflist.end(); iter++)
    {
        std::cout << iter->mi << " ����ʵ���ĵ�ַΪ " << &*iter << std::endl;
    }
    //ͬ����Ҳֻ�ܴ�ͷ��popԪ��
    ctcflist.pop_front();
    std::cout << "now ctcflist's front element's mi is: " << ctcflist.front().mi << std::endl;
}
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//set��map���ǹ����������������ú������Ϊ�ڲ������ݽṹʵ�ֵģ������������в������ݣ�����Ҫ�ֶ�ָ������λ�ã���������ڲ����㷨�Զ�ѡһ��λ�ò���Ԫ�أ���˲������ݵ��ٶȿ�������
//map��ÿ��Ԫ����һ����ֵ�ԣ�ÿ��key�ǲ�����ͬ�ģ����һ��Ҫ����ͬ��key����map�����ǿ���ʹ��multimap��������ͨ��map��ͨ��key��value�ܸ�Ч
//��setֻ��value��û��key��������û���ظ���Ԫ�أ����Ҫ������ͬԪ�أ�����ʹ��multiset
void map_learning()
{
    std::map<char, std::string> strmap;
    //���ǿ���ʹ��ģ�庯��make_pair�����ɼ�ֵ��
    strmap.insert(std::make_pair('a', std::string("hello")));
    //Ҳ����ֱ�Ӱ���ͳ�ķ�������ʼ��һ��pairģ����ʵ������
    strmap.insert(std::pair<char, std::string>('b', "world"));
    //��������������ȥ������iter.end()���ص������������һ��Ԫ��֮��ĵ�ַ��Ҳ���ǳ�β
    /// for (auto iter = strmap.begin(); iter != strmap.end(); iter++)
    //Ҳ����ֱ��ʹ��find������������������Ա����find()�������ҵ�һ����ӵ��ĳkey����Ԫ�أ�������һ��ָ���λ�õĵ����������û�ҵ�������Ԫ�أ��ͷ���������end()
    //�޷���find()����ӵ��ĳ�ض�value��Ԫ�أ��������STL�㷨��find_if()����ɴ�����дһ��ѭ��
    auto iter = strmap.find('b');
    if (iter != strmap.end())
    {
        //first���ص�ǰԪ�ص�key����Եأ���Ҫ���ص�ǰԪ�ص�value������second
        std::cout << iter->first << std::endl;
    }
    strmap.insert(std::make_pair('b', "earth"));
    std::cout << strmap.find('b')->second << std::endl;
    //��������Կ���������ͨ��map�ظ�insert������ͬkey��ֵ����Ч�ģ���һ��֮��������ظ�insert�Ĳ������ᱻ����
}
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//�ϰ汾��c++��hash_map��hase_set��hash_multimap��hash_multiset
//�°汾�Ѿ����Ƽ�ʹ���ˣ�ȡ����֮���ǽ�hash_ǰ׺��Ϊunordered_ǰ׺���������������������������ѿ��������ڲ�ʹ�õ����ݽṹ��hash��
//���������������ݵ�ʱ��Ҳ����Ҫ�˹��ֶ���Ԥ�����Զ�ѡ����ʵ�λ�ý��в���

//unordered_set��bucket���������Զ����ݣ�bucket��������������Ԫ�ص���������Ԫ�ص�����Ҫ����bucket��ʱ��bucket�ͻ��Զ�����
void unorderedSet_learning()
{
    std::unordered_set<int> uoset = {};
    std::cout <<"bucket count: " << uoset.bucket_count() << std::endl;
    for (int i = 0; i < 10; i++)
    {
        uoset.insert(i);
        std::cout << "insert: " << i << std::endl;
        std::cout <<"bucket count: " << uoset.bucket_count() << std::endl;
    }
    std::cout <<"��������������ɵ�bucket����" << uoset.max_bucket_count() << std::endl;
    for (int n = 0; n < uoset.bucket_count(); n++)
    {
        std::cout << "bucket" << n << " has " << uoset.bucket_size(n) << " elements." << std::endl;
    }
    auto findresult = uoset.find(7);    //���ڲ��ұȽϷ�ʱ�����Ե������ṩ���Լ���find����ʱ��Ӧ����ʹ��������Ϊ�ض���findЧ�ʻ���Ը��ߣ����û�У���ʹ��ȫ�ֵ�find
    if (findresult != uoset.end())
    {
        std::cout << "element '7' is found." << std::endl;
    }
    //ȫ��find��ʹ�÷�����ʾ
    if (find(uoset.begin(), uoset.end(), 12) == uoset.end())
    {
        std::cout << "element '12' is not found" << std::endl;
    }
}



//������������
void stlContainer_learning()
{
    std::cout << "///////vector learning:" << std::endl;
    vector_learning();

    std::cout << "\n\n\n///////deque learning:" << std::endl;
    deque_learning();

    std::cout << "\n\n\n///////queue learning:" << std::endl;
    queue_learning();

    std::cout << "\n\n\n///////forwardlist learning:" << std::endl;
    forwardlist_learning();

    std::cout << "\n\n\n///////map learning:" << std::endl;
    map_learning();

    std::cout << "\n\n\n///////unordered_set learning:" << std::endl;
    unorderedSet_learning();


}
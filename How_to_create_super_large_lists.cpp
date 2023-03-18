#include <iostream>
#include "header_learning.h"
#include <thread>
#include <time.h>
#include <mutex>

//海量数据要用new在堆上开辟内存，不用new直接爆栈，还不给明确的报错提示，同时项目属性一定要改成x64，如果是win32，无法开辟四千万int的list，而且list的sizeof()结果是12，改为x64就变成24了
std::list<int>* intvec_1 = new std::list<int>/*(30000000)*/;
std::list<int>* intvec_2 = new std::list<int>/*(10000000)*/;
std::list<int>* intvec_3 = new std::list<int>/*(20000000)*/;

void writedata_1()
{
    for (int i = 0; i < 30000000; ++i)
    {
        intvec_1->push_back(i);
    }
}

void writedata_2()
{
    for (int k = 20000000; k < 30000000; ++k)
    {
        intvec_2->push_back(k);
    }
}

void writedata_3()
{
    for (int n = 0; n < 20000000; ++n)
    {
        intvec_3->push_back(n);
    }
}

void How_to_create_enormous_lists()
{
    auto begin = std::chrono::system_clock::now();
    std::thread thread1(writedata_1);
    std::thread thread2(writedata_2);
    std::thread thread3(writedata_3);
    thread1.join();
    thread2.join();
    thread3.join();
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - begin);

    std::cout << intvec_1->size() << std::endl;
    std::cout << intvec_2->size() << std::endl;
    std::cout << intvec_3->size() << std::endl;
    delete intvec_1;
    delete intvec_2;
    delete intvec_3;
    std::cout << duration.count() << "secs costed" << std::endl;
}
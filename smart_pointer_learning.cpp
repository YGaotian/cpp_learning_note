#include "header_learning.h"

//如果我们要使用new来动态为某个对象分配内存，那我们就必须在使用完后通过 delete 来手动释放内存
//如果我们用new来分配了一个数组的内存，那我们也必须配套地使用 delete [] 来手动释放内存
//一旦我们忘记delete或者使用错了delete，那就会造成程序运行有问题
//所以我们可以使用智能指针来代替手动new出来的裸指针，智能指针可以自动帮我们在合适的时候释放内存
//智能指针有三个，都是类模板，分别是 shared_ptr, weak_ptr, unique_ptr（代替了c++98的auto_ptr）
//当我们有多个指针指向同一块内存的时候，我们就需要用shared_ptr，同时也可以用weak_ptr来辅助操作，
//而unique_ptr就是用于只有一个指针指向一块内存的时候的

namespace SharedPtrNotes
{
    //函数声明
    std::shared_ptr<double> makeSmartPtrOfADouble(double);
    void receiveSharedPtrAndDoNothing(std::shared_ptr<int>);
    std::shared_ptr<int> returnASmartPtr(std::shared_ptr<int>&);
    void sharedPtrDeleter_1(int*);
    void sharedPtrDeleter_2(int*);
    void sharedPtrDeleter_3(int*);

    void shared_ptr_learning()
    {
        //实例化了一个int类型的智能指针
        std::shared_ptr<int> shr_ptr_1(new int(100));
        *shr_ptr_1 = 100;
        //实例化一个string类型的智能指针
        std::shared_ptr<std::string> shr_ptr_2(new std::string("Wow it's a smart pointer!"));
        std::cout << *shr_ptr_1 << std::endl;
        std::cout << *shr_ptr_2 << std::endl;
        //智能指针不支持隐式类型转换，是explicit的，必须显式地通过构造函数创建
        /// std::shared_ptr<double> shr_ptr_wrong_way = new int(5);

        //也可以通过函数返回一个智能指针
        std::shared_ptr<double> shr_ptr_3 = makeSmartPtrOfADouble(33.336f);
        std::cout << *shr_ptr_3 << std::endl;

        //make_shared 一个可以安全高效地分配和使用shared_ptr的标准库函数模板，可以帮我们在堆上分配并初始化一段内存，然后返回此对象的shared_ptr
        std::shared_ptr<int> shr_ptr_4 = std::make_shared<int>();
        std::cout << *shr_ptr_4 << std::endl;
        auto shr_ptr_5 = std::make_shared<std::string>(3, 'o');
        //自动delete shr_ptr_4 指向0的内存，然后又指向了500
        shr_ptr_4 = std::make_shared<int>(500);
        std::cout << *shr_ptr_4 << std::endl << *shr_ptr_5 << std::endl;

        //shared_ptr是通过引用计数器来知道有多少指针指向同一块内存的
        //每个shared_ptr都有这个引用计数器
        //我们可以将一个shared_ptr赋给另一个shared_ptr来实现多个指针指向同一块内存
        std::shared_ptr<int> shr_ptr_6 = std::make_shared<int>(202);    //可以给一个断点，看一下这里引用计数器记录了多少个指针
        auto shr_ptr_7(shr_ptr_6);
        //将智能指针作为实参传给一个函数时，也会增加引用计数，直到函数生命周期结束，引用计数会-1，但是如果用&引用传递，则不会增加智能指针的引用计数
        receiveSharedPtrAndDoNothing(shr_ptr_7);                        //单步运行到函数内部的时候，形参p上会显示有3个引用，函数退出后来到这一行，shr_ptr_7的引用计数变回2
        //并且，将智能指针作为返回值，让另一个对象来接收的时候也会增加引用计数
        returnASmartPtr(shr_ptr_6);                                     //没有对象来接受返回出来的临时对象，所以临时对象在该行执行完之后就销毁了，引用计数没有增加
        auto shr_ptr_8 = returnASmartPtr(shr_ptr_7);                    //因为这里让一个对象去接收了，所以引用次数会增加一次
        //当shr_ptr_8不再指向shr_ptr_7，那么引用计数就会-1
        shr_ptr_8 = shr_ptr_4;                                          //shr_ptr_6和shr_ptr_7的引用计数变回了2

        //当shr_ptr_6指向其他对象的时候，shr_ptr_7依然会指向之前shr_ptr_6指向的内存，这块内存并不会被释放
        shr_ptr_6 = nullptr;
        //现在shr_ptr_7是最后指向值为202的这块内存的指针，当shr_ptr_7也指向其他对象的时候，原内存就被释放了
        shr_ptr_7 = std::make_shared<int>(12345);                       //现在shr_ptr_7指向了存放的值为12345的内存

        //其实如果不想设置断点，可以用use_count()来查看指针的引用计数
        std::cout << std::endl;
        int shr_ptr_count_1 = shr_ptr_8.use_count();
        int shr_ptr_count_2 = shr_ptr_6.use_count();
        std::cout << shr_ptr_count_1 << "\n" << shr_ptr_count_2 << std::endl;

        //unique()在一个指针的引用计数为1的时候返回True，否则返回False，c++20中已移除，c++17已弃用
        std::cout << std::endl;
        if (/*shr_ptr_7.unique()*/shr_ptr_3.use_count() == 1)   ///使用use_count() == 1 来代替
            std::cout << "This shared_ptr is unique!" << std::endl;
        else
            std::cout << "This shared_ptr is not unique!" << std::endl;

        //reset()可以将一个shared_ptr置空，如果这个指针是唯一指向这块内存的指针，则这块内存会被释放，如果不是，则不会释放，但指向这块内存的其他指针的引用计数会-1
        std::cout << std::endl;
        shr_ptr_7.reset();
        std::cout << shr_ptr_7 << std::endl;
        //如果reset()接收了一个参数，则不会置空当前指针，会让该指针指向作为参数传进来的新对象，内存是否释放的规则与无参数的时候一样
        shr_ptr_8.reset(new int(618));
        std::cout << *shr_ptr_8 << "\n" << std::endl;

        //get()会将智能指针里的裸指针返回出来，但使用的时候要小心，一旦智能指针指向的内存被释放，那么裸指针也就没意义了，所以不要手动delete裸指针，该方法是为了应付一些第三方函数需要传入裸指针的情况
        int* nude_int_ptr = shr_ptr_8.get();
        std::cout << "nude_int_ptr: " << *nude_int_ptr << "\n" << std::endl;

        //swap()交换两个智能指针指向的对象
        std::swap(shr_ptr_8, shr_ptr_7);
        std::cout << "shr_ptr_7: " << *shr_ptr_7 << std::endl;
        shr_ptr_8.swap(shr_ptr_7);
        std::cout << "shr_ptr_8: " << *shr_ptr_8 << "\n" << std::endl;

        //智能指针还可以作为条件语句的判断条件，如果智能指针指向了某对象，那么就是True，否则是False

        //智能指针还可以指定删除器，可以通过我们自己的删除器来释放它的内存，比如我们想在释放内存的时候生成一些日志，我们可以自己定义一个删除器
        std::shared_ptr<int> shr_ptr_9(new int(1024), sharedPtrDeleter_1);
        shr_ptr_9 = nullptr;    //置空，这样指向1024的内存就会被删除器释放
        std::cout << std::endl;
        //删除器也可以是一个lambda表达式
        std::shared_ptr<int>shr_ptr_10(new int(2048), [](int* p) { delete p; std::cout << "指针所指向的内存已经释放完毕 " << std::endl; });
        std::cout << *shr_ptr_10 << std::endl;
        shr_ptr_10 = nullptr;
        std::cout << std::endl;
        //有时候shared_ptr的默认的删除器无法正确地释放内存，比如我们用数组来初始化智能指针的时候，默认的删除器只会执行delete，而不是delete[]，我们需要添加自己的删除器
        std::shared_ptr<Myclass> mycl_shr_ptr_1(new Myclass[5], [](Myclass* mc) { delete[] mc; std::cout << "myclass 对象的内存释放完毕 " << std::endl; });
        mycl_shr_ptr_1 = nullptr;
        std::cout << std::endl;
        //其实我们也可以用标准库模板的删除器，实例化一个数组类型的版本，传入shared_ptr的构造函数，可以方便地起到删除数组的作用
        std::shared_ptr<Myclass> mycl_shr_ptr_2(new Myclass[3], std::default_delete<Myclass[]>());
        mycl_shr_ptr_2 = nullptr;
        std::cout << std::endl;
        //然而还有更方便的做法，c++17的方法是，我们在实例化shared_ptr的时候，可以在尖括号里写明是个数组类型，这样释放内存的时候就自然会释放数组，而不必提供自己的删除器
        std::shared_ptr<Myclass[]> mycl_shr_ptr_3(new Myclass[7]);
        mycl_shr_ptr_3 = nullptr;
        std::cout << std::endl;

        //如果两个shared_ptr的所指对象的类型相同，就算给它们指定了不同的删除器，它们也属于同一种类型
        std::shared_ptr<int[]> shr_array_ptr_1(new int[3], sharedPtrDeleter_2);
        std::shared_ptr<int[]> shr_array_ptr_2(new int[5], sharedPtrDeleter_3);
        shr_array_ptr_2 = shr_array_ptr_1;  //会先调用sharedPtrDeleter_3，释放 new int[5]
        shr_array_ptr_2 = nullptr;  //因为ptr2指向ptr1所指向的对象了，所以现在再释放ptr2的时候会调用ptr1的删除器
        std::cout << std::endl;
    }

    std::shared_ptr<double> makeSmartPtrOfADouble(double x)
    {
        return std::shared_ptr<double>(new double(x));
    }

    void receiveSharedPtrAndDoNothing(std::shared_ptr<int> p) {}

    std::shared_ptr<int> returnASmartPtr(std::shared_ptr<int>& shr_intp)
    {
        return shr_intp;
    }

    //自定义的智能指针删除器
    void sharedPtrDeleter_1(int* p)
    {
        //智能指针删除器接收一个与智能指针的裸指针类型对应的指针，因为其实删除器就是要自己手动释放这个裸指针
        delete p;
        std::cout << "指针所指向的内存已经被1号删除器释放完毕 " << std::endl;
    }

    void sharedPtrDeleter_2(int* par)
    {
        //智能指针删除器接收一个与智能指针的裸指针类型对应的指针，因为其实删除器就是要自己手动释放这个裸指针
        delete[] par;
        std::cout << "指针所指向的内存已经被2号删除器释放完毕 " << std::endl;
    }

    void sharedPtrDeleter_3(int* par)
    {
        //智能指针删除器接收一个与智能指针的裸指针类型对应的指针，因为其实删除器就是要自己手动释放这个裸指针
        delete[] par;
        std::cout << "指针所指向的内存已经被3号删除器释放完毕 " << std::endl;
    }
}


namespace WeakPtrNotes
{
    void weak_ptr_learning()
    {
        //weak_ptr是用来辅助shared_ptr的，它指向由shared_ptr所指的对象，但它并不会影响所指对象的生命周期
        //就是说当一个对象不再由任何shared_ptr所指向时，如果还有weak_ptr指向它，这个对象的内存依然会被释放，自然地无论有多少个weak_ptr指向该对象，shared_ptr的引用计数都不会有所增减
        //weak_ptr（弱引用）不是一种独立的智能指针，它是用来监视shared_ptr（强引用）的生命周期的，可以监视到所指向的对象是否存在，它不能用来操作所指向的资源，只是对shared_ptr的能力的扩充
        std::shared_ptr<int> shr_ptr_1(new int(102));
        std::weak_ptr<int> weak_ptr_1 = shr_ptr_1;  //weak_ptr_1指向shr_ptr_1所指向的对象
        //当shr_ptr_1所指的对象被释放，weak_ptr_1就指向了不存在的对象，所以不能用weak_ptr_1来操作对象
        //我们可以用lock()来保证weak_ptr所指向的对象一直存在，lock()会返回一个新的shared_ptr
        //当weak_ptr所指向的对象存在，返回的就是指向该对象的shared_ptr，原来的shared_ptr的引用计数会+1，当原来的shared_ptr不再指向该对象时，由于还有一个shared_ptr指向该对象，所以内存不会被释放
        //若weak_ptr指向的对象不存在，lock()返回的就是一个空的shared_ptr
        auto shr_ptr_2 = weak_ptr_1.lock();
        shr_ptr_1.reset();
        std::cout << *shr_ptr_2 << std::endl;

        //use_count()可以返回weak_ptr所指向的对象上的强引用的数量（shared_ptr的数量）
        //reset()重置weak_ptr，使弱引用的引用计数-1

        //expired()可以判断weak_ptr所指的对象是否已过期（use_count是否为0），是返回True，表示已经不存在了，否则返回False，就是还存在
        shr_ptr_2 = nullptr;
        if (weak_ptr_1.expired())
            std::cout << "所指对象已销毁 " << std::endl;
        else
            std::cout << "存在" << std::endl;

        //shared_ptr和weak_ptr的大小都是他们的裸指针的2倍，比如它们的裸指针是int，4个字节，那么shared_ptr<int>和weak_ptr<int>就是8字节
        //因为它们内部包含了两个裸指针，一个指向T(模板参数)类型的对象，另一个指向很大的数据结构（控制块），这个控制块里包含强引用计数，弱引用计数，还有自定义删除器等其他对象
    }
}


namespace PitfallsOfSP
{
    std::shared_ptr<int> returnSharedPtr(std::shared_ptr<int>);

    class ForPtrTest
    {
    public:
        std::shared_ptr<ForPtrTest> getSelf()
        {
            return std::shared_ptr<ForPtrTest>(this);   //用裸指针this初始化了一个shared_ptr，这个shared_ptr有自己的控制块，控制块内有自己的引用计数
        }
    };

    //通过类成员函数返回this的shared_ptr指针的正确方法，是让这个类继承标准库的类模板std::enable_shared_from_this<>，然后在成员函数中返回shared_from_this()
    class ReturnSharedThisCorrectly : public std::enable_shared_from_this<ReturnSharedThisCorrectly>
    {
    public:
        std::shared_ptr<ReturnSharedThisCorrectly> getSelf()
        {
            return shared_from_this();   //用裸指针this初始化了一个shared_ptr，这个shared_ptr有自己的控制块，控制块内有自己的引用计数
        }
    };

    void pitfalls_of_shared_ptr()
    {
        //如果创建了一个动态分配内存的指针，在用这个指针去初始化一个临时的shared_ptr对象后，就不应该再使用这个指针了
        //因为一旦临时的shared_ptr被销毁，那么智能指针的引用计数就会变成0，也就意味着这块内存会被释放
        //那么此时原来的指针就被置空，也就是说成为了一个野指针，所以一旦将一个普通的指针用来初始化一个临时智能指针，就相当于承诺将这块内存的使用权移交给了临时的智能指针，以后不再使用原指针了
        int* ip = new int(1024);
        auto shr_ptr_1 = returnSharedPtr(std::shared_ptr<int>(ip)); //用ip初始化了一个临时的shared_ptr
        shr_ptr_1 = nullptr;
        std::cout << *ip << std::endl;   //输出了乱码，因为p所指向的内存已被释放
        //所以应该不再使用指针p，并立即将p指向空指针
        ip = nullptr;

        //不要用一个普通指针初始化多个shared_ptr，因为一旦这么做，那么不同的shared_ptr会指向各自的控制块，那么引用计数就不是互通的
        //这样一旦其中一个shared_ptr不再指向这块内存，那么引用计数就变成0了，这块内存就会被释放，那其他的shared_ptr如果被销毁，就会重复释放已经被释放的内存
        //所以正确的做法是用一个裸指针初始化一个shared_ptr，或是直接用匿名的指针初始化shared_ptr，再用这个shared_ptr初始化其他的shared_ptr，这样它们就指向了同一个控制块，可以共享引用计数
        /* Don't do this */
        ///int * op = new int(123);
        ///std::shared_ptr<int> shr_ptr_x1(op);
        ///std::shared_ptr<int> shr_ptr_x2(op);
        // 也不要把shared_ptr.get()返回出来的裸指针绑定到另一个shared_ptr上，因为这么做和上面讲的情况类似，两个shared_ptr指向同一块内存，但指向了各自的控制块，无法共享引用计数

        //不要将类自己的指针this用于初始化shared_ptr，然后再返回给其他shared_ptr
        std::shared_ptr<ForPtrTest> shr_ptr_of_class_1(new ForPtrTest);
        //异常，因为函数返回出来的shared_ptr对象有自己的引用计数，与shr_ptr_of_class_1并不共享引用计数，一旦其中一个指针被delete，别的shared_ptr再释放内存时会将同一个内存释放多次
        ///std::shared_ptr<ForPtrTest> shr_ptr_of_class_2 = shr_ptr_of_class_1->getSelf();
        //如果有需求返回一个类指针的shared_ptr，可以用标准库里的enable_shared_from_this<>
        std::shared_ptr<ReturnSharedThisCorrectly> shr_ptr_of_class_2(new ReturnSharedThisCorrectly);   //尽量别用auto来推断new出来的类对象的shared_ptr指针，可能推断不正确
                                                                                                        //这里要是用auto的话下一行会异常，可以用typeid.name()看看auto推断出来的是什么类型
        std::shared_ptr<ReturnSharedThisCorrectly> shr_ptr_of_class_3 = shr_ptr_of_class_2->getSelf();  //无异常，成功
        std::cout << shr_ptr_of_class_3 << std::endl;
        std::cout << std::endl;
    }

    std::shared_ptr<int> returnSharedPtr(std::shared_ptr<int> p)
    {
        return p;
    }
}


namespace UniquePtrNotes
{
    //自定义删除器函数声明
    void myUniqueDeleter_1(int*);
    void myUniqueDeleter_2(double*);

    void unique_ptr_learning()
    {
        //unique_ptr就是一个独占式的智能指针，同一时刻只能有一个unique_ptr指向一块内存空间，当unique_ptr被销毁的时候，指针所指的内存就被释放了
        std::unique_ptr<int> uniq_ptr_1(new int(555));
        std::cout << uniq_ptr_1 << ": " << *uniq_ptr_1 << std::endl;
        //到了c++ 14标准，新增了一个std::make_unique<>模板，可以以更高的性能创建unique_ptr，但是不支持指定自定义的删除器
        auto uniq_ptr_2 = std::make_unique<int>(2324);
        std::cout << *uniq_ptr_2 << std::endl;

        //unique_ptr不支持拷贝构造初始化，就是说不允许使用unique_ptr初始化一个新的unique_ptr，当然地，也不支持拷贝赋值
        //但是可以移动赋值或移动构造
        std::unique_ptr<int> uniq_ptr_3 = std::move(uniq_ptr_2);
        std::cout << "uniq_ptr_3: " << *uniq_ptr_3 << "\n" << std::endl;

        //release()方法可以切断unique_ptr与所指内存的联系，返回裸指针并将unique_ptr置空，我们可以手动delete这个裸指针，或是用这个裸指针初始化另一个智能指针
        std::unique_ptr<int> uniq_ptr_4(uniq_ptr_3.release());
        std::cout << "uniq_ptr_4: " << *uniq_ptr_4 << std::endl;
        std::cout << "uniq_ptr_3: " << uniq_ptr_3 << std::endl;
        //release之后如果没有用新的指针去接，也没有delete裸指针的话，就会导致内存泄漏，所以一定不要忘了用完delete
        delete uniq_ptr_4.release();
        std::cout << "uniq_ptr_4: " << uniq_ptr_4 << "\n" << std::endl;

        //reset()直接置空unique_ptr，并释放内存，如果带参数，那就再让unique_ptr指向传进来的实参对象，注意，参数是个裸指针
        std::unique_ptr<int> uniq_ptr_5 = std::make_unique<int>(654);
        std::unique_ptr<int> uniq_ptr_6;
        std::cout << "uniq_6: " << uniq_ptr_6 << std::endl;
        std::cout << "uniq_5: " << *uniq_ptr_5 << std::endl;
        uniq_ptr_6.reset(uniq_ptr_5.release());    //使uniq_ptr_2指向保存的数据为654的内存
        std::cout << "uniq_6: " << *uniq_ptr_6 << std::endl;
        std::cout << "uniq_5: " << uniq_ptr_5 << std::endl;

        //指向数组
        std::unique_ptr<int[]> uniq_array_ptr(new int[3]);  //我们应使用 unique_ptr<类型名[]> 的方式来创建指向数组的智能指针，这样才能保证没有自定义的删除器的情况下也能正常释放任何类型的数组指针
        uniq_array_ptr[0] = 1;
        uniq_array_ptr[1] = 2;
        uniq_array_ptr[2] = 123;
        for (int i = 0; i < 3; ++i)
            std::cout << uniq_array_ptr[i] << std::endl;

        //get()可以返回裸指针，但是千万不要delete从get()获取的裸指针

        //对于指向数组的智能指针，是不支持*解引用的

        //swap()用于交换两个智能指针所指的对象

        //unique_ptr可以通过转换为右值，来转换成shared_ptr，可以使用move，也可以将它写在一个函数里作为临时对象返回，赋值给shared_ptr
        std::shared_ptr<int> shr_uniq_ptr_1 = std::move(uniq_ptr_6);
        std::cout << "shr_uniq_ptr_1:" << *shr_uniq_ptr_1 << "\n" << std::endl;

        //unique_ptr在特殊的情况下还是可以进行特殊的拷贝的（就是移动），当这个unique_ptr将要被销毁的时候，比如作为函数的返回值，如果有函数外部的unique_ptr来接这个临时对象的话，临时对象会调用移动构造函数

        //向unique_ptr传递删除器
        //将自定义的删除器传递给unique_ptr的方法与shared_ptr不同，我们我需要先在模板参数中传递删除器函数的类型，再在实例化的时候传递删除器的函数名
        using intUPD = void(*)(int*);   //删除器函数的类型别名，是个无返回值，接收一个int*类型的函数指针
        std::unique_ptr<int, intUPD> uniq_ptr_7(new int(2001), myUniqueDeleter_1);
        std::cout << *uniq_ptr_7 << std::endl;
        uniq_ptr_7 = nullptr;
        //我们也可以用typedef，或是typedef decltype()*，后者就是用decltype来获取了函数的类型，然后加一个*表明这是一个指针类型
        typedef decltype(myUniqueDeleter_1)* iUPD;
        std::unique_ptr<int, iUPD> uniq_ptr_8(new int(1225), myUniqueDeleter_1);
        std::cout << *uniq_ptr_8 << std::endl;
        uniq_ptr_8 = nullptr;

        //由于我们指定删除器的时候，是要在模板参数里写明删除器函数指针的类型的，所以与shared_ptr不同的是，一旦两个unique_ptr指定了不同的删除器，那它们就不再是相同的类型

        //unique_ptr的大小一般是4个字节，但如果指定了删除器，就有可能变化，比如说传进一个删除器函数指针，大小就会变成两倍，但如果删除器是个lambda表达式，就不会变化
        using doubleUPD = void(*)(double*);
        std::unique_ptr<double, doubleUPD> uniq_ptr_9(new double(12.25), myUniqueDeleter_2);
        std::cout << sizeof(uniq_ptr_9) << " " << sizeof(double) << std::endl;
        std::cout << std::endl;

    }

    //自定义删除器
    void myUniqueDeleter_1(int* pUniq)
    {
        delete pUniq;
        pUniq = nullptr;
        std::cout << "已删除unique_ptr<int> " << std::endl;
    }

    void myUniqueDeleter_2(double* pUniq)
    {
        delete pUniq;
        pUniq = nullptr;
        std::cout << "已删除unique_ptr<double> " << std::endl;
    }
}


void smart_pointer_learning()
{
    std::cout << "===shared_ptr" << std::endl;
    using namespace SharedPtrNotes;
    shared_ptr_learning();

    using namespace WeakPtrNotes;
    std::cout << "\n===weak_ptr" << std::endl;
    weak_ptr_learning();

    using namespace PitfallsOfSP;
    std::cout << "\n===Some pitfalls of using shared_ptr" << std::endl;
    pitfalls_of_shared_ptr();

    using namespace UniquePtrNotes;
    std::cout << "===unique_ptr" << std::endl;
    unique_ptr_learning();
}
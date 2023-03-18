#include "header_learning.h"
#include "tellMeYourPassword.h"

int main()
{
	//const_pointer_and_pointer_const();
	//cin_learning();
	//cin_getline_learning();
	//cin_get_learning();
	//cin_with_string();
	//string_in_istream();
	//new_pointer_learning();
	//array_learning();
	//new_array();
	//pointer_and_array();
	//strArray_with_pointer();
	//pointer_and_struct();
	//array_vector_compare();
	//compare_two_char_and_charArray();
	//typedef_and_define();
	//simple_file_output();
	//simple_file_input();
	//function_2DArray();
	//function_pointer();
	//learning::namespace_learning();
	//range_based_for();
	//nullptr_and_voidptr();
	//public_and_private_in_struct();
	/*
	Aclass A;
	A.print_hello();
	*/
	//trailing_return_func();                               //含有 auto 函数名() -> 返回类型 的解释
	//funcaa();//funcaa an inline function
	//why_we_can_put_class_definition_into_header_files();
	//defense_declared_header();
	//iterator_fundamental();
	//convert_type_learning();
	//introduction_to_class();                              //讲解了不同的初始化方式产生的结果，以及explicit关键字
	//const_function_learning();
	//mutable_learning();
	//this_learning();
	/*
	//global_k在static_and_extern中被初始化，因为它不是static变量。所以在此处用extern声明，便可以被访问
	extern int global_k;
	std::cout << global_k << std::endl;
	*/
	/*
	k被声明为static int，即使在这里使用了extern也无法访问，下述代码不会有错误提示，但是无法被运行
	extern int k;
	std::cout << k << std::endl;
	*/
	//static_learning();
	//operator_overload();
	//class_inheritance();                                  //包含有函数遮蔽的解决办法
	//virtual_in_class();                                   //讲解了多态动态绑定
	//friend_function();
	//friend_class();
	//friend_class_member_function();
	//RTTI_learning();                                      //含有typeid和type_info的讲解
	//more_about_the_inheritance();
	//right_value_reference();
	//temporary_object();
	//move_constructor();                                   //含有 noexcept 的讲解
	//inherited_constructor();
	//virtual_inheritance();
	//type_convert_constructor();
	//type_convert_operator();
	//convert_class_member_to_function_pointer();           //含有 typedef 和 using 定义函数指针类型的用法讲解
	//class_member_function_pointer();
	//class_member_variable_pointer();
	//function_template();
	//class_template();                                     //含有为什么要写hpp的讲解
    //occasion_to_use_typename();                           //含有 typename 类名<模板形参>::类型成员 类名<模板形参>::成员函数() 的讲解
    //what_are_callable_objects();                          //含有仿函数的讲解
    //default_param_of_templates();                         //调用的时候可以省略参数，直接写 类名<>类实例名 的情况
    //the_template_function_in_template_class();
    //explicit_instantiation_of_template_class();           //包含类模板和函数模板的显式实例化
    //template_alias();                                     //using 定义模板别名
    //class_template_specialization();
    //function_template_specialization();                   //不管是类模板还是函数模板，定义和实现都应该放在同一个头文件中，并且泛化版本应该放在特化版本之前
    //variadic_template();                                  //包含递归终止函数
    //template_template_parameter();
    //foreword_of_direct_management_of_memory();            //含有auto与new的结合使用
    //smart_pointer_learning();
    //concurrency_learning_part1();                         //并发编程入门-上
    //concurrency_learning_part2();                         //并发编程入门-下，含有std::ref的讲解，关于ref还有额外的注解，请看part8
    //concurrency_learning_part3();                         //并发编程继续-多线程创建及数据共享问题分析/互斥量
    //concurrency_learning_part4();                         //多互斥量产生的死锁问题/一般解决方案
    //concurrency_learning_part5();                         //lock_guard 的可选替代品 - unique_lock 入门：try_to_lock / adopt_lock
    //concurrency_learning_part6();                         //unique_lock 继续：try_lock / defer_lock
    //concurrency_learning_part7();                         //条件变量
    //concurrency_learning_part8();                         //async / future / packaged_task / promise初探
    //concurrency_learning_part9();                         //wair_for / future_status / shared_future / 原子操作 atomic 入门
    //concurrency_learning_part10();                        //原子操作-续/async-续
    //critical_section_learning();                          //windows临界区
    //concurrency_learning_part11();                        //可重复加锁的recursive_mutex / timed_mutex / timed_recursive_mutex
    //singleton_pattern_learning();
    //本节无代码，请查看thread_pool_concept文件
    //reacquaint_new_and_delete();                          //new 与 delete 的重载，单一对象与数组对象在堆上申请内存背后的分配机制浅谈
    //memory_pool_learning();
    //memory_pool_with_embeded_pointer();                   //嵌入式指针与内存池
	//override_global_operator_new_and_delete();            //重载全局new与delete
    //placement_new_learning();                             //定位new以及自定义new 
    //stlContainer_learning();                              //stl容器探究测试
    //stlAllocator_learning();                              //stl分配器浅析
    //stlIterator_learning();                               //stl迭代器浅析
    //stlAlgorithm_learning();                              //stl算法浅析
    //stlFunctional_learning();                             //stl函数对象浅析
    //stlAdaptor_learning();                                //适配器，含有std::bind<>的讲解
    //stlFunction_learning();                               //包装器类模板std::function讲解，用于将不同的可调用对象包装成统一类型的对象
    //universal_reference_learning();                       //万能引用的辨认与使用
    //understand_type_deduction_with_boost_library();       //使用第三方的boost库，理解模板类型推断
    //reference_collapsing_and_perfect_forwarding();        //引用折叠与完美转发的概念，与万能引用的联系
    //auto_learning();                                      //自动类型推断详解，不同的初始化方式 {} / () / ={} 会影响自动类型推断的结果
    //decltype_learning();                                  //decltype与auto的区别，用法，decltype(auto)的作用
    //deep_in_binder();                                     //再谈std::bind<>
    //lambda_learning();                                    //lambda表达式详解
    //lambda_additional_analysis();                         //lambda深入续谈
    //variadic_function_learning();                         //使用initializer_list或省略号形参的可变参数函数详解
    //type_traits_learning();                               //类型萃取的概念以及部分用法演示
    //constexpr_learning();                                 //constexpr详解，可变参数函数模板包展开的另一种写法演示
    //exception_handling_learning();                        //异常处理详解，try，catch，throw，noexcept，函数测试块
    //How_to_create_enormous_lists();                       //无法在堆上开辟巨大容量的list的时候需要检查的东西
    //test();
    return 0;
}


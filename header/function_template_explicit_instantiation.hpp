#pragma once

template <typename W>
void explicit_instantiation_of_function_template(W arg)
{
    std::cout << "arg type: " << typeid(arg).name() << std::endl;
}

#include "header_learning.h"
#include "class_template_learning.hpp"
#include "function_template_explicit_instantiation.hpp"

template class MyTemplateClassA<double>;

template void explicit_instantiation_of_function_template(int i);

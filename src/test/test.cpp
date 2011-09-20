
#include "test.h"

template<typename T>
T tpl::get(){return T(value);}


void tpl::call()
{
     float f=get<float>();
}

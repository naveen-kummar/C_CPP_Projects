#include "6_extern_template.h"
extern template int ReallyBigFunction<int>();
int something1()
{
    int j = ReallyBigFunction<int>();
    return j + 1;
}
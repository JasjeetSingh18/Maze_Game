#include "helper_functions.h"

void clear_list (int list[], int length, int clear_value)
{
    for (int i=0; i<length; i++)
    {
        list[i] = clear_value;
    }
}
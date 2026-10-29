#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define PRINT_TYPE_INFO(type)\
    printf("%11s: size = %zu bytes\t\talignment = %zu bytes\n", #type, sizeof(type), _Alignof(type))

int main(void)
{
    printf("\t\tMEMORY LAYOUT EXPLORER\n");
    printf("\tIn this environment, a byte has %d bits\n", CHAR_BIT);

    PRINT_TYPE_INFO(char);
    PRINT_TYPE_INFO(short);
    PRINT_TYPE_INFO(int32_t);
    PRINT_TYPE_INFO(int32_t*);
    PRINT_TYPE_INFO(long);
    PRINT_TYPE_INFO(long long);
    PRINT_TYPE_INFO(float);
    PRINT_TYPE_INFO(double);
    PRINT_TYPE_INFO(long double);

    return EXIT_SUCCESS;
}

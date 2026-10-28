#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/*
    Check if the architecture is valid for IEEE 754 binary32 representation
*/
_Static_assert(sizeof(float) == 4, "Error: float must be 4 bytes.");
_Static_assert(sizeof(float) * CHAR_BIT == 32, "Error: byte must have 8 bits.");

int main(void)
{
    int check_input;
    float number;

    do
    {
        printf("Enter a float number: ");
        check_input = scanf("%f", &number);
    } 
    while (check_input != 1);
    
    return EXIT_SUCCESS;
}

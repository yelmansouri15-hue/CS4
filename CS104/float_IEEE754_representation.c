#include <float.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Check if the architecture is valid for IEEE 754 binary32 representation
*/
_Static_assert(sizeof(float) == 4, "Error: float must be 4 bytes.");
_Static_assert(sizeof(float) * CHAR_BIT == 32, "Error: byte must have 8 bits.");

const unsigned short bits_float = sizeof(float) * CHAR_BIT;

short exponent_bits(uint32_t n);
float get_float(void);
short sign_bit(uint32_t);

int main(void)
{
    uint32_t representation;
    float number;

    number = get_float();

    memcpy(&representation, &number, sizeof(number));

    return EXIT_SUCCESS;
}

float get_float(void)
{
    int check_input;
    float number;

    do
    {
        printf("Enter a float number: ");
        check_input = scanf("%f", &number);
    } 
    while (check_input != 1);

    return number;
}

short exponent_bits(uint32_t n)
{
    short bits = (n >> 23) & 0xFF;

    return bits;
}

short sign_bit(uint32_t n)
{
    short bit = (n >> (bits_float - 1)) & 1;

    return bit;
}

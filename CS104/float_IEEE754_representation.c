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

const unsigned short bits_float = sizeof(float) * CHAR_BIT, position_exponent = 23, bitmask_exponent = 0xFF, size_exp = 8, size_frac = 23;
const uint32_t bitmask_frac = 0x007FFFFF;

void binary(uint32_t number, unsigned short size);
unsigned short exponent_bits(uint32_t);
uint32_t frac_bits(uint32_t);
float get_float(void);
void IEEE754(uint32_t);
short sign_bit(uint32_t);

int main(void)
{
    uint32_t representation;
    float number;

    number = get_float();

    memcpy(&representation, &number, sizeof(number));

    IEEE754(representation);

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

void IEEE754(uint32_t n)
{
    short sign = sign_bit(n);
    unsigned short exp = exponent_bits(n);
    uint32_t frac = frac_bits(n);

    printf("Sign bit: %d\t Exponent field: ", sign);
    binary(exp, size_exp);
    printf("\t Fraction field: ");
    binary(frac, size_frac);
    printf("\nRepresentation: %d ", sign);
    binary(exp, size_exp);
    binary(frac, size_frac);

    if (exp == 0)
    {
        printf("\nType: denormalized");
        if (frac == 0)
            printf(" (zero)");
    }
    else if (exp == 255)
    {
        if (frac == 0)
            printf("\nType: infinity");
        else
            printf("\nType: NaN");
    }
    else
        printf("\nType: normalized");
}

void binary(uint32_t n, unsigned short size)
{
    short i, bit;

    for (i = size - 1; i >= 0; i--)
    {
        bit = (n >> i) & 1;
        printf("%d", bit);
    }
    printf(" ");
}

unsigned short exponent_bits(uint32_t n)
{
    short bits = (n >> position_exponent) & bitmask_exponent;

    return bits;
}

uint32_t frac_bits(uint32_t n)
{
    uint32_t bits = n & bitmask_frac;

    return bits;
}

short sign_bit(uint32_t n)
{
    short bit = (n >> (bits_float - 1)) & 1;

    return bit;
}

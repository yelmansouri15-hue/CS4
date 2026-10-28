#include <stdio.h>
#include <stdint.h>

/*
    Sum of two unsigned integer in a safe way
    true --> overflow
*/
bool safe_sum(uint8_t a, uint8_t b, uint8_t *result)
{
    unsigned int sum = (unsigned int)a + (unsigned int)b;
    *result = (uint8_t)sum;
    return sum > UINT8_MAX;
}

/*
    Product of two unsigned integer in a safe way
    true --> overflow
*/
bool safe_prod(uint8_t a, uint8_t b, uint8_t *result)
{
    unsigned int product = (unsigned int)a * (unsigned int)b;
    *result = (uint8_t)product;
    return product > UINT8_MAX;
}

int main()
{
    uint8_t res_suma;
    uint8_t res_multiplicacion;

    if (safe_sum(200, 60, &res_suma)) 
    {
        printf("Alert! An overflow occurred during the addition. Result truncated: %d\n", res_suma);
    } 
    else 
    {
        printf("Safe addition. Result: %d\n", res_suma);
    }

    if (safe_prod(10, 5, &res_multiplicacion)) {
        printf("Alert! There was an overflow in the product.\n");
    } 
    else 
    {
        printf("Safe product. Result: %d\n", res_multiplicacion);
    }

    return 0;
}

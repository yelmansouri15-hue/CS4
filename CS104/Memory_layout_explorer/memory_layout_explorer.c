/**
 * @file memory_layout_explorer.c
 * @brief Memory Layout Explorer - Investigating sizes, alignment, struct padding, 
 *        array decay, and dynamic memory allocation in C.
 * @author Yasser El Mansouri
 */

#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 32
#define PRINT_TYPE_INFO(type)\
    printf("%11s: size = %zu bytes\t\talignment = %zu bytes\n", #type, sizeof(type), _Alignof(type))
#define SHOW_OFFSET(type, m)\
    printf("%s = %zu\t", #m, offsetof(type, m))
#define PRINT_OFFSETS(type, member1, member2, member3) do {\
    printf("%19sOffsets: ", "");\
    SHOW_OFFSET(type, member1);\
    SHOW_OFFSET(type, member2);\
    SHOW_OFFSET(type, member3);\
    printf("\n");\
} while(0)

typedef struct
{
    char first;
    int32_t second;
    short third;
} Inefficient_Struct;

typedef struct
{
    int32_t first;
    short second;
    char third;
} Efficient_Struct;

/* --- Function Prototypes --- */
void array_addresses(void);
void array_decay(const int32_t *);
int32_t *create_array(size_t);
size_t get_size(void);

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
    printf("\n");

    array_addresses();

    printf("\nPress Enter to continue...");
    getchar();

    printf("\n\tAnd what if we change the ORDER of the members in a struct?\n");
    printf("char - int - short:\n\t");
    PRINT_TYPE_INFO(Inefficient_Struct);
    PRINT_OFFSETS(Inefficient_Struct, first, second, third);
    printf("int - short - char:\n\t  ");
    PRINT_TYPE_INFO(Efficient_Struct);
    PRINT_OFFSETS(Efficient_Struct, first, second, third);

    printf("\nPress Enter to continue...");
    getchar();

    int32_t array[10];
    int32_t *pointer = array;

    printf("\t1. Array vs Pointer (in local scope):\n");
    printf("sizeof(array)   = %zu bytes (Total array size)\n", sizeof(array));
    printf("sizeof(pointer) = %zu bytes (Pure pointer size)\n", sizeof(pointer));

    printf("\n\t2. Array Decay (passing to a function):\n");
    array_decay(array);

    return EXIT_SUCCESS;
}

void array_addresses(void)
{
    size_t index;
    size_t size = get_size();

    int32_t *array = create_array(size);
    if (array == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed or invalid size.\n");
        exit(EXIT_FAILURE);
    }

    printf("\t(Note: The distance between elements' addresses should be %zu bytes)\n", sizeof(int32_t));
    printf("\tAddresses: |");

    for (index = 0; index < size; index++)
        printf("%p|", (void*)&array[index]);

    printf("\n");

    free(array);
}

void array_decay(const int32_t *array)
{
    // Notice that sizeof(array) here evaluates to the size of the pointer (8 bytes on 64-bit), 
    // confirming that the array has decayed to a pointer.
    printf("Inside function, sizeof(array) = %zu bytes (It decayed to a pointer!)\n", sizeof(array));
}

int32_t *create_array(size_t n)
{
    if (n == 0 || n > SIZE_MAX / sizeof(int32_t)) 
    {
        return NULL;
    }

    int32_t *array = malloc(n * sizeof *array);

    if (array == NULL) 
    {
        return NULL;
    }

    return array;
}

size_t get_size(void)
{
    bool extra_chars, invalid_number, not_number, overflow;
    char input[MAX_INPUT_LEN];
    char *end;
    int c;
    unsigned long int size = 0;

    do
    {
        errno = 0;
        invalid_number = false;

        printf("Enter a size to create an int array: ");

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            fprintf(stderr, "\nError: Input stream closed. Exiting.\n");
            exit(EXIT_FAILURE);   
        }
        
        // Check if the input was longer than the buffer size
        if (strchr(input, '\n') == NULL)
        {
            while((c = getchar()) != '\n' && c != EOF);
            invalid_number = true;
        }

        size = strtoul(input, &end, 10);

        if (strchr(input, '-') != NULL || size == 0)
            invalid_number = true;

        overflow = (errno == ERANGE);
        not_number = (end == input);
        extra_chars = (*end != '\n' && *end != '\0' && *end != '\r');

        if (overflow || not_number || extra_chars || invalid_number)
        {
            printf("Invalid input. Please enter a positive integer.\n");
            invalid_number = true; // Keep looping
        }
    } 
    while (invalid_number);

    return (size_t)size;
}

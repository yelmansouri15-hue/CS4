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

void array_addresses(void);
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

    return EXIT_SUCCESS;
}

void array_addresses(void)
{
    size_t index;
    size_t size = get_size();

    int32_t *array = malloc(size * sizeof(int32_t));
    if (array == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    printf("\t(Note: The distance between elements' addresses should be %zu bytes)\n", sizeof(int32_t));
    printf("\tAddresses: |");

    for (index = 0; index < size; index++)
        printf("%p|", (void*)&array[index]);

    printf("\n");

    free(array);
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
            printf("\nError: Input stream closed. Exiting.\n");
            exit(EXIT_FAILURE);   
        }
        
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
        extra_chars = (*end != '\n' && *end != '\0');
    } 
    while (overflow || not_number || extra_chars || invalid_number);

    return (size_t)size;
}

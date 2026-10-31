#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 32
#define PRINT_TYPE_INFO(type)\
    printf("%11s: size = %zu bytes\t\talignment = %zu bytes\n", #type, sizeof(type), _Alignof(type))

size_t get_size();

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

        if (strchr(input, '-') != NULL)
            invalid_number = true;

        size = strtoul(input, &end, 10);

        overflow = (errno == ERANGE);
        not_number = (end == input);
        extra_chars = (*end != '\n' && *end != '\0');
    } 
    while (overflow || not_number || extra_chars || invalid_number);

    return (size_t)size;
}

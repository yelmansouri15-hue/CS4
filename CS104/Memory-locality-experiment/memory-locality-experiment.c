#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const size_t N = 256;

static int64_t *create_matrix(size_t rows, size_t cols);
static void init_matrix(int64_t *matrix, size_t rows, size_t cols);

int main (void)
{
    int64_t *matrix = create_matrix(N, N);
    if (matrix == NULL)
    {
        fprintf(stderr, "Error: failed to allocate contiguous matrix.\n");
        return EXIT_FAILURE;
    }

    init_matrix(matrix, N, N);

    free(matrix);
    return EXIT_SUCCESS;
}

static int64_t *create_matrix(size_t rows, size_t cols)
{
    if (rows == 0 || cols == 0)
    {
        return NULL;
    }

    if (rows > SIZE_MAX / cols || (rows * cols) > SIZE_MAX / sizeof(int64_t))
    {
        return NULL;
    }

    return malloc(rows * cols * sizeof(int64_t));
}

static void init_matrix(int64_t *matrix, size_t rows, size_t cols)
{
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            matrix[i * cols + j] = (int64_t)(i + j);
        }
    }
}

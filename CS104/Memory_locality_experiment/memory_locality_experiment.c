#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const size_t SIZES[] = {256, 512, 1024, 2048};
static const size_t NUM_SIZES = sizeof(SIZES) / sizeof(SIZES[0]);
static const size_t ITERATIONS = 9;

static int64_t *create_matrix(size_t rows, size_t cols);
static void init_matrix(int64_t *matrix, size_t rows, size_t cols);
static int64_t rows_route(const int64_t *matrix, size_t rows, size_t cols);
static int64_t cols_route(const int64_t *matrix, size_t rows, size_t cols);
static double now_seconds(void);

int main (void)
{
    volatile int64_t sink = 0;

    for (size_t s = 0; s < NUM_SIZES; s++)
    {
        const size_t N = SIZES[s];

        int64_t *matrix = create_matrix(N, N);
        if (matrix == NULL)
        {
            fprintf(stderr, "Error: failed to allocate contiguous matrix.\n");
            return EXIT_FAILURE;
        }

        init_matrix(matrix, N, N);

        sink ^= rows_route(matrix, N, N);
        sink ^= cols_route(matrix, N, N);

        double row_times[ITERATIONS];
        double col_times[ITERATIONS];
        int64_t row_sum = 0;
        int64_t col_sum = 0;

        for (size_t r = 0; r < ITERATIONS; r++)
        {
            double t0, t1;

            if (r % 2 == 0)
            {
                t0 = now_seconds();
                row_sum = rows_route(matrix, N, N);
                t1 = now_seconds();
                row_times[r] = t1 - t0;

                t0 = now_seconds();
                col_sum = cols_route(matrix, N, N);
                t1 = now_seconds();
                col_times[r] = t1 - t0;
            }
            else
            {
                t0 = now_seconds();
                col_sum = cols_route(matrix, N, N);
                t1 = now_seconds();
                col_times[r] = t1 - t0;

                t0 = now_seconds();
                row_sum = rows_route(matrix, N, N);
                t1 = now_seconds();
                row_times[r] = t1 - t0;
            }

            if (row_sum != col_sum)
            {
                fprintf(stderr, "Error: the sum is different in each route\n");
                free(matrix);
                return EXIT_FAILURE;
            }

            sink ^= row_sum ^ col_sum;
        }

        free(matrix);
    }

    (void)sink;
    return EXIT_SUCCESS;
}

static int64_t rows_route(const int64_t *matrix, size_t rows, size_t cols)
{
    int64_t sum = 0;

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            sum += matrix[i * cols + j];
    
    return sum;
}

static int64_t cols_route(const int64_t *matrix, size_t rows, size_t cols)
{
    int64_t sum = 0;

    for (size_t j = 0; j < cols; j++)
        for (size_t i = 0; i < rows; i++)
            sum += matrix[i * cols + j];
    
    return sum;
}

static double now_seconds(void)
{
    return (double)clock() / (double)CLOCKS_PER_SEC;
}

static int64_t *create_matrix(size_t rows, size_t cols)
{
    if (rows == 0 || cols == 0)
        return NULL;

    if (rows > SIZE_MAX / cols || (rows * cols) > SIZE_MAX / sizeof(int64_t))
        return NULL;

    return malloc(rows * cols * sizeof(int64_t));
}

static void init_matrix(int64_t *matrix, size_t rows, size_t cols)
{
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            matrix[i * cols + j] = (int64_t)(i + j);
}

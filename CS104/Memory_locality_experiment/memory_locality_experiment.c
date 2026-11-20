#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const size_t SIZES[] = {256, 512, 1024, 2048};
static const size_t NUM_SIZES = sizeof(SIZES) / sizeof(SIZES[0]);
static const size_t WARMUP_RUNS = 1;
static const size_t MEASURED_RUNS    = 9;

typedef struct
{
    int64_t *data;
    size_t rows;
    size_t cols;
} Matrix;

typedef int64_t (*traversal_fn)(const int64_t *data, size_t rows, size_t cols);

static bool run_size_benchmark(size_t n, double *row_times, double *col_times, volatile int64_t *sink);
static bool matrix_create(Matrix *m, size_t rows, size_t cols);
static void matrix_destroy(Matrix *m);
static void matrix_init(Matrix *m);
static int64_t rows_route(const int64_t *data, size_t rows, size_t cols);
static int64_t cols_route(const int64_t *data, size_t rows, size_t cols);
static double now_seconds(void);
static double measure_once(traversal_fn fn, const Matrix *m, int64_t *out_sum);

int main(void)
{
    volatile int64_t sink = 0;
    double row_times[MEASURED_RUNS];
    double col_times[MEASURED_RUNS];

    for (size_t s = 0; s < NUM_SIZES; s++)
        if (!run_size_benchmark(SIZES[s], row_times, col_times, &sink))
            return EXIT_FAILURE;

    (void)sink;
    return EXIT_SUCCESS;
}

static bool run_size_benchmark(size_t n, double *row_times, double *col_times, volatile int64_t *sink)
{
    Matrix m;
    if (!matrix_create(&m, n, n))
    {
        fprintf(stderr, "Error: failed to allocate %zu x %zu matrix.\n", n, n);
        return false;
    }

    matrix_init(&m);

    const traversal_fn routes[] = {rows_route, cols_route};

    for (size_t w = 0; w < sizeof(routes) / sizeof(routes[0]); w++)
        for (size_t k = 0; k < WARMUP_RUNS; k++)
            *sink ^= routes[w](m.data, m.rows, m.cols);

    for (size_t r = 0; r < MEASURED_RUNS; r++)
    {
        int64_t row_sum = 0;
        int64_t col_sum = 0;

        if (r % 2 == 0)
        {
            row_times[r] = measure_once(rows_route, &m, &row_sum);
            col_times[r] = measure_once(cols_route, &m, &col_sum);
        }
        else
        {
            col_times[r] = measure_once(cols_route, &m, &col_sum);
            row_times[r] = measure_once(rows_route, &m, &row_sum);
        }

        if (row_sum != col_sum)
        {
            fprintf(stderr,
                    "Error: sum mismatch for N=%zu on run %zu (rows=%" PRId64", cols=%" PRId64").\n",
                    n, r, row_sum, col_sum);
            matrix_destroy(&m);
            return false;
        }

        *sink ^= row_sum ^ col_sum;
    }

    matrix_destroy(&m);
    return true;
}

static bool matrix_create(Matrix *m, size_t rows, size_t cols)
{
    m->data = NULL;
    m->rows = 0;
    m->cols = 0;

    if (rows == 0 || cols == 0)
        return false;

    if (rows > SIZE_MAX / cols || (rows * cols) > SIZE_MAX / sizeof(int64_t))
        return false;

    m->data = malloc(rows * cols * sizeof(int64_t));
    if (m->data == NULL)
        return false;

    m->rows = rows;
    m->cols = cols;
    return true;
}

static void matrix_destroy(Matrix *m)
{
    free(m->data);
    m->data = NULL;
    m->rows = 0;
    m->cols = 0;
}

static void matrix_init(Matrix *m)
{
    for (size_t i = 0; i < m->rows; i++)
        for (size_t j = 0; j < m->cols; j++)
            m->data[i * m->cols + j] = (int64_t)(i + j);
}

static int64_t rows_route(const int64_t *data, size_t rows, size_t cols)
{
    int64_t sum = 0;

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            sum += data[i * cols + j];

    return sum;
}

static int64_t cols_route(const int64_t *data, size_t rows, size_t cols)
{
    int64_t sum = 0;

    for (size_t j = 0; j < cols; j++)
        for (size_t i = 0; i < rows; i++)
            sum += data[i * cols + j];

    return sum;
}

static double measure_once(traversal_fn fn, const Matrix *m, int64_t *out_sum)
{
    const double t0 = now_seconds();
    const int64_t sum = fn(m->data, m->rows, m->cols);
    const double t1 = now_seconds();

    *out_sum = sum;
    return t1 - t0;
}

static double now_seconds(void)
{
    return (double)clock() / (double)CLOCKS_PER_SEC;
}

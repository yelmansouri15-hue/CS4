#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static const size_t SIZES[] = {256, 512, 1024, 2048};
#define NUM_SIZES (sizeof(SIZES) / sizeof((SIZES)[0]))
#define WARMUP_RUNS 1U
#define MEASURED_RUNS 9U
#define CSV_PATH "benchmark.csv"

_Static_assert(NUM_SIZES > 0, "SIZES must not be empty");
_Static_assert(MEASURED_RUNS > 0, "MEASURED_RUNS must be greater than zero");

typedef struct
{
    int64_t *data;
    size_t rows;
    size_t cols;
} Matrix;

typedef struct
{
    size_t dimension;
    size_t bytes;
    double row_median_sec;
    double col_median_sec;
} BenchmarkRow;

typedef int64_t (*traversal_fn)(const int64_t *data, size_t rows, size_t cols);

static bool csv_init(FILE **out_file, const char *path);
static bool csv_append_row(FILE *fp, const BenchmarkRow *row);
static bool run_size_benchmark(size_t n, double *row_times, double *col_times, 
                               volatile int64_t *sink, BenchmarkRow *out_row);
static bool matrix_create(Matrix *m, size_t rows, size_t cols);
static void matrix_destroy(Matrix *m);
static void matrix_init(Matrix *m);
static int64_t rows_route(const int64_t *data, size_t rows, size_t cols);
static int64_t cols_route(const int64_t *data, size_t rows, size_t cols);
static double now_seconds(void);
static double measure_once(traversal_fn fn, const Matrix *m, int64_t *out_sum);
static bool median_seconds(const double *values, size_t count, double *out_median);
static int compare_doubles(const void *lhs, const void *rhs);

int main(void)
{
    volatile int64_t sink = 0;
    double row_times[MEASURED_RUNS];
    double col_times[MEASURED_RUNS];

    FILE *csv = NULL;
    if (!csv_init(&csv, CSV_PATH))
        return EXIT_FAILURE;

    for (size_t s = 0; s < NUM_SIZES; s++)
    {
        BenchmarkRow row = {0};

        if (!run_size_benchmark(SIZES[s], row_times, col_times, &sink, &row))
        {
            fclose(csv);
            return EXIT_FAILURE;
        }

        if (!csv_append_row(csv, &row))
        {
            fprintf(stderr, "Error: failed to write benchmark row for N=%zu.\n", SIZES[s]);
            fclose(csv);
            return EXIT_FAILURE;
        }
    }

    if (fclose(csv) != 0) 
    { 
        fprintf(stderr, "Error: failed to close '%s'.\n", CSV_PATH); 
        return EXIT_FAILURE; 
    }
    (void)sink;
    return EXIT_SUCCESS;
}

static bool csv_init(FILE **out_file, const char *path)
{
    if (out_file == NULL || path == NULL)
    {
        return false;
    }

    FILE *fp = fopen(path, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "Error: failed to open '%s' for writing.\n", path);
        return false;
    }

    if (fprintf(fp, "dimension,bytes,row_median_sec,col_median_sec\n") < 0)
    {
        fprintf(stderr, "Error: failed to write CSV header to '%s'.\n", path);
        fclose(fp);
        return false;
    }

    *out_file = fp;
    return true;
}

static bool csv_append_row(FILE *fp, const BenchmarkRow *row)
{
    if (fp == NULL || row == NULL)
    {
        return false;
    }

    if (fprintf(fp, "%zu,%zu,%.9f,%.9f\n",
                row->dimension,
                row->bytes,
                row->row_median_sec,
                row->col_median_sec) < 0)
    {
        return false;
    }

    return true;
}

static bool run_size_benchmark(size_t n, double *row_times, double *col_times, 
                               volatile int64_t *sink, BenchmarkRow *out_row)
{
    if (row_times == NULL || col_times == NULL || sink == NULL || out_row == NULL)
    {
        return false;
    }

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

    double row_median = 0.0;
    double col_median = 0.0;
    if (!median_seconds(row_times, MEASURED_RUNS, &row_median) ||
        !median_seconds(col_times, MEASURED_RUNS, &col_median))
    {
        fprintf(stderr, "Error: failed to compute medians for N=%zu.\n", n);
        return false;
    }

    out_row->dimension = n;
    out_row->bytes = n * n * sizeof(int64_t);
    out_row->row_median_sec = row_median;
    out_row->col_median_sec = col_median;

    return true;
}

static bool matrix_create(Matrix *m, size_t rows, size_t cols)
{
    if (m == NULL)
    {
        return false;
    }

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
    if (m == NULL)
    {
        return;
    }

    free(m->data);
    m->data = NULL;
    m->rows = 0;
    m->cols = 0;
}

static void matrix_init(Matrix *m)
{
    if (m == NULL || m->data == NULL)
    {
        return;
    }

    for (size_t i = 0; i < m->rows; i++)
        for (size_t j = 0; j < m->cols; j++)
            m->data[i * m->cols + j] = (int64_t)(i + j);
}

static int64_t rows_route(const int64_t *data, size_t rows, size_t cols)
{
    if (data == NULL) 
    { 
        return 0; 
    }

    int64_t sum = 0;

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            sum += data[i * cols + j];

    return sum;
}

static int64_t cols_route(const int64_t *data, size_t rows, size_t cols)
{
    if (data == NULL) 
    { 
        return 0; 
    }

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

static bool median_seconds(const double *values, size_t count, double *out_median)
{
    if (values == NULL || out_median == NULL || count == 0)
    {
        return false;
    }

    if (count > SIZE_MAX / sizeof(double))
    {
        return false;
    }

    double *copy = malloc(count * sizeof(double));
    if (copy == NULL)
    {
        return false;
    }

    memcpy(copy, values, count * sizeof(double));
    qsort(copy, count, sizeof(double), compare_doubles);

    const size_t mid = count / 2;
    if (count % 2 == 0)
    {
        *out_median = 0.5 * (copy[mid - 1] + copy[mid]);
    }
    else
    {
        *out_median = copy[mid];
    }

    free(copy);
    return true;
}

static int compare_doubles(const void *lhs, const void *rhs)
{
    const double a = *(const double *)lhs;
    const double b = *(const double *)rhs;

    if (a < b)
    {
        return -1;
    }
    if (a > b)
    {
        return 1;
    }
    return 0;
}

static double now_seconds(void)
{
    return (double)clock() / (double)CLOCKS_PER_SEC;
}

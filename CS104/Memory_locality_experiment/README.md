# Memory Spatial Locality Experiment: Row-Major vs. Column-Major Traversal

## 1. Objective

Experimentally quantify the impact of **spatial locality** and the CPU cache hierarchy on memory access performance in C using contiguous 2D arrays (`int64_t`), comparing row-major traversal against column-major traversal as matrix dimensions scale up.

---

## 2. Test Environment

> **Note:** Fill in the bracketed fields with your exact machine specifications before making your final commit.

* **Operating System:** `Windows`
* **Procesador (CPU):** 13th Gen Intel(R) Core(TM) i3-1315U
* **Memoria RAM:** 8 GB``
* **Compilador:** GCC
* **Compilation Fla`gs:*`* `-std=c11 -O2 -Wall -Wextra -pedantic`
* **Timer Used:** `clock()` (`<time.h>`)
``
---

## 3. Build and Execution Instructions

From the project root directory, compile the program with `-O2` optimization and strict warnings enabled:

```bash
gcc -std=c11 -O2 -Wall -Wextra -pedantic memory_locality_experiment.c -o memory_locality_experiment
```

Run the compiled binary to execute the benchmark and automatically generate benchmark.csv:
.\memory_locality_experiment

## 4. Methodology
To obtain reproducible measurements and minimize compiler or operating system bias, the benchmark follows this protocol:
1. **Contiguous Memory Layout:** Each $N \times N$ square matrix of 64-bit signed integers (`int64_t`) is allocated as a single contiguous heap block via `malloc` and indexed linearly using `i * cols + j`.
2. **Evaluated Matrix Sizes:** $N \in \{256, 512, 1024, 2048\}$, spanning memory footprints from `512 KiB` up to `32 MiB`.
3. **Cache Warm-Up:** Before starting timed measurements for each matrix size, one untimed warm-up pass is executed for both traversal patterns (`WARMUP_RUNS = 1`) to stabilize initial cache and CPU state.
4. **Repeated Runs & Alternating Order:** `MEASURED_RUNS = 9` timed iterations are executed per size. Even iterations measure row-major followed by column-major, while odd iterations reverse the order to eliminate systematic ordering bias.
5. **Dead-Code Elimination Prevention:** Under `-O2`, traversal checksums are verified (`row_sum == col_sum`) and accumulated into a `volatile int64_t sink` variable so the compiler cannot optimize away the loops.
6. **Robust Statistics:** The median of the 9 runs per traversal is computed via `qsort` over a temporary copy of the timings to filter out OS scheduling spikes. Results are exported to `benchmark.csv`.

## 5. Results
Data recorded in `benchmark.csv`, where the relative performance speedup is computed as:
$$
\text{Speedup} = \frac{T_{\text{column-major}}}{T_{\text{row-major}}}
$$
| N | Memory Footprint ($N2×8 B$) | Row-Major Time (Median) | Column-Major Time (Median) | Speedup |
| --- | --- | --- | --- | --- |
| **256** | `524,288 B` (`512 KiB`) | `0.000000000 s` | `0.000000000 s` | `—` | 
| **512** | `2,097,152 B `(`2 MiB`) | `0.000000000 s` | `0.001000000 s` | `—` |
| **1024** | `8,388,608 B ` (`8 MiB`) | `0.001000000 s` | `0.005000000 s` | `5.00x` |
| **2048** | `33,554,432 B` (`32 MiB`) | `0.003000000 s` | `0.051000000 s` | `17.00x` |

## 6. Conclusions
- **Row-Major Traversal Dominance:** Across all matrix dimensions where execution time exceeds the timer resolution threshold, row-major traversal is substantially faster than column-major traversal, achieving a 5x speedup at $N = 1024$ and a **17x speedup at** $N = 2048$.
- **Matrix Size & Cache Capacity Effects:** At smaller working sets ($N = 256$, `512 KiB`), the entire matrix fits comfortably within fast CPU caches and both traversals complete below the measurable tick threshold. As the footprint scales to `8 MiB` and `32 MiB`, it spills out of fast cache levels and frequent cache misses severely penalize non-contiguous access.
- **Spatial Locality & Cache Lines:** Because C stores multidimensional arrays in row-major order, row-wise iteration accesses adjacent addresses (`+8` bytes), maximizing utilization of each 64-byte cache line (8 `int64_t` elements) and enabling effective hardware prefetching. Conversely, column-wise iteration at $N = 2048$ strides by `16 KiB` (`2048 × 8` bytes) per step, causing frequent cache line evictions and increased **TLB** (*Translation Lookaside Buffer*) pressure.
- **Timer Resolution Limitations (`clock()`)**: For smaller matrices ($N = 256$ and $N = 512$), `clock()` reports `0.000000000 s` due to coarse tick granularity (`1 ms` in this environment). Capturing sub-millisecond differences at small sizes requires platform-specific high-resolution monotonic timers (`QueryPerformanceCounter` on Windows or `clock_gettime(CLOCK_MONOTONIC, ...)` on POSIX systems).
- **Hardware & Environment Sensitivity:** Exact execution times and degradation thresholds vary across processors depending on L1/L2/L3 cache sizes, DRAM bandwidth, dynamic frequency scaling, and compiler optimizations, though the structural advantage of spatial locality remains consistent.
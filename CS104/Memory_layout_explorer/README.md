# Memory Layout Explorer (C99)

A robust systems-level C program designed to explore data alignment, memory allocation, structure padding, pointer behavior, and array decay.

---

## Compilation

To compile the program with strict warnings and adherence to the C standard, use GCC (or Clang) with the following flags:

```bash
gcc -Wall -Wextra -Wpedantic -std=c11 memory_layout_explorer.c -o memory_layout_explorer
```
To run the executable:

```bash
./memory_layout_explorer
```

## Example Output
Below is a representative sample of what the program outputs during execution:

```Plaintext
		MEMORY LAYOUT EXPLORER
	In this environment, a byte has 8 bits
       char: size = 1 bytes		alignment = 1 bytes
      short: size = 2 bytes		alignment = 2 bytes
    int32_t: size = 4 bytes		alignment = 4 bytes
   int32_t*: size = 8 bytes		alignment = 8 bytes
      long: size = 8 bytes		alignment = 8 bytes
  long long: size = 8 bytes		alignment = 8 bytes
      float: size = 4 bytes		alignment = 4 bytes
     double: size = 8 bytes		alignment = 8 bytes
long double: size = 16 bytes		alignment = 16 bytes

Enter a size to create an int array: 5
	(Note: The distance between elements' addresses should be 4 bytes)
	Addresses: |0x55c1b69d12a0|0x55c1b69d12a4|0x55c1b69d12a8|0x55c1b69d12ac|0x55c1b69d12b0|

Press Enter to continue...

	And what if we change the ORDER of the members in a struct?
char - int - short:
       Inefficient_Struct: size = 12 bytes		alignment = 4 bytes
                   Offsets: first = 0	second = 4	third = 8	
int - short - char:
        Efficient_Struct: size = 8 bytes		alignment = 4 bytes
                   Offsets: first = 0	second = 4	third = 6	

Press Enter to continue...
	1. Array vs Pointer (in local scope):
sizeof(array)   = 40 bytes (Total array size)
sizeof(pointer) = 8 bytes (Pure pointer size)

	2. Array Decay (passing to a function):
Inside function, sizeof(array) = 8 bytes (It decayed to a pointer!)
```

## Technical Conclusions & Analysis
### 1. Observations
- **Type Sizes & Alignment**: Fundamental types (```char```, ```short```, ```int32_t```, ```long```, etc.) adhere strictly to architectural alignment boundaries, where the alignment requirement is typically equal to or related to their size in bytes. Pointers on a 64-bit architecture consistently occupy 8 bytes.

- **Struct Padding Impact**: Comparing ```Inefficient_Struct``` (```char```, ```int32_t```, ```short```) with ```Efficient_Struct``` (```int32_t```, ```short```, ```char```) reveals a dramatic difference in total memory footprint. Despite holding the exact same data fields, the inefficient layout occupies **12 bytes** while the efficient layout occupies only **8 bytes** due to hidden padding gaps.

- **Array vs. Pointer Semantics**: In local scope, ```sizeof(array)``` evaluates to the total size of the entire block in bytes, whereas ```sizeof(pointer)``` evaluates solely to the size of the address variable itself.

- **Array Decay**: When an array is passed as a function parameter, it "decays" automatically into a pointer to its first element. Consequently, applying ```sizeof``` inside the function yields the size of a pointer, proving that the array's size information does not travel by value across function boundaries.

### 2. Why padding gaps appear?
- **Hardware Efficiency**: Modern CPU architectures do not access arbitrary memory addresses with equal efficiency. Reading a 4-byte integer from an address aligned to a multiple of 4 bytes can be performed in a single memory transaction by the memory controller. Unaligned access can cause performance penalties or hardware faults depending on the architecture.

- **Alignment Constraints**: To satisfy these hardware alignment rules, the compiler inserts invisible bytes of padding between structure members so that each member sits at an offset that is a multiple of its alignment requirement. For instance, if a 1-byte ```char``` is followed by a 4-byte ```int32_t```, 3 bytes of padding must be inserted after the ```char``` so the ```int32_t``` starts cleanly at an offset divisible by 4.

### 3. Implementation-dependent results
- **Sizes of Fundamental Types**: The C standard defines minimum sizes (e.g., ```short``` is at least 2 bytes, ```long``` at least 4), but exact sizes (such as ```long double``` being 10, 16, or even 8 bytes) vary across compilers and hardware architectures (x86_64, ARM64, etc.).

- **Struct Padding & Alignment Rules**: The exact placement of padding bytes, overall struct sizes, and alignment requirements (```_Alignof```) are dictated by the target ABI (Application Binary Interface) and the compiler implementation.

- **Pointer Width**: Address sizes are strictly tied to the target architecture (e.g., 4 bytes on 32-bit systems, 8 bytes on 64-bit systems).
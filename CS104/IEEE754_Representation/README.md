# IEEE 754 Binary32 Decoder (CS104 Module)

Educational and industrial-grade implementation of a 32-bit single-precision floating-point decoder adhering to the **IEEE 754** standard, written in standard C (C11). The project strictly follows modular programming principles, defensive programming, and architecture validation at compile time.

---

## Compilation

To compile the program with strict warnings and standard compliance, use a compatible compiler like GCC or Clang:

```bash
gcc -std=c11 -Wall -Wextra ieee754_decoder.c -o ieee754_decoder
```

---

## Input Format & Usage

1. Run the generated binary from the terminal:
   ```bash
   ./ieee754_decoder
   ```
2. The program will prompt you to enter a decimal floating-point number (e.g., `5.5`, `-3.25`, `0.0`).
3. It features a robust input validation wrapper over `scanf` that clears the input buffer if invalid characters (such as letters) are entered, preventing infinite loops.

---

## Mathematical Foundations & Formulas

An IEEE 754 `binary32` number occupies exactly 4 bytes (32 bits) divided into three logical fields:

1. **Sign ($S$):** 1 bit (Bit 31). Indicates whether the number is positive ($0$) or negative ($1$).
2. **Exponent ($E$):** 8 bits (Bits 30–23). Encodes the magnitude using a bias of $127$.
3. **Fraction / Mantissa ($M$):** 23 bits (Bits 22–0). Represents the fractional precision bits.

### Real Value Reconstruction

#### 1. Normalized Numbers ($0 < E < 255$)
The true value is calculated by incorporating the implicit leading bit ($1.$):

$$\text{Value} = (-1)^S \times 2^{E - 127} \times \left(1 + \frac{M}{2^{23}}\right)$$

#### 2. Subnormal / Denormalized Numbers ($E = 0, M \neq 0$)
When the exponent is zero, there is no implicit leading bit ($0.$), allowing the representation of infinitesimally small values near zero:

$$\text{Value} = (-1)^S \times 2^{-126} \times \left(0 + \frac{M}{2^{23}}\right)$$

#### 3. Special Values
- **Zero ($E = 0, M = 0$):** Represents $+0$ or $-0$ depending on the sign bit.
- **Infinity ($E = 255, M = 0$):** Represents $+\infty$ or $-\infty$ depending on the sign bit.
- **NaN / Not a Number ($E = 255, M \neq 0$):** Represents invalid or undefined mathematical operations.

---

## Representative Test Cases

| Input Number | Sign ($S$) | Exponent Field ($E$) | Fraction Field ($M$) | Identified Type |
| :--- | :---: | :---: | :---: | :--- |
| **`0.0`** | `0` | `00000000` | `00000000000000000000000` | Zero |
| **`-0.0`** | `1` | `00000000` | `00000000000000000000000` | Zero |
| **`1.0`** | `0` | `01111111` | `00000000000000000000000` | Normalized |
| **`-5.5`** | `1` | `10000001` | `01100000000000000000000` | Normalized |
| **`INFINITY`** | `0` | `11111111` | `00000000000000000000000` | Infinity |
| **`NAN`** | `0` | `11111111` | `10000000000000000000000` | NaN |

---

## Console Output Example

```text
Enter a float number: -5.5
Sign bit: 1      Exponent field: 10000001         Fraction field: 01100000000000000000000 
Representation: 1 10000001 01100000000000000000000 
Type: Normalized
```
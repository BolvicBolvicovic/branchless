# Branchless

Exercises to practice writing branchless code in C.

## Exercises

- **max** - Find the maximum of two integers
- **clamp** - Clamp a value to [0, 255]
- **clamp_range** - Clamp a value to an arbitrary range
- **median** - Find the median of three integers
- **sort** - Swap two values if out of order

## Usage

Compile and run any exercise:

```bash
cd max
gcc -O2 -Wall -Wextra main.c && ./a.out
```

View the generated assembly:

```bash
gcc -O2 -S -masm=intel main.c -o -
```

# Branchless

Exercises to practice writing branchless code in C.

## Cheat Sheet

You can open the [cheat sheet](./branchless.excalidraw) in [Excalidraw](https://excalidraw.com/).

## Exercises

- **max** - Find the maximum of two integers
- **clamp** - Clamp a value to [0, 255]
- **clamp_range** - Clamp a value to an arbitrary range
- **median** - Find the median of three integers
- **sort** - Swap two values if out of order

## Usage

Compile update the branchless function and run any exercise:

```bash
cd max
vim main.c # Propose your solutions
gcc -O2 -Wall -Wextra main.c && ./a.out
```

View the generated assembly:

```bash
gcc -O2 -S -masm=intel main.c -o -
```

Solutions are in the [solutions](./solutions) folder.

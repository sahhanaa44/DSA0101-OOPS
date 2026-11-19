# Task 05 – Pointers to Objects and the this Pointer

**Name:** [Your Name]  
**Register Number:** [Your Register Number]  
**Compiler:** g++ [write your version]

## Files
- `task05_cart.cpp` – method chaining, `this`, direct object, pointer, reference, dynamic object, and highest-total search.

## Compile and run
```bash
g++ -std=c++17 -Wall -Wextra task05_cart.cpp -o task05
./task05
```
Windows PowerShell:
```powershell
g++ -std=c++17 -Wall -Wextra task05_cart.cpp -o task05.exe
.\task05.exe
```

## Result
The chained calls produce `324.00`. The example also shows direct access, `->` through a pointer, reference access, and a dynamically allocated object released with `delete`.

## Concepts
- `this` points to the current object.
- `*this` is the current object itself as an lvalue, allowing a method to return `Cart&` and support chaining.
- Returning `Cart` by value makes copies and means each chained call may operate on a temporary copy.
- Highest-total search is O(n). If a `std::vector<Cart>` grows and reallocates, pointers/references/iterators to its elements can be invalidated.

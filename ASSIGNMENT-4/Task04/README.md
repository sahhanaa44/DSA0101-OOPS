# Task 04 – Pointers to Derived Classes: Forensics

**Name:** [Your Name]  
**Register Number:** [Your Register Number]  
**Compiler:** g++ [write your version]

## Files
- `task04_accounts.cpp` – corrected polymorphic account design and slicing demonstration.

## Compile and run
```bash
g++ -std=c++17 -Wall -Wextra task04_accounts.cpp -o task04
./task04
```
To run with AddressSanitizer where supported:
```bash
g++ -std=c++17 -Wall -Wextra -fsanitize=address -fno-omit-frame-pointer task04_accounts.cpp -o task04_asan
./task04_asan
```

## Defects in the original design
- `rate()` was non-virtual, so `Account*` calls the base implementation.
- A non-virtual base destructor makes deleting a derived object through `Account*` undefined behavior.
- A raw owning pointer needs correct copy/move handling; otherwise copying can cause leaks or double deletion.
- `Account copy = SeniorAccount()` slices off the derived part.
- Use `override`, a virtual destructor, and smart pointers such as `std::unique_ptr`.

## Result
The corrected program calls the derived rate through `vrate()` and safely owns account objects with `std::unique_ptr`.

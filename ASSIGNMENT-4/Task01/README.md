# Task 01 – Class Design Review

**Name:** [Your Name]  
**Register Number:** [Your Register Number]  
**Compiler:** g++ [write your version]

## Files
- `task01_payroll.cpp` – common base class, overridden `pay()` functions, and polymorphic processing.

## Compile and run
```bash
g++ -std=c++17 -Wall -Wextra task01_payroll.cpp -o task01
./task01
```
On Windows PowerShell:
```powershell
g++ -std=c++17 -Wall -Wextra task01_payroll.cpp -o task01.exe
.\task01.exe
```

## Result
The program stores Professor, LabAssistant, and GuestFaculty objects through `Staff*` pointers and calls the correct `pay()` implementation through runtime polymorphism.

## Design review notes
- Repeated name, ID, and basic-pay fields belong in a common base class.
- Public data permits invalid values; use protected/private data and public accessors.
- Inconsistent names (`name`/`nm`, `id`/`code`) make maintenance harder.
- `da` is unused, which is misleading.
- `0.42` is a magic number; represent it as a named constant or configurable rule.
- A single polymorphic loop can process every staff category.
- A new category can be added as a derived class without rewriting the loop.

## Alternative (one class + type switch)
Both approaches take O(1) time per `pay()` call. A single class with all fields wastes space on fields unused by some staff types and requires edits to the class and switch whenever a new type is added. Inheritance keeps type-specific data in derived classes.

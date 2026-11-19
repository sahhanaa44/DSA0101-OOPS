# Task 03 – Constructors in Derived Classes and Member Classes

**Name:** [Your Name]  
**Register Number:** [Your Register Number]  
**Compiler:** g++ [write your version]

## Files
- `task03_construction.cpp` – base/member/derived construction and reverse destruction order.
- `task03_student_address.cpp` – completed TODO constructor from the assignment.

## Compile and run
```bash
g++ -std=c++17 -Wall -Wextra task03_construction.cpp -o task03
./task03
g++ -std=c++17 -Wall -Wextra task03_student_address.cpp -o task03_student
./task03_student
```
Use `.exe` names and `.\program.exe` in Windows PowerShell.

## Rules
1. Virtual base classes are constructed first.
2. Direct base classes are constructed in the order they appear in the inheritance list.
3. Member objects are constructed in the order they are declared in the class, not the order in the initializer list.
4. The derived-class constructor body runs last.
5. Destruction occurs in reverse construction order.

## Result
The completed Student constructor initializes the Person base, then `regNo`, then the Address member using an initializer list. Swapping initializer-list entries does not change construction order; compilers may warn about the mismatch.

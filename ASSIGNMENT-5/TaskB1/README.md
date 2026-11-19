# Task B1 – Implement and Validate Polymorphic Billing
Compile: `g++ -std=c++17 -Wall -Wextra main.cpp -o program`
Run: `./program`
Expected output is in `expected_output.txt`. Totals: OP = 500 + 1200 = 1700; IP = 3 × 2500 + 40000 = 47500; combined = 49200.
To investigate binding, remove `virtual` from `total()`: the base declaration is pure virtual in this example, so removing `virtual` makes the declaration invalid (`= 0` is only allowed for virtual functions). To compare non-virtual dispatch, replace the interface with a non-virtual base method and observe that it cannot dynamically select the derived calculation.
To investigate destruction, remove `virtual` from the base destructor and test with `-fsanitize=address`; deleting a derived object through a base pointer is undefined behaviour, so no particular diagnostic/output is guaranteed.

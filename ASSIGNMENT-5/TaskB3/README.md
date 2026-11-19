# Task B3 – Virtual vs Switch vs Exceptions Cost
This benchmark compares virtual dispatch with a tagged `switch` representation for 10, 1,000, 1,000,000 and 10,000,000 generated bills. Compile using:
`g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o benchmark`
Run `./benchmark`. It prints measured durations on your machine. Do not copy another machine's timings as your own.

The exception/return-code test compares 1,000,000 validations with 0%, 1% and 50% invalid data. Exception timings are especially sensitive to the invalid percentage. Both approaches must produce the same accepted/rejected count.

Alternative `std::variant`: store `variant<OP,IP>` values in one vector and use `std::visit` with an overloaded visitor. It keeps one heterogeneous container; each element occupies enough space for its largest alternative plus a discriminator (implementation-dependent). Measure it separately if required by your instructor.

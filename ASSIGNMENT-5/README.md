# Task B4 – Final Engineering Decision
This task extends the hierarchy with a new bill type and payer without modifying existing classes, then runs exception tests under AddressSanitizer.

Compile:
`g++ -std=c++17 -Wall -Wextra -fsanitize=address -fno-omit-frame-pointer main.cpp -o program`
Run: `./program`

Production decision: for a hospital billing domain with frequent new bill and payer types, abstract interfaces and virtual dispatch provide a maintainable extension point. Exceptions are appropriate for exceptional invalid claims and infrastructure failures; routine outcomes should remain explicit. Production deployment still requires persistent transactions, audit logging, authentication, validation, concurrency testing and measured load testing.

Plugin/configuration alternative: encode rate rules in validated configuration and interpret them at runtime. Rule evaluation may take more time than a direct virtual call but avoids compiling a new class for simple rate changes. Configuration needs schema validation, versioning and safe rollout; arbitrary new behaviour may still require code plugins.

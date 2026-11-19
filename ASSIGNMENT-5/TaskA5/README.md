# Task A5 – Recovery and Rethrowing
## Catch locations
- Validate near the input or domain boundary and throw a specific exception.
- Catch at a layer that can add useful context (audit/logging); use `throw;` to rethrow the same exception.
- Catch at the application boundary to report a clear message to the user and continue or terminate safely.

## Stack unwinding / RAII
When an exception leaves a scope, local automatic objects are destroyed in reverse construction order. RAII objects such as `std::string`, `std::vector`, `std::unique_ptr` and file streams release their resources automatically. Manual `delete` in every catch block is fragile because every new error path must repeat cleanup.

## Predict the given program
Expected output:
```text
~f ~main caught 42
```
`f`'s local Guard is destroyed first as the exception leaves `f`; then `main`'s Guard is destroyed while unwinding to the handler. The statement `not printed` is skipped because control transfers to the matching catch block.

## Alternative: manual delete
Manual cleanup has similar asymptotic time, but every return/throw/catch path must release every owned resource. Each missing cleanup branch can leak. RAII centralizes cleanup in destructors.

# Task A4 – Exception Strategy
## Error cases
- Negative consultation, room, procedure or package charge → `InvalidChargeError`.
- Claim exceeds policy cover → `ClaimError`.
- Unknown government package → `UnknownPackageError`.
- Missing patient record → `PatientNotFoundError`.
- Allocation failure → standard `std::bad_alloc`.

## Exception hierarchy
```mermaid
classDiagram
 std::exception <|-- BillingError
 BillingError <|-- InvalidChargeError
 BillingError <|-- ClaimError
 BillingError <|-- UnknownPackageError
 BillingError <|-- PatientNotFoundError
```
Functions validating input, calculating claims, looking up packages and allocating may throw. Destructors and cleanup functions should not throw; mark suitable functions `noexcept`. A throwing destructor during stack unwinding can cause `std::terminate`.

## Alternative: return status
A function returns an enum/status and writes the result through an output parameter. Normal execution avoids exception handling overhead and error paths are explicit. The caller must check every status and propagate messages/results through each layer. This adds branching and parameter/code complexity. Exceptions separate normal logic from exceptional paths but should not be used for routine control flow.

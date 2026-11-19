# Task A2 – Runtime Binding
## Early vs late binding
A non-virtual call is resolved by the compiler using the declared type (early/static binding). A virtual call through `Bill*` is resolved at runtime using the actual object type (late/dynamic binding). Thus `b->total()` invokes the override belonging to the object.

## Conceptual vtables
```text
Bill vtable:          OutPatientBill vtable:     InPatientBill vtable:
total -> pure         total -> OutPatientBill    total -> InPatientBill
type  -> pure         type  -> OutPatientBill    type  -> InPatientBill
~Bill  -> destructor  ~Bill -> derived cleanup  ~Bill -> derived cleanup
```
`b` points to an OutPatientBill. The object's vptr selects the OutPatientBill vtable; the `total` slot leads to `OutPatientBill::total()`.

## Why virtual destructor?
Deleting a derived object through `Bill*` must run the derived destructor and then the base destructor. Without a virtual base destructor, this is undefined behaviour and derived resources may not be released.

## Predict the given program
Expected output:
```text
500 ~OPBill ~Bill
```
`show()` itself is non-virtual, but it calls virtual `total()`. The inner call is dynamically dispatched. `delete b` invokes the derived then base destructor because `~Bill` is virtual. If `~Bill` is made non-virtual, deleting through the base pointer is undefined behaviour; do not treat any observed output as guaranteed. AddressSanitizer may or may not diagnose it.

## Alternative: dynamic_cast
The program could test each possible derived type with `dynamic_cast` and call its calculation. For k types, this can require up to k runtime checks per bill, versus one virtual dispatch. Both total n bills in O(n) for a fixed number of types, but casts increase constants and require editing the dispatch logic when types are added. A polymorphic object generally carries a vptr (implementation-dependent pointer-sized overhead).

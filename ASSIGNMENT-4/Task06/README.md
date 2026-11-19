# Task 06 – Design Challenge: Vehicle Rental Fleet

**Name:** [Your Name]  
**Register Number:** [Your Register Number]  
**Compiler:** g++ [write your version]

## Files
- `task06_vehicle_fleet.cpp` – abstract `Vehicle` base class, derived vehicle types, rent/return, late charge, and polymorphic fleet storage.

## Compile and run
```bash
g++ -std=c++17 -Wall -Wextra task06_vehicle_fleet.cpp -o task06
./task06
```
Windows PowerShell:
```powershell
g++ -std=c++17 -Wall -Wextra task06_vehicle_fleet.cpp -o task06.exe
.\task06.exe
```

## Design summary
- `Vehicle` stores shared registration and daily rate data and declares the pure virtual `rentalCharge()` function.
- `Bicycle`, `TwoWheeler`, `Car`, and `ElectricCar` override the charge calculation.
- `MotorVehicle` is an intermediate abstract class for fuel/charge level and service due date.
- `Car` adds seating capacity; `ElectricCar` adds battery capacity and cost per kWh.
- A fleet of `std::unique_ptr<Vehicle>` allows one loop to list mixed vehicle types safely.
- Returning late adds a fee based on the number of late days.

## Result
The demo rents and returns several vehicle types, calculates a late fee, and demonstrates extension by adding an `ElectricBus` derived type without changing the fleet-processing loop.

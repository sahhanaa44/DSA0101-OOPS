#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Vehicle {
protected:
    std::string registration_;
    double dailyRate_;
    bool rented_ = false;

public:
    Vehicle(std::string registration, double dailyRate)
        : registration_(std::move(registration)), dailyRate_(dailyRate) {}
    virtual ~Vehicle() = default;

    virtual double rentalCharge(int days) const = 0;
    virtual const char* type() const = 0;

    void rent() {
        if (!rented_) {
            rented_ = true;
            std::cout << registration_ << " rented\n";
        } else {
            std::cout << registration_ << " is already rented\n";
        }
    }

    double returnVehicle(int lateDays) {
        rented_ = false;
        const double lateFee = lateDays > 0 ? lateDays * 200.0 : 0.0;
        std::cout << registration_ << " returned; late fee: " << lateFee << '\n';
        return lateFee;
    }

    void list() const {
        std::cout << type() << " | " << registration_
                  << " | base rental for 1 day: " << rentalCharge(1) << '\n';
    }
};

class Bicycle : public Vehicle {
public:
    using Vehicle::Vehicle;
    double rentalCharge(int days) const override { return dailyRate_ * days; }
    const char* type() const override { return "Bicycle"; }
};

class MotorVehicle : public Vehicle {
protected:
    double fuelOrChargeLevel_;
    std::string serviceDueDate_;

public:
    MotorVehicle(std::string registration, double rate, double level,
                 std::string serviceDate)
        : Vehicle(std::move(registration), rate),
          fuelOrChargeLevel_(level), serviceDueDate_(std::move(serviceDate)) {}
};

class TwoWheeler : public MotorVehicle {
public:
    using MotorVehicle::MotorVehicle;
    double rentalCharge(int days) const override { return dailyRate_ * days; }
    const char* type() const override { return "Two-wheeler"; }
};

class Car : public MotorVehicle {
protected:
    int seats_;

public:
    Car(std::string registration, double rate, double level,
        std::string serviceDate, int seats)
        : MotorVehicle(std::move(registration), rate, level, std::move(serviceDate)),
          seats_(seats) {}
    double rentalCharge(int days) const override { return dailyRate_ * days; }
    const char* type() const override { return "Car"; }
};

class ElectricCar : public Car {
    double batteryCapacityKWh_;
    double costPerKWh_;

public:
    ElectricCar(std::string registration, double rate, double level,
                std::string serviceDate, int seats,
                double batteryCapacityKWh, double costPerKWh)
        : Car(std::move(registration), rate, level, std::move(serviceDate), seats),
          batteryCapacityKWh_(batteryCapacityKWh), costPerKWh_(costPerKWh) {}

    double rentalCharge(int days) const override {
        return dailyRate_ * days + batteryCapacityKWh_ * costPerKWh_;
    }
    const char* type() const override { return "Electric car"; }
};

class ElectricBus : public MotorVehicle {
    int seats_;
    double batteryCapacityKWh_;
    double costPerKWh_;

public:
    ElectricBus(std::string registration, double rate, double level,
                std::string serviceDate, int seats,
                double batteryCapacityKWh, double costPerKWh)
        : MotorVehicle(std::move(registration), rate, level, std::move(serviceDate)),
          seats_(seats), batteryCapacityKWh_(batteryCapacityKWh),
          costPerKWh_(costPerKWh) {}

    double rentalCharge(int days) const override {
        return dailyRate_ * days + batteryCapacityKWh_ * costPerKWh_;
    }
    const char* type() const override { return "Electric bus"; }
};

int main() {
    std::vector<std::unique_ptr<Vehicle>> fleet;
    fleet.push_back(std::make_unique<Bicycle>("BIKE-01", 150));
    fleet.push_back(std::make_unique<TwoWheeler>("TN01-A1234", 500, 70, "2026-12-01"));
    fleet.push_back(std::make_unique<Car>("TN01-C5678", 1800, 60, "2026-11-20", 5));
    fleet.push_back(std::make_unique<ElectricCar>("TN01-E9999", 2200, 80,
                                                  "2026-12-15", 5, 60, 8));

    for (const auto& vehicle : fleet) vehicle->list();

    fleet[2]->rent();
    std::cout << "Three-day charge: " << fleet[2]->rentalCharge(3) << '\n';
    fleet[2]->returnVehicle(2);

    // New vehicle type added without changing the fleet loop:
    fleet.push_back(std::make_unique<ElectricBus>("TN01-B8888", 3500, 90,
                                                  "2026-12-30", 40, 180, 8));
    fleet.back()->list();
    return 0;
}

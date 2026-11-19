#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
class Staff {
protected:
    std::string name_;
    int id_;
    double basic_;

public:
    Staff(std::string name, int id, double basic)
        : name_(std::move(name)), id_(id), basic_(basic) {}
    virtual ~Staff() = default;
    virtual double pay() const = 0;
    virtual const char* role() const = 0;

    void print() const {
        std::cout << role() << " | " << name_ << " | ID " << id_
                  << " | Pay: " << std::fixed << std::setprecision(2)
                  << pay() << '\n';
    }
};

class Professor : public Staff {
    double research_;

public:
    Professor(std::string name, int id, double basic, double research)
        : Staff(std::move(name), id, basic), research_(research) {}
    double pay() const override { return basic_ * 1.42 + research_; }
    const char* role() const override { return "Professor"; }
};

class LabAssistant : public Staff {
public:
    LabAssistant(std::string name, int id, double basic)
        : Staff(std::move(name), id, basic) {}
    double pay() const override { return basic_ * 1.42; }
    const char* role() const override { return "Lab Assistant"; }
};

class GuestFaculty : public Staff {
    double hours_;
    double rate_;

public:
    GuestFaculty(std::string name, int id, double hours, double rate)
        : Staff(std::move(name), id, 0.0), hours_(hours), rate_(rate) {}
    double pay() const override { return hours_ * rate_; }
    const char* role() const override { return "Guest Faculty"; }
};

int main() {
    std::vector<std::unique_ptr<Staff>> staff;
    staff.push_back(std::make_unique<Professor>("Ananya", 101, 50000, 8000));
    staff.push_back(std::make_unique<LabAssistant>("Kavin", 102, 30000));
    staff.push_back(std::make_unique<GuestFaculty>("Mira", 103, 40, 900));

    for (const auto& member : staff) member->print();
    return 0;
}

#include <iostream>
#include <memory>
#include <vector>
#include <string>
struct Bill {
    std::string patient;
    explicit Bill(std::string p) : patient(std::move(p)) {}
    virtual ~Bill() = default;
    virtual double total() const = 0;
    virtual std::string type() const = 0;
    void print() const { std::cout << type() << " " << patient << ": " << total() << '\n'; }
};
struct OP : Bill {
    double consultation, tests;
    OP(std::string p,double c,double t):Bill(std::move(p)),consultation(c),tests(t){}
    double total() const override { return consultation+tests; }
    std::string type() const override { return "OP"; }
};
int main() {
    std::vector<std::unique_ptr<Bill>> bills;
    bills.push_back(std::make_unique<OP>("Ravi",500,1200));
    double sum=0; for (const auto& b:bills) { b->print(); sum+=b->total(); }
    std::cout << "Daily total " << sum << '\n';
}
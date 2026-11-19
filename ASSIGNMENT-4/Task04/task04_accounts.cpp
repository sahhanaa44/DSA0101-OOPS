#include <iostream>
#include <memory>
#include <vector>

class Account {
public:
    virtual double rate() const { return 3.5; }
    virtual ~Account() = default;
};

class SeniorAccount : public Account {
    double* history_;

public:
    SeniorAccount() : history_(new double[100]{}) {}
    SeniorAccount(const SeniorAccount&) = delete;
    SeniorAccount& operator=(const SeniorAccount&) = delete;
    ~SeniorAccount() override { delete[] history_; }
    double rate() const override { return 4.0; }
};

int main() {
    std::vector<std::unique_ptr<Account>> accounts;
    accounts.push_back(std::make_unique<Account>());
    accounts.push_back(std::make_unique<SeniorAccount>());

    for (const auto& account : accounts) {
        std::cout << account->rate() << '\n';
    }

    SeniorAccount senior;
    Account* p = &senior;
    Account slicedCopy = senior; // Demonstrates slicing: derived part is not copied.
    std::cout << "Base pointer rate: " << p->rate() << '\n';
    std::cout << "Sliced copy rate: " << slicedCopy.rate() << '\n';
    return 0;
}

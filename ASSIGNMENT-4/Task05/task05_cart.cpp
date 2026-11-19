#include <iomanip>
#include <iostream>
#include <string>

class Cart {
    std::string items_[10];
    double prices_[10]{};
    int n_ = 0;
    double discount_ = 0.0;

public:
    Cart& add(const std::string& item, double price) {
        if (n_ < 10) {
            items_[n_] = item;
            prices_[n_] = price;
            ++n_;
        }
        return *this;
    }

    Cart& setDiscount(double discount) {
        this->discount_ = discount;
        return *this;
    }

    double total() const {
        double sum = 0.0;
        for (int i = 0; i < n_; ++i) sum += prices_[i];
        return sum * (100.0 - discount_) / 100.0;
    }
};

int main() {
    Cart c;
    c.add("Rice", 60).add("Dal", 120).setDiscount(10);

    Cart* p = &c;
    p->add("Oil", 180);
    std::cout << std::fixed << std::setprecision(2) << p->total() << '\n';

    Cart& ref = c;
    ref.setDiscount(0);
    std::cout << "Through reference: " << ref.total() << '\n';

    Cart* dynamicCart = new Cart;
    dynamicCart->add("Tea", 50);
    std::cout << "Dynamic cart: " << dynamicCart->total() << '\n';
    delete dynamicCart;

    Cart* carts[] = {&c, &ref};
    Cart* highest = carts[0];
    for (Cart* cart : carts) {
        if (cart->total() > highest->total()) highest = cart;
    }
    std::cout << "Highest total: " << highest->total() << '\n';
    return 0;
}

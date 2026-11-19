#include <iostream>
struct Bill { double amount; };
struct Payer { virtual ~Payer()=default; virtual double amountCovered(const Bill&) const=0; };
struct SelfPay: Payer { double amountCovered(const Bill& b) const override{return b.amount;} };
struct Insurance: Payer {
    double limit, copay;
    Insurance(double l,double c):limit(l),copay(c){}
    double amountCovered(const Bill& b) const override {
        if(limit<0 || copay<0 || copay>100) throw "invalid policy";
        return (b.amount<limit?b.amount:limit)*(1-copay/100.0);
    }
};
int main(){Bill b{1000}; SelfPay p; std::cout<<p.amountCovered(b)<<'\n';}
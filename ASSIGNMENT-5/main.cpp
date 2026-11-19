#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>
#include <vector>
struct Bill{virtual ~Bill()=default;virtual double total()const=0;virtual std::string type()const=0;};
struct OP:Bill{double c,t;OP(double a,double b):c(a),t(b){}double total()const override{return c+t;}std::string type()const override{return "OP";}};
struct DayCare:Bill{double package;explicit DayCare(double p):package(p){if(p<0)throw std::invalid_argument("negative package");}double total()const override{return package;}std::string type()const override{return "DayCare";}};
struct Payer{virtual ~Payer()=default;virtual double pay(const Bill&)const=0;};
struct SelfPay:Payer{double pay(const Bill& b)const override{return b.total();}};
struct CorporatePayer:Payer{double discount;explicit CorporatePayer(double d):discount(d){}double pay(const Bill& b)const override{if(discount<0||discount>100)throw std::invalid_argument("invalid discount");return b.total()*(1-discount/100);}};
int main(){
 std::vector<std::unique_ptr<Bill>> bills;
 bills.push_back(std::make_unique<OP>(500,1200));
 bills.push_back(std::make_unique<DayCare>(25000));
 CorporatePayer corporate(10);
 for(const auto& b:bills)std::cout<<b->type()<<" total "<<b->total()<<", corporate pays "<<corporate.pay(*b)<<'\n';
 try{DayCare invalid(-5);}catch(const std::exception& e){std::cout<<"caught: "<<e.what()<<'\n';}
}
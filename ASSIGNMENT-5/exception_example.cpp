#include <iostream>
#include <stdexcept>
struct BillingError:std::runtime_error{using std::runtime_error::runtime_error;};
struct ClaimError:BillingError{using BillingError::BillingError;};
double approve(double amount,double cover){
    if(amount<0 || cover<0) throw std::invalid_argument("negative amount");
    if(amount>cover) throw ClaimError("exceeds cover");
    return amount;
}
int main(){try{std::cout<<approve(120,100)<<'\n';}
catch(const std::exception& e){std::cout<<e.what()<<'\n';}}
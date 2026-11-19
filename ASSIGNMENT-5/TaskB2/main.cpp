#include <iostream>
#include <stdexcept>
#include <string>
#include <new>
class ClaimError:public std::runtime_error{public:using std::runtime_error::runtime_error;};
double approve(double billed,double cover){
    if(billed<0 || cover<0) throw std::invalid_argument("negative amount");
    if(billed>cover) throw ClaimError("exceeds cover");
    return billed;
}
double settle(double billed,double cover){
    try{return approve(billed,cover);}
    catch(const ClaimError& e){std::cout<<"audit: "<<e.what()<<'\n';throw;}
}
int main(){
    double cases[][2]={{40000,50000},{60000,50000},{-1,50000}};
    for(auto& c:cases) try {double paid=settle(c[0],c[1]); std::cout<<"approved "<<paid<<'\n';}
    catch(const ClaimError& e){std::cout<<"claim rejected: "<<e.what()<<'\n';}
    catch(const std::exception& e){std::cout<<"error: "<<e.what()<<'\n';}
    try { double x=std::stod("not-a-number"); (void)x; }
    catch(const std::exception& e){std::cout<<"text input: "<<e.what()<<'\n';}
    try { std::size_t n=static_cast<std::size_t>(-1); int* p=new int[n]; delete[] p; }
    catch(const std::bad_alloc&){std::cout<<"allocation failed safely\n";}
}
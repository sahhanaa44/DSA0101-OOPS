#include <iostream>
#include <vector>
#include <chrono>
#include <stdexcept>
#include <string>
#include <iomanip>
struct Base{virtual ~Base()=default;virtual double total()const=0;};
struct OP:Base{double a,b;OP(double x,double y):a(x),b(y){}double total()const override{return a+b;}};
struct IP:Base{double a,b;IP(double x,double y):a(x),b(y){}double total()const override{return a+b;}};
struct Plain{int type;double a,b;};
using Clock=std::chrono::steady_clock;
template<class F> double measure(F f){auto s=Clock::now();volatile double result=f();(void)result;return std::chrono::duration<double,std::milli>(Clock::now()-s).count();}
int main(){
 for(int n:{10,1000,1000000,10000000}){
  std::vector<Base*> v;std::vector<Plain> p;v.reserve(n);p.reserve(n);
  for(int i=0;i<n;++i){if(i%2){v.push_back(new OP(500,1200));p.push_back({0,500,1200});}else{v.push_back(new IP(7500,40000));p.push_back({1,7500,40000});}}
  double tv=measure([&]{double s=0;for(auto x:v)s+=x->total();return s;});
  double ts=measure([&]{double s=0;for(auto x:p)s+=(x.type==0?x.a+x.b:x.a+x.b);return s;});
  std::cout<<n<<" bills: virtual "<<tv<<" ms, switch "<<ts<<" ms\n";
  for(auto x:v)delete x;
 }
 for(int rate:{0,1,50}){
  const int n=1000000;std::vector<double> values(n,100.0);
  for(int i=0;i<n*rate/100;++i)values[i]=-1;
  int valid1=0,valid2=0;
  double tr=measure([&]{int c=0;for(double x:values){if(x>=0)++c;}valid1=c;return c;});
  double te=measure([&]{int c=0;for(double x:values){try{if(x<0)throw std::invalid_argument("negative");++c;}catch(const std::exception&){} }valid2=c;return c;});
  std::cout<<rate<<"% invalid: return-code "<<tr<<" ms ("<<valid1<<"), exceptions "<<te<<" ms ("<<valid2<<")\n";
 }
}
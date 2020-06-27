#include "polynom.h"

polynom::polynom(int n, int arr[]) :
    func(),
    n_(n)
{
    coefs_ = new int[n + 1]; //alocate array of n+1 coeffs(0,...,n)
    for (int i = 0; i <= n; i++)
        coefs_[i] = arr[i];
}

polynom::polynom(const polynom& p) :
    func(),
    n_(p.n_)
{
    coefs_ = new int[n_ + 1]; //alocate array of n+1 coeffs(0,...,n)
    for (int i = 0; i <= n_; i++)
        coefs_[i] = p.coefs_[i];
}

polynom::~polynom() {
    delete[] coefs_;
}

polynom polynom::operator+(const polynom& p2) const {
    polynom pRes(*this);
    for (int i = 0; i <= pRes.n_; i++) {
        pRes.coefs_[i] = coefs_[i] + p2.coefs_[1];
    }
    return pRes;
}

polynom polynom::operator-(const polynom& p2) const {

}

polynom polynom::operator*(const polynom& p2) const {

}

void polynom::print(ostream& os) const {

}

void polynom::printcoefs(ostream& os)  const {
  int allZero = 1;
  for (auto i = n_ ; i>=0; i--) {
    if (coefs_[i]>0) {
      allZero = 0;
      if(i!=n_){
	os << "+";
      }
      if (coefs_[i]!=1 || i==0){
	os << coefs_[i];
      }
      if(i>0) {
	os << "x";
	if (i>1) 
	  os << "^" << i ;
      }
    }
    else if(coefs_[i]<0) {
      allZero = 0;
      if (coefs_[i]!=-1 || i==0){
	os << coefs_[i];
      }
      else 
	os << "-";
      if(i>0) {
	os << "x";
	if (i>1) 
	  os << "^" << i ;
      }
    }
    else if(i==0 && allZero == 1){ //coefs_[i]==0
        os << "0";
	continue;
    }
  }
}

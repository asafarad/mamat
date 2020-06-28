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
    delete [] coefs_;
}

polynom polynom::operator+(const polynom& p2) const {
    polynom bigger(*this);
    int n_min, n_max;
    
    if (this->n_ < p2.n_) {
        n_min = this->n_;
        n_max = p2.n_;
        bigger = p2;
    }
    else {
        n_min = p2.n_;
        n_max = this->n_;
        bigger = *this;
    }

    //We shall declare our result as the polynom with 
    //the higher degree, and then add the coeffs of
    //the lower degree polynom
    for (int i = 0; i <= n_min; i++) {
        bigger.coefs_[i] = coefs_[i] + p2.coefs_[i];
    }
    // CHECK-ASSIGNMENT OPERATOR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    int n_new = 0;
    for (int i = n_max; i >= 0; i--) {
        if (bigger.coefs_[i] != 0) {
            n_new = i;
            break;
        }
    }
    polynom pRes(n_new, bigger.coefs_);
    return pRes;
}

//IMPLEMENT ASSIGMENT OP//////////////////////////////////////////////////////////////////

polynom polynom::operator-(const polynom& p2) const {
    polynom bigger(*this);
    int n_min, n_max;

    if (this->n_ < p2.n_) {
        n_min = this->n_;
        n_max = p2.n_;
        bigger = p2;
    }
    else {
        n_min = p2.n_;
        n_max = this->n_;
        bigger = *this;
    }

    //We shall declare our result as the polynom with 
    //the higher degree, and then add the coeffs of
    //the lower degree polynom
    for (int i = 0; i <= n_min; i++) {
        bigger.coefs_[i] = coefs_[i] - p2.coefs_[i];
    }
    // CHECK-ASSIGNMENT OPERATOR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    int n_new;
    for(int i = n_max; i >= 0; i--) {
        if (bigger.coefs_[i] != 0) {
            n_new = i;
            break;
        }
    }
    polynom pRes(n_new, bigger.coefs_);
    return pRes;
}

polynom polynom::operator*(const polynom& p2) const {

}

polynom polynom::Derivative() const {

}

polynom polynom::Integral() const {

}

polynom& polynom::operator<<(const int& x) {

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

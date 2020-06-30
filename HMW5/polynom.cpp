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

polynom::polynom(int n) :
    func(),
    n_(n)
{
    coefs_ = new int[n + 1]; //alocate array of n+1 coeffs(0,...,n)
    for (int i = 0; i <= n; i++)
        coefs_[i] = 0;
}

polynom::~polynom() {
    delete [] coefs_;
}

polynom polynom::operator+(const polynom& p2) const {
    polynom bigger(n_);
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
    polynom p2_neg(*this);
    for (int i = 0; i <= p2_neg.n_; i++) {
        p2_neg.coefs_[i] = (-1) * p2_neg.coefs_[i];
    }
    return (*this + p2_neg); // this - p2
    /*polynom bigger(*this);
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
    return pRes;*/
}

polynom polynom::operator*(const polynom& p2) const {
    int n_res = n_ + p2.n_;
    //int* array = new int[n_res + 1];
 
    polynom result(n_res);
    for (int i = 0; i <= n_; i++) {
        for (int j = 0; j <= p2.n_; j++) {
            result.coefs_[i + j] = result.coefs_[i + j]
                + coefs_[i] * p2.coefs_[j];
        }
    }

    int n_new = 0;
    for (int i = n_res; i >= 0; i--) {
        if (result.coefs_[i] != 0) {
            n_new = i;
            break;
        }
    }
    polynom pRes(n_new, result.coefs_);
    //delete[] array;
    return pRes;

}

polynom polynom::Derivative() const {
    if (n_ == 0) {
        int array[1] = { 0 };
        polynom result(n_, array);
        return result;
    }
    int n_res = n_ - 1;
    //int* array = new int[n_res + 1];
    //*array = { 0 };
    polynom result(n_res);

    for (int i = n_; i >= 1; i--) {
        result.coefs_[i - 1] = i * coefs_[i];
    }
    //delete[] array;
    return result;
}

polynom polynom::Integral() const {
    int n_res = n_ + 1;
    //int* array = new int[n_res + 1];
    //*array = { 0 };
    polynom result(n_res);

    for (int i = n_res; i >= 1; i--) {
        result.coefs_[i] = (coefs_[i-1]) / i;
    }
    //delete[] array;
    return result;
}

polynom& polynom::operator<<(const int& x) {
    

    int y = 0;

    for (int i = 0; i <= n_; i++) {        
        y = y + coefs_[i] * (int)pow(x,i);
    }

    //Update max and min values of the object
    maxVal_ = (x > maxVal_) ? x : maxVal_;
    minVal_ = (x < minVal_) ? x : minVal_;

    fmap_.insert(pair<int, int>(x, y));
    return *this;
}

void polynom::print(ostream& os) const {
    //os << "q(x)-";
    printcoefs(os); //////MAKE SURE IT ENDS THE LINE
    polynom der = Derivative();
    os << endl << "Derivative: ";
    der.printcoefs(os);
    polynom integ = Integral();
    os << endl << "Integral: ";

    // Check whether evrything is zero
    if (integ.n_ == 0 && coefs_[0] == 0)
        os << "C" << endl;

    else {
        integ.printcoefs(os);
        os << "+C" << endl;
    }
    if (fmap_.size() != 0) {
        //os << endl;
        plot(os);
    }
    else {
        pass;
    }
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

polynom& polynom::operator=(const polynom& other) {
    if (coefs_ == other.coefs_)
        return *this;

    n_ = other.n_;

    delete[] coefs_;

    coefs_ = new int[n_ + 1];

    for (int i = 0; i <= n_; i++) {
        coefs_[i] = other.coefs_[i];
    }
    return *this;
}
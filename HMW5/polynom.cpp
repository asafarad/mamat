/*

  File: polynom.cpp

  Abstract:

    Polynom handling implementation

*/


#include "polynom.h"


/*
  Function Name	:	polynom
  Description	:	Constructor of polynom object.
  Parameters	:	n	- order of the polynom as an integer.
                    arr - array contains the polynom's coefficients.
  Return Value	:	Instantiation of polynom class.
  */
polynom::polynom(int n, int arr[]) :
    func(),
    n_(n)
{
    coefs_ = new int[n + 1]; //alocate array of n+1 coeffs(0,...,n)
    for (int i = 0; i <= n; i++)
        coefs_[i] = arr[i];
}


/*
  Function Name	:	polynom
  Description	:	Copy constructor of polynom object.
  Parameters	:	p	- polynom object to copy.
  Return Value	:	Instantiation of polynom class.
  */
polynom::polynom(const polynom& p) :
    func(),
    n_(p.n_)
{
    coefs_ = new int[n_ + 1]; //alocate array of n+1 coeffs(0,...,n)
    for (int i = 0; i <= n_; i++)
        coefs_[i] = p.coefs_[i];
}


/*
  Function Name	:	polynom
  Description	:	Default constructor of polynom object.
  Parameters	:	n	- order of the polynom as an integer.
  Return Value	:	Instantiation of polynom class.
  */
polynom::polynom(int n = 0) :
    func(),
    n_(n)
{
    coefs_ = new int[n + 1]; //alocate array of n+1 coeffs(0,...,n)
    //create all zero polynom by default
    for (int i = 0; i <= n; i++)
        coefs_[i] = 0;
}


/*
  Function Name	:	~polynom
  Description	:   Destructor of polynom object.
  Parameters	:	None.
  Return Value	:	None.
  */
polynom::~polynom() {
    //delete the allocated coefficients of polynom
    delete [] coefs_;
}

/*
  Function Name	:	operator+
  Description	:   Overload the operator + , calculate the sum of two polynoms.
  Parameters	:	p2  - polynom to calculate the sum with.
  Return Value	:	result  - result polynom of the sum.
  */
polynom polynom::operator+(const polynom& p2) const {
    //temp polynom to keep the higher order polynom
    polynom bigger(n_);
    int n_min, n_max;
    
    if (this->n_ < p2.n_) {
        //p2 order is higher
        n_min = this->n_;
        n_max = p2.n_;
        bigger = p2; //call assign operator
    }
    else {
        //this order is higher
        n_min = p2.n_;
        n_max = this->n_;
        bigger = *this; //call assign operator
    }

    //We shall declare our result as the polynom with 
    //the higher degree, and then add the coeffs of
    //the lower degree polynom
    for (int i = 0; i <= n_min; i++) {
        bigger.coefs_[i] = coefs_[i] + p2.coefs_[i];
    }
    //find the real degree of result polynom-
    //check the higher nonzero degree
    int n_new = 0;
    for (int i = n_max; i >= 0; i--) {
        if (bigger.coefs_[i] != 0) {
            n_new = i;
            break;
        }
    }
    //construct the result polynom
    polynom result(n_new, bigger.coefs_);
    return result;
}


/*
  Function Name	:	operator-
  Description	:   Overload the operator - , calculate the subtraction of two polynoms.
  Parameters	:	p2  - polynom to subtract with.
  Return Value	:	result  - result polynom of the subtraction.
  */
polynom polynom::operator-(const polynom& p2) const {
    //create the negative of polynom to subtract
    polynom p2_neg(p2);
    for (int i = 0; i <= p2_neg.n_; i++) {
        p2_neg.coefs_[i] = (-1) * p2.coefs_[i];
    }
    //calculate: this + (-p2)
    return (*this + p2_neg);
}


/*
  Function Name	:	operator*
  Description	:   Overload the operator * , calculate the multiplication of two polynoms.
  Parameters	:	p2  - polynom to multiply with.
  Return Value	:	result  - result polynom of the multiplication.
  */
polynom polynom::operator*(const polynom& p2) const {
    //result degree is sum of multipliers degree
    int n_res = n_ + p2.n_;
 
    polynom tmpRes(n_res);
    //calculate the coeffs of multiplication
    for (int i = 0; i <= n_; i++) {
        for (int j = 0; j <= p2.n_; j++) {
            tmpRes.coefs_[i + j] = tmpRes.coefs_[i + j]
                + coefs_[i] * p2.coefs_[j];
        }
    }

    //find the real degree of result polynom-
    //check the higher nonzero degree
    int n_new = 0;
    for (int i = n_res; i >= 0; i--) {
        if (tmpRes.coefs_[i] != 0) {
            n_new = i;
            break;
        }
    }
    //construct the result polynom
    polynom result(n_new, tmpRes.coefs_);
    return result;

}


/*
  Function Name	:	operator=
  Description	:   Overload the assignment operator.
  Parameters	:	other  - polynom to assign to.
  Return Value	:	this polynom.
  */
polynom& polynom::operator=(const polynom& other) {
    //in case of self assignment- don't do anything
    if (coefs_ == other.coefs_)
        return *this;

    n_ = other.n_;
    //destroy the old coefficients
    delete [] coefs_;
    //allocate new coeffs
    coefs_ = new int[n_ + 1];
    //assign the other coeffs
    for (int i = 0; i <= n_; i++) {
        coefs_[i] = other.coefs_[i];
    }
    return *this;
}


/*
  Function Name	:	Derivative
  Description	:   Calculate the derivative of polynom- a1+a2*2x+...+an*nx^(n-1).
  Parameters	:	None.
  Return Value	:	result  - result polynom of the derivative.
  */
polynom polynom::Derivative() const {
    //if the polynom is constant- derivative is zero polynom
    if (n_ == 0) {
        int array[1] = { 0 };
        polynom result(n_, array);
        return result;
    }
    //initial polynom with degree n-1
    int n_res = n_ - 1;
    polynom result(n_res);
    //calc coeffs of derivative: a_(n-1)=n*a_n
    for (int i = n_; i >= 1; i--) {
        result.coefs_[i - 1] = i * coefs_[i];
    }
    return result;
}


/*
  Function Name	:	Integral
  Description	:   Calculate the indefinite integral of polynom- C+a0*x+a1/2*x^2+...+an/(n+1)*x^(n+1).
  Parameters	:	None.
  Return Value	:	result  - result polynom of the integral.
  */
polynom polynom::Integral() const {
    //initial polynom with degree n+1
    int n_res = n_ + 1;
    polynom result(n_res);
    //calc coeffs of derivative: a_n=a_(n-1)/n
    for (int i = n_res; i >= 1; i--) {
        result.coefs_[i] = (coefs_[i-1]) / i;
    }
    return result;
}


/*
  Function Name	:	operator<<
  Description	:   Overload the input operator << , get point, calculate the image and insert it to the func map.
  Parameters	:	x  - point to calc image and add to map.
  Return Value	:	this polynom.
  */
polynom& polynom::operator<<(const int& x) {
    int y = 0;
    //calculate image: y=f(x)=a0+a1*x+...+an*x^n
    for (int i = 0; i <= n_; i++) {        
        y = y + coefs_[i] * (int)pow(x,i);
    }

    //Update max and min values of the object
    maxVal_ = (x > maxVal_) ? x : maxVal_;
    minVal_ = (x < minVal_) ? x : minVal_;
    //insert to point function map
    fmap_.insert(pair<int, int>(x, y));
    return *this;
}


/*
  Function Name	:	print
  Description	:   Print the polynom by demands- print print polynom itself,
                    then its derivative, then integral, then plot it if it has points
  Parameters	:	os  - output ostream object to print to.
  Return Value	:	None.
  */
void polynom::print(ostream& os) const {
    //print polynom coeffs
    printcoefs(os);
    //calc its derivative
    polynom der = Derivative();
    //print the derivative coeffs
    os << endl << "Derivative: ";
    //calc its integral
    der.printcoefs(os);
    //print the integral coeffs
    polynom integ = Integral();
    os << endl << "Integral: ";

    //Check whether integral is allzero polynom
    if (integ.n_ == 0 && integ.coefs_[0] == 0)
        //if its zero polynom- print only integral const C
        os << "C" << endl;

    else {
        //print integral coeffs
        integ.printcoefs(os);
        //print anyway the integral const C
        os << "+C" << endl;
    }
    //print plot if its map isn't empty
    if (fmap_.size() != 0) {
        //os << endl;
        plot(os);
    }
    //if map is empty- pass
    else {
        pass;
    }
}


/*
  Function Name	:	printcoefs
  Description	:   Print polynom coeffs in its template to output- a0+a1*x+...+an*x^n
  Parameters	:	os  - output ostream object to print to.
  Return Value	:	None.
  */
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


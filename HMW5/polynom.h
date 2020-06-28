#ifndef _POLY_F
#define _POLY_F

#include "func.h"

using namespace std;


class polynom : public func {
 public:
  //Constructor
  polynom(int n, int arr[]);
  //Copy Constructor
  polynom(const polynom& p);
  //Destructor
  ~polynom();

  //Operators
  virtual polynom operator+(const polynom&) const;
  virtual polynom operator-(const polynom&) const;
  virtual polynom operator*(const polynom&) const;
  
  //Derivative
  virtual polynom Derivative() const;
  //Integral
  virtual polynom Integral() const;
  //Print to map
  virtual polynom& operator<<(const int& x);

  //Print Coeffs
  void printcoefs(ostream&) const ;

  
 
  


  protected:

  int n_; //order of the polynom
  int* coefs_; //coefficients 

  polynom& decrease_degree(polynom&);
};



#endif
 

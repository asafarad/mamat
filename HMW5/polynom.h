/*

  File: polynom.h

  Abstract:

    Polynom handling interface

*/


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
  //Constructor without coefs- default 0
  polynom(int n);
  //Destructor
  ~polynom();

  //Operators
  virtual polynom operator+(const polynom&) const;
  virtual polynom operator-(const polynom&) const;
  virtual polynom operator*(const polynom&) const;
  virtual polynom& operator=(const polynom& other);
  
  //Derivative
  virtual polynom Derivative() const;
  //Integral
  virtual polynom Integral() const;
  //Print to map
  virtual polynom& operator<<(const int& x);

  //Print polynom according to the demands
  void print(ostream& os) const;

  //Print polynom as coeffs: a0+a1*x+...+an*x^n
  void printcoefs(ostream&) const ;


  protected:

  int n_; //order of the polynom
  int* coefs_; //coefficients 

  //polynom& decrease_degree(polynom&);
};



#endif
 

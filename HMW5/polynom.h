#ifndef _POLY_F
#define _POLY_F

#include "func.h"

using namespace std;


class polynom : public func {
 public:
 
  polynom(int n, int arr[]);
  void printcoefs(ostream&)  const ;

  protected:

  int n_; //order of the polynom
  int* coefs_; //coefficients 
};



#endif
 

#ifndef blah_F
#define blah_F
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

#define pass (void)0;
#define Inf 999999
#define minusInf -999999


/// CHECK LATER WHICH STD's we can get rid of

using namespace std;

class func {

 protected:
   
  
  int maxVal_; //maximum of all inputs
  int minVal_; //minimum of all inputs
  map<int,int> fmap_; //holds inputs and corresponding outputs
  void plot(ostream& os) const ; //plot fmap_

  public:

      //Constructor:
      func();

      //Copy Constructor:
      func(const func& function);

      //Destructor:
      virtual ~func();

      // CHECK if need to implement or pure virtual!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      virtual func& operator<<(const int& x) = 0;
      friend ostream& operator<<(ostream& os, const func& f);
      virtual void print(ostream& os) const = 0;
      friend class compfunc;

      // need to declare pure vritual operators???????????????????????????????????????????????????
      //virtual func operator+(const func&) = 0;
      //virtual func operator-(const func&) = 0;
      //virtual func operator*(const func&) = 0;
      //virtual func Derivative() = 0;
      //virtual func Integral() = 0;


};

#endif

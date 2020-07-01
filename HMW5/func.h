#ifndef blah_F
#define blah_F
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

#define pass (void)0;
#define Inf 999999
#define minusInf -999999

using namespace std;

class func {

 protected:
   
  //We need to define some variables that will
  //help us plot y=f(x): maxVal_ and minVal_ of x
  //in order to know where to begin plotting the x
  //axis and where to end it:
  int maxVal_; 
  int minVal_; 

  map<int,int> fmap_; //holds pairs of (x,y)
  void plot(ostream& os) const ; //plots fmap_

  public:

      /**
      * @ brief The constructor of func (without parameters),
      * which only initializes maxVal and minVal
      */
      func();

      /**
      * @ brief The destructor of func, which
      * doesn't do anything
      */
      //Destructor:
      virtual ~func();

      /**
      * @ brief A copy constructor of func,
      * which sets maxVal and minVal to those
      * of the given function
      */
      func(const func& function);


      // CHECK if need to implement or pure virtual!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

      /**
      * @ brief Insert input into the function
      */

      virtual func& operator<<(const int& x) = 0;

      /**
      * @ brief Print operator, prints the function
      f to the standard output
      */
      friend ostream& operator<<(ostream& os, const func& f);

      /**
      * @ brief Virtual function which assists us
      * with printing the function in a way
      * suitable for the specific subclass
      */
      virtual void print(ostream& os) const = 0;

      /**
      * @ brief The class "compfunc" which represents
      * implementation of one function upon another
      * is defined as a friend class
      */
      friend class compfunc;

      // need to declare pure vritual operators???????????????????????????????????????????????????
      //virtual func operator+(const func&) = 0;
      //virtual func operator-(const func&) = 0;
      //virtual func operator*(const func&) = 0;
      //virtual func Derivative() = 0;
      //virtual func Integral() = 0;


};

#endif

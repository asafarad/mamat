/*

  File: func.cpp

  Abstract:

    Func handling interface

*/

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

      /*
        Function Name	: func
        Description	:	The constructor of func (without parameters),
                          which only initializes maxVal and minVal
        Parameters	:	None.
        Return Value	: Instantiation of func class.
      */
      func();


      /*
        Function Name	: ~func
        Description	:   Destructor of func object.
        Parameters	:	None.
        Return Value	: None.
      */
      virtual ~func();

      /*
      Function Name	:	func
      Description	:	Copy constructor of func object
                          which assigns maxVal and minVal
                          according to the copied func
      Parameters	:	function - func object to copy.
      Return Value	:	Instantiation of func class.
      */
      func(const func& function);

      /*
      Function Name	:	plot
      Description	:   plots f(x): creates an axis for
                          x and for y and adds a star (*) wherever
                          f(x) = y
      Parameters	:	os  - output ostream object to print to.
      Return Value	:	None.
      */

      virtual func& operator<<(const int& x) = 0;

      /*
      Function Name	:	operator<<
      Description	:   The input operator << which prints the
                        function to the standard output
      Parameters	:	os  - reference to output ostream object
                        f - reference to a func object
      Return Value	:	os
      */

      friend ostream& operator<<(ostream& os, const func& f);

      /**
      * Virtual function which assists us
      * with printing the function in a way
      * suitable for the specific subclass
      */
      virtual void print(ostream& os) const = 0;

      /**
      * The class "compfunc" which represents
      * implementation of one function upon another
      * is defined as a friend class
      */
      friend class compfunc;


};

#endif

#ifndef _F
#define _F
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>



using std::map;
using std::ostream;
using std::vector;
using std::sort;
using std::reverse;

class func {

 



 protected:
   
  
  int maxVal_; //maximum of all inputs
  int minVal_; //minimum of all inputs
  map<int,int> fmap_; //holds inputs and corresponding outputs
  void plot(ostream& os) const ; //plot fmap_

  public:

      //Constructor:
      func();

      // CHECK if need to implement or pure virtual!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      virtual func& operator<<(const int& x) =0;
      friend virtual ostream& operator<<(ostream&, const func&) = 0;
};



#endif

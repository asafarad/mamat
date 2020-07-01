#include "func.h"

/**
* @ brief The constructor of func (without parameters),
* which only initializes maxVal and minVal
*/

func::func() :
    maxVal_(minusInf),
    minVal_(Inf) {
    }

/**
* @ brief The destructor of func, which
* doesn't do anything
*/

func::~func() {
    pass;
}

/**
* @ brief A copy constructor of func,
* which sets maxVal and minVal to those
* of the given function
*/

func::func(const func& function): 
    maxVal_(function.maxVal_),
    minVal_(function.minVal_) {
}

/**
* @ brief plots f(x): creates an axis for
* X and for Y and adds a star (*) wherever
* f(x) = y
*/

void func::plot(ostream& os) const {

  vector<int> sortImage;
    

  //Firstly, we shall insert into the vector sortImage
  //All of the dots in the map, and then sort them
  sortImage.clear();
  for ( auto it : fmap_){
      sortImage.push_back(it.second); 
  }

  sort(sortImage.begin(), sortImage.end());
  reverse(sortImage.begin(), sortImage.end());
  
  for ( auto it_im = sortImage.begin();
       it_im != sortImage.end(); ++it_im) {
    if(it_im!=sortImage.begin() && *it_im==*(it_im-1)){ //remove repeated
      it_im = sortImage.erase(it_im)-1;
      
    }
  }
 
  //Secondly, we shall iterate over the vector
  //and "plot" as described on the brief each pair

  for (auto it_im = sortImage.begin();
       it_im != sortImage.end(); ++it_im) {
    int x_anchor=minVal_;
    if(*it_im<-9) 
      os <<*it_im;
    else
      if((*it_im<0) || (*it_im>9)) 
	os<<" "<<*it_im;
      else 
	os<<"  "<<*it_im;
    
    for (auto it_dom : fmap_) {
      if(it_dom.second == *it_im){
	int x=it_dom.first;
	int spaces= x-x_anchor;
	int i=0;
	while(i<spaces){
	  os<<"   ";
	  i++;
	}
	os<<"*  ";
	x_anchor=x+1;
      }

    }

    os<< endl ;
    if((it_im+1)!=sortImage.end()){ //print empty lines
      int lines=*it_im-*(it_im+1)-1;
      int i=1;
      
      while(i<lines+1){
	if(*it_im-i<-9) 
	  os <<*it_im-i;
	else 
	  if( (*it_im-i<0) || (*it_im-i>9) )
	    os<<" "<<*it_im-i;
	  else 
	    os<<"  "<<*it_im-i;
	cout<<endl;
	i++;

      }
    }

  }//for sortImage

  //print x axis
  cout<< " ";
  for (auto i=minVal_; i<maxVal_+1;i++){
    if(i<0) os<<" "<<i;
    else os<<"  "<<i;
  }
  os<<endl;
}

/**
* @ brief Print operator, prints the function
f to the standard output
*/


ostream& operator<<(ostream& os, const func& f) {
    f.print(os);
    return os;

}
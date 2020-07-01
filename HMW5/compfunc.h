#pragma once
#ifndef _COMP_F
#define _COMP_F
#include "func.h"

/**
* @ brief A class which represent a complex function and 
* holds pointers to an inner function and an outer function
*/

class compfunc : public func {
	
	public:
		compfunc(func& q, func& p);
		compfunc& operator<<(const int& x);
		void print(ostream& os) const;


	protected:
		func* inner;
		func* outer;

};






#endif

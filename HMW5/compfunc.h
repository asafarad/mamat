/*

  File: func.cpp

  Abstract:

	Compfunc handling interface

*/

#pragma once
#ifndef _COMP_F
#define _COMP_F
#include "func.h"


//A class which represents a complex function and holds 
//pointers to an inner function and an outer function
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

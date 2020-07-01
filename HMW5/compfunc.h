#pragma once
#ifndef _COMP_F
#define _COMP_F
#include "func.h"

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

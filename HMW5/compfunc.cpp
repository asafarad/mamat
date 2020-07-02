/*

  File: func.cpp

  Abstract:

	Complex function handling implementation

*/
#include "compfunc.h"

/*
  Function Name	:	compfunc
  Description	:	The constructor of a complex function
  Parameters	:	q - out function
					p - innter function
  Return Value	:	Instantiation of compufunc class.
  */

compfunc::compfunc(func& q, func& p): inner(&p), outer(&q) {

}
compfunc& compfunc::operator<<(const int& x) {

	int temp_res, y;
	*inner << x;
	temp_res = inner->fmap_[x];
	*outer << temp_res;
	y = outer->fmap_[temp_res];
	inner->fmap_.clear();
	inner->minVal_ = Inf;
	inner->maxVal_ = minusInf;
	outer->fmap_.clear();
	outer->minVal_ = Inf;
	outer->maxVal_ = minusInf;

	maxVal_ = (x > maxVal_) ? x : maxVal_;
	minVal_ = (x < minVal_) ? x : minVal_;

	fmap_.insert(pair<int, int>(x, y));
	return *this;

}

/*
  Function Name	:	plot
  Description	:   Plots the complex function - prints the exisiting
					pairs of (x,y) from the map
  Parameters	:	os  - output ostream object to print to.
  Return Value	:	None.
  */

void compfunc::print(ostream& os) const {
	os << endl;
	if (fmap_.size() != 0) {
		plot(os);
	}
}
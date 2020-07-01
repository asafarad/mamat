#include "compfunc.h"


/**
* @ brief The constructor of a complex function
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

/**
* @ brief Plot the complex function
*/

void compfunc::print(ostream& os) const {
	if (fmap_.size() != 0) {
		os << endl;
		plot(os);
	}
	else {
		pass;
	}
}
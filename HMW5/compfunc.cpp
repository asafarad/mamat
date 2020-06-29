#include "compfunc.h"



compfunc::compfunc(func& q, func& p): inner(&p), outer(&q) {

}
compfunc& compfunc::operator<<(const int& x) {

	int temp_res, y;
	*inner << x;
	temp_res = inner->fmap_[x];
	*outer << temp_res;
	y = outer->fmap_[temp_res];

	maxVal_ = (y > maxVal_) ? y : maxVal_;
	minVal_ = (y < minVal_) ? y : minVal_;

	fmap_.insert(pair<int, int>(x, y));
	return *this;

}
void compfunc::print(ostream& os) const {
	os << "q(p)(x)=";
	plot(os);
}
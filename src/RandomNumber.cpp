#include "RandomNumber.h"

#include <cmath>

using namespace std;

RandomNumber::RandomNumber(int nRan)
	:idum(nRan)
{
}

RandomNumber::~RandomNumber(){}

double RandomNumber::ran3()
{
	//This routine returns an randomic number 0 <= r <= 1
	const double mbig = 1000000000;
	const double mseed = 161803398;
	const double fac = 1.E-9;
	int mz = 0;

	if (idum < 0 || iff == 0) {
		iff = 1;
		mj = (int)mseed - abs(idum);
		mj = mj % (int)mbig;
		ma[55] = mj;
		mk = 1;
		for (int i = 1; i <= 54; i++) {
			int ii = ((21 * i) % 55);
			ma[ii] = mk;
			mk = mj - mk;
			if (mk < mz)
				mk = mk + (int)mbig;

			mj = ma[ii];
		}
		for (int k = 1; k <= 4; k++) {
			for (int i = 1; i <= 55; i++) {
				ma[i] = ma[i] - ma[1 + ((i + 30) % 55)];

				if (ma[i] < mz)
					ma[i] = ma[i] + (int)mbig;
			}
		}
		inext = 0;
		inextp = 31;
		idum = 1;
	}

	inext = inext + 1;
	if (inext == 56)
		inext = 1;

	inextp = inextp + 1;
	if (inextp == 56)
		inextp = 1;

	mj = ma[inext] - ma[inextp];
	if (mj < mz)
		mj = mj + (int)mbig;

	ma[inext] = mj;

	double ran3_ = mj*fac;

	return (ran3_);
}

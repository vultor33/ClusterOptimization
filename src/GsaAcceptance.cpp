#include "GsaAcceptance.h"

#include <cmath>

using namespace std;

GsaAcceptance::GsaAcceptance(){}

GsaAcceptance::~GsaAcceptance(){}

void GsaAcceptance::initialize(
	double qA_in,
	double qT_in,
	double To_in,
	double D_in,
	RandomNumber * random_in_
	)
{
	random_ = random_in_;
	qA = qA_in;
	qT = qT_in;
	To = To_in;
	D = D_in;

	qA1 = qA - 1.0e0;
	OneqA1 = 1.0e0 / qA1;

	qT1 = qT - 1.0e0;
	Tqt = To * (pow(2.0e0, qT1) - 1.0e0);// fredmudar - esse 2

}

bool GsaAcceptance::acceptNewIndividual()
{
	DeltaE = func_t - func_0;

	if (DeltaE < 0.0e0)
	{
		return true;
	}
	else
	{
		PqA = 1.0e0 /
			pow((1.0e0 + qA1 * (DeltaE / T)), OneqA1);
		rand01 = random_->generateRandomNumber(0.0e0,1.0e0);
		if (rand01 < PqA)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

void GsaAcceptance::temperatureUpdate(double Time)
{
	T = Tqt / (pow((1.0e0 + Time), qT1) - 1.0e0); // Temperature T(t)
	if (abs(D) < 1.0e-6)
	{
		Tup = 1.0e0;
	}
	else
	{
		Tup = pow(T, D / (qT - 3.0e0));
	}
}




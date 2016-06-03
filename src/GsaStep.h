#ifndef GSASTEP_H
#define GSASTEP_H

#include <vector>

#include "RandomNumber.h"

class GsaStep
{
public:
	GsaStep();
	~GsaStep();

	void initialize(
		double qT_in,
		double qV_in,
		double To_in,
		double D_in,
		RandomNumber * random_in_
		);

	std::vector<double> makeStep(const std::vector<double> &X_0);

	void temperatureUpdate(double Time);

private:
	const double pi = 3.14159265359E0;
	double T; //temperature
	double Tup;

	double qV1, qT1, D, exp1, exp2, coef, To, Tqt;
	double qV, qT;

    double dGamma(const double &r);

	RandomNumber * random_;

};

#endif

#include "GsaStep.h"

#include <vector>

using namespace std;

#define round_it(d) (static_cast<int>((d)+0.5))

GsaStep::GsaStep(){}

GsaStep::~GsaStep(){}

void GsaStep::initialize(
	double qT_in, 
	double qV_in, 
	double To_in, 
	double D_in,
	RandomNumber * random_in_)
{
	random_ = random_in_;
	qV = qV_in;
	qT = qT_in;
	To = To_in;
	D = D_in; //fredmudar atencao!!!!

	qT1 = qT - 1.0e0;
	Tqt = To * (pow(2.0e0, qT1) - 1.0e0);// fredmudar - esse 2

	qV1 = qV - 1.0e0;
	double tmp = -0.5e0 + 1.0e0 / qV1;
	double gammaDown = dGamma(tmp);
	exp1 = 2.0e0 / (3.0e0 - qV); //fredmudar

	double coef1, gammaUp;
	if (abs(D) < 1.0e-6)
	{
		coef1 = 1.0e0;
		exp2 = -0.5e0 + 1.0e0 / qV1;
	}
	else
	{
		coef1 = pow(qV1 / pi, 0.5e0 * D);
		exp2 = 0.5e0 * D - 0.5e0 + 1.0e0 / qV1;
	}
	gammaUp = dGamma(exp2);
	coef = coef1 * (gammaUp / gammaDown);
}


vector<double> GsaStep::makeStep(const vector<double> &x_0)
{

	int size = x_0.size();
	vector<double> x_new(size);
	double r, s, DeltaX;

	for (int i = 0; i < size; i++) {
		r = random_->ran3();
		s = random_->ran3();

		DeltaX = coef * Tup / pow((1.0e0 + qV1 * r * r / pow(T, exp1)), exp2);

		if (s <= 0.5E0)
			DeltaX = -DeltaX;

		x_new[i] = x_0[i] + DeltaX;
	}

	return x_new;
}


double GsaStep::dGamma(const double &r)
{
	const double p0 = 0.999999999999999990E+00;
	const double p1 = -0.422784335098466784E+00;
	const double p2 = -0.233093736421782878E+00;
	const double p3 = 0.191091101387638410E+00;
	const double p4 = -0.024552490005641278E+00;
	const double p5 = -0.017645244547851414E+00;
	const double p6 = 0.008023273027855346E+00;
	const double p7 = -0.000804329819255744E+00;
	const double p8 = -0.000360837876648255E+00;
	const double p9 = 0.000145596568617526E+00;
	const double p10 = -0.000017545539395205E+00;
	const double p11 = -0.000002591225267689E+00;
	const double p12 = 0.000001337767384067E+00;
	const double p13 = -0.000000199542863674E+00;

	double w, y;
	int n, k;

	n = (int)round_it(r - 2.E0);
	w = r - ((double)n + 2.E0);
	y = ((((((((((((p13 * w + p12) * w + p11) * w + p10) * w + p9) * w + p8) * w + p7) * w + p6) * w + p5) *
		w + p4) * w + p3) * w + p2) * w + p1) * w + p0;

	if (n > 0) {
		w = r - 1;
		for (k = 2; k <= n; k++)
			w = w * (r - (double)k);
	}
	else {
		w = 1.E0;
		for (k = 0; k <= (-n - 1); k++)
			y = y * (r + (double)k);
	}

	return (w / y);
}



void GsaStep::temperatureUpdate(double Time)
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
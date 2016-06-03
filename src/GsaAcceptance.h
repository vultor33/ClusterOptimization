#ifndef GSAACCEPTANCE_H
#define GSAACCEPTANCE_H

#include "RandomNumber.h"

class GsaAcceptance
{
public:
	
	GsaAcceptance();
	~GsaAcceptance();

	void initialize(
		double qA_in,
		double qT_in,
		double To_in,
		double D_in,
		RandomNumber * random_in_
		);

	void temperatureUpdate(double Time);
	bool acceptNewIndividual();

	inline void setFunc0(double func_0_){func_0 = func_0_;}
	inline void setFunct(double func_t_){func_t = func_t_;}

private:
	const double pi = 3.14159265359E0;

	double T; //temperature
	double Tup;

	double qA, qT, To;

	double qA1, qT1, Tqt;
	double OneqA1;
	double PqA;
	double D;

	double DeltaE,rand01;
	double func_0;
	double func_t;

	RandomNumber * random_;

};

#endif

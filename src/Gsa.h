#ifndef Gsa_H
#define Gsa_H

#include <vector>

#include "GsaStep.h"
#include "GsaAcceptance.h"
#include "Fitness.h"
#include "RandomNumber.h"

class Gsa
{
public:
	Gsa(double qA, 
		double qT, 
		double qV, 
		double To,
		double gamma,
		double rca,
		int natm
		);
	~Gsa();

	double initializeGSA(
		std::vector<double> &X_initial, 
		double qA, 
		double qT, 
		double qV, 
		double To, 
		RandomNumber * random_in_,
		int NStopMax_in,
		bool printXyz);

private:
	const double pi = 3.14159265359E0;
	const int fitType = 0;
	int nstopMax;

	std::vector<double> x_0;
	std::vector<double> x_t;
	std::vector<double> x_Min;
	double func_0, func_t, func_Min;

};

#endif


//temperatureUpdate(Time); 2
//accep - setFunc e acceptNewIndividual
//step - makestep
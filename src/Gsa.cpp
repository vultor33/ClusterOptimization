#include "Gsa.h"

#include <vector>
#include <iostream>

#include "RandomNumber.h"
#include "PrintAll.h"
#include "InitializeAtoms.h"
#include "GsaAcceptance.h"
#include "Fitness.h"

using namespace std;

// compress operator - multiplica todas as coordenadas por uma fração para
// aumentar a interacao de todos eles.

Gsa::Gsa(
	double qA, 
	double qT, 
	double qV, 
	double To,
	double gamma,
	double rca,
	int natm
	)
{
	PrintAll printAll_("gbh.log", "gbh-movie.xyz", 1);
	RandomNumber random_;
	random_.setSeed(-75);
	nstopMax = 10000;

	// generation of initial vector
	InitializeAtoms init_(&random_);
	vector<double> x_0 = init_.generateCluster(natm, gamma, rca);
	if (x_0.size() == 0)
	{
		printAll_.printInfinityLoop();
		exit(3);
	}

////////////////////////////////////////////////////
	double D = 1.0e0;
////////////////////////////////////////////////////

	GsaAcceptance gsaAccept_;
	gsaAccept_.initialize(qA, qT, To, D, &random_);
	GsaStep gsaStep_;
	gsaStep_.initialize(qT, qV, To, D, &random_);
	Fitness fit_; // adicionar o log


	double Time = 0.0e0;
	int dimension = x_0.size();
	x_t.resize(dimension);
	x_Min.resize(dimension);
	
	func_0 = fit_.fit(x_0,fitType);
	printAll_.printNewFunction(func_0);

	for (int cycle = 1; cycle < nstopMax; cycle++)
	{
		Time += 1.0e0;

		gsaAccept_.temperatureUpdate(Time);
		gsaStep_.temperatureUpdate(Time);

		x_t = gsaStep_.makeStep(x_0);
		func_t = fit_.fit(x_t, fitType);
		printAll_.printNewFunction(func_t);

		gsaAccept_.setFunc0(func_0);
		gsaAccept_.setFunct(func_t);

		if (gsaAccept_.acceptNewIndividual())
		{
			printAll_.printAccepted();
			func_0 = func_t;
			for (int i = 0; i < dimension; i++)
			{
				x_0[i] = x_t[i];
			}
		}
		
		if (func_t < func_Min)
		{
			func_Min = func_t;
			for (int i = 0; i < dimension; i++)
			{
				x_Min[i] = x_t[i];
				printAll_.printCoordinates(x_t);
			}
		}
	}
}

Gsa::~Gsa(){}






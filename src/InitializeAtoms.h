#ifndef INITIALIZEATOMS_H
#define INITIALIZEATOMS_H

#include <vector>
#include <string>

#include "RandomNumber.h"
#include "PrintAll.h"

class InitializeAtoms
{
public:
	InitializeAtoms::InitializeAtoms(RandomNumber * random_in_, PrintAll * printAll_in_);
	InitializeAtoms::~InitializeAtoms();

	std::vector<double> generateCluster(int Natoms, double gamma_in, double Rca_in);

private:
	double gamma;// parameter
	double Rca;//Rcalfa na tese pag 62
	int natm;

	const double pi4sqr2 = 17.771531752633464988063523960243;
	const double pi = 3.1415926535897932384626433832795e0;
	const double exp3 = 0.33333333333333333333333333333333e0;

	double calcDist(const std::vector<double> &x, int i, int j);
	bool checkSuperposition(const std::vector<double> &x, int iMax);
	double findMinimum(const std::vector<double> &dist, int i);
	double dRand(double dMin, double dMax);

	RandomNumber * random_;
	PrintAll * printAll_;



};

#endif




#include "InitializeAtoms.h"

#include "RandomNumber.h"

using namespace std;

InitializeAtoms::InitializeAtoms(RandomNumber * random_in_, PrintAll * printAll_in_)
	:random_(random_in_),printAll_(printAll_in_)
{}

InitializeAtoms::~InitializeAtoms(){}


vector<double> InitializeAtoms::generateCluster(int natm_in, double gamma_in, double Rca_in)
{
	gamma = gamma_in;
	Rca = Rca_in;
	natm = natm_in;

//  original
//	double rSphere = 2.0e0 * Rca *
//		(0.5e0 + pow((3.0e0 * (double)natm) / pi4sqr2, exp3));
	double rSphere = Rca *
		(0.5e0 + pow((3.0e0 * (double)natm) / pi4sqr2, exp3));



	vector<double> x(3 * natm);
	double r, teta, fi;
	double xi, yi, zi;
	int breakLoop = 0;
	do
	{
		for (int i = 0; i < natm; i++)
		{
			r = dRand(0, rSphere);
			teta = dRand(0, pi);
			fi = dRand(0, 2.0e0 * pi);
			xi = r * sin(teta) * cos(fi);
			yi = r * sin(teta) * sin(fi);
			zi = r * cos(teta);
	
			x[i] = xi;
			x[i + natm] = yi;
			x[i + 2 * natm] = zi;
		}
		breakLoop++;
		if (breakLoop > 1000000)
		{
			vector<double> xdummy;
			return xdummy;
		}
	} while (checkSuperposition(x, natm));

	printAll_->printCoordinates(x);

	return x;

}

double InitializeAtoms::dRand(double min, double max)
{
	double random = random_->ran3();
	return min + (random * (max - min));
}

double InitializeAtoms::calcDist(const vector<double> &x, int i, int j)
{
	return sqrt(
		(x[i] - x[j])*(x[i] - x[j]) +
		(x[i + natm] - x[j + natm])*(x[i + natm] - x[j + natm]) +
		(x[i + 2 * natm] - x[j + 2 * natm])*(x[i + 2 * natm] - x[j + 2 * natm])
		);
}

bool InitializeAtoms::checkSuperposition(const std::vector<double>& x, int iMax)
{
	double rMin;
	double lowerLimit = (1.0e0 - gamma) * Rca;
	double upperLimit = (1.0e0 + gamma) * Rca;
	for (int i = 0; i < iMax; i++)
	{
		rMin = findMinimum(x, i);
		if ((rMin < lowerLimit) ||
			(rMin > upperLimit))
		{
			return true;
		}
	}

	return false;
}

double InitializeAtoms::findMinimum(const std::vector<double>& x, int i)
{
	//distancia ao vizinho mais proximo
	double dist;
	double distmin = 1.0e3;
	for (int j = 0; j < natm; j++)
	{
		if (i != j)
		{
			dist = calcDist(x, i, j);
			if (dist < distmin)
			{
				distmin = dist;
			}
		}
	}
	return distmin;
}

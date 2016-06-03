#include "Annealing.h"

#include <vector>
#include <fstream>
#include <iomanip>

#include "Coordstructs.h"
#include "AuxMath.h"

using namespace std;

Annealing::Annealing(){}

Annealing::~Annealing(){}

vector<double> Annealing::basinHoping()
{
	AuxMath auxMath_;
	vector<double> x0;
	double f0 = optimize(x0);

#ifdef _DEBUG
	printAllAtoms("initialComplexBeforeAnnealing.xyz", x0);
	ofstream annealingInfo_("AnnealingInfo.log");
#endif

	//Variable temperature - always 50/100
	double cTemp = f0 / saInitialTemperature;
	int dices = 0;
	int accep = 0;
	vector<double> xMin = x0;
	double fMin = f0;
	vector<double> x;
	double f;
	double prob;
	double rand;

	for (int i = 0; i < saMaxIterations; i++)
	{
		x = x0;
		perturbOperations(x);
		saveIndividual(x);
		f = optimize(x);
		if (f < f0)
		{
			x0 = x;
			f0 = f;
		}
		else
		{
			dices++;
			prob = exp((f0 - f) / cTemp);
			rand = auxMath_.fRand(0, 1.0e0);
			if (prob > rand)
			{
				x0 = x;
				f0 = f;
				accep++;
			}
			if (((double)accep / (double)dices) > saAcceptance)
				cTemp -= saTemperatureUpdate * cTemp;
			else
				cTemp += saTemperatureUpdate * cTemp;
		}
		if (f < fMin)
		{
			xMin = x;
			fMin = f;
			finalIteration = i;
		}

#ifdef _DEBUG
		annealingInfo_ << "i:  " << i << "  fMin:  "
			<< setprecision(16)
			<< fMin
			<< "  cTemp:  " << cTemp << endl;
#endif
	}

#ifdef _DEBUG
	printAllAtoms("complexAfterAnnealing.xyz", xMin);
	annealingInfo_.close();
#endif

	return xMin;
}

double Annealing::optimize(vector<double>& x)
{
	return 0.0;
}

void Annealing::perturbOperations(vector<double>& x)
{
}

void Annealing::saveIndividual(vector<double>& x)
{
	allIndividuals.push_back(x);
}


void Annealing::printAllAtoms(string xyzName, vector<double> & x)
{
	// x1 x2 x3 ... y1 y2 y3 ... z1 z2 z3
	size_t size = x.size() / 3;
	ofstream xyzAll(xyzName.c_str());
	xyzAll << size << endl
		<< "useful title" << endl;
	for (size_t i = 0; i < size; i++)
		xyzAll << " H   "
			<< x[i] << "  "
			<< x[i + size] << "  "
			<< x[i + 2 * size] << endl;
}

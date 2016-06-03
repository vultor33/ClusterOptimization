#include "Annealing.h"

#include <vector>
#include <fstream>
#include <iomanip>

#include "Coordstructs.h"
#include "AuxMath.h"
#include "LocalOptimization.h"

using namespace std;

Annealing::Annealing(){}

Annealing::~Annealing(){}

vector<double> Annealing::basinHoping()
{
	finalIteration = 0;
	AuxMath auxMath_;
	vector<double> x0;
	double f0 = optimize(x0);

#ifdef _DEBUG
	printAllAtoms("initialComplexBeforeAnnealing.xyz", x0);
	ofstream annealingInfo_("AnnealingInfo.log");
#endif

	//Variable temperature - always 50/100
	double temperature = f0 / saInitialTemperature;
	double fMin = f0;
	vector<double> xMin = x0;
	vector<double> x;
	double f;
	double prob;
	double rand;
	// update temperature data
	dices = 0;
	accep = 0;

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
			prob = exp((f0 - f) / temperature);
			rand = auxMath_.fRand(0, 1.0e0);
			if (prob > rand)
			{
				x0 = x;
				f0 = f;
				accep++;
			}
			temperature = updateTemperature(temperature);
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
			<< "  temperature:  " << temperature << endl;
#endif
	}

#ifdef _DEBUG
	printAllAtoms("complexAfterAnnealing.xyz", xMin);
	annealingInfo_.close();
#endif

	return xMin;
}

double Annealing::updateTemperature(double temperature)
{
	if (((double)accep / (double)dices) > saAcceptance)
		return -saTemperatureUpdate * temperature;
	else
		return saTemperatureUpdate * temperature;
}

double Annealing::optimize(vector<double>& x)
{
	LocalOptimization local_;	
	return local_.optimize(x, 0);
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


#ifndef ANNEALING_H
#define ANNEALING_H

#include <vector>
#include <fstream>

#include "Coordstructs.h"

class Annealing
{
public:
	Annealing();
	~Annealing();

	std::vector<double> basinHoping();


private:
	//data
	double saAcceptance;
	double saInitialTemperature;
	double saMaxIterations;
	double saTemperatureUpdate;
	double finalIteration;
	std::vector< std::vector<double> > allIndividuals;

	double optimize(std::vector<double> & x);

	void perturbOperations(std::vector<double> & x);

	void saveIndividual(std::vector<double> & x);

	void printAllAtoms(std::string xyzName, std::vector<double> & x);

};


#endif
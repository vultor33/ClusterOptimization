#include "LocalOptimization.h"

#include <dlib/optimization.h>
#include <iostream>

#include "FunctionDlib.h"
#include "DerivativeDlib.h"

using namespace std;
using namespace dlib;

LocalOptimization::LocalOptimization() {}

LocalOptimization::~LocalOptimization() {}

double LocalOptimization::optimize(std::vector<double> &x, int fitType)
{
	int size = x.size();
	column_vector starting_point(size);
	for (int i = 0; i < size; i++)
		starting_point(i) = x[i];

	double fMin = find_min(bfgs_search_strategy(),
		objective_delta_stop_strategy(1e-6),
		FunctionDlib(size, fitType),
		DerivativeDlib(size, fitType),
		starting_point,
		-1.0e99);

	for (int i = 0; i < size; i++)
		x[i] = starting_point(i);

	return fMin;
}

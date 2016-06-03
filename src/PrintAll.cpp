#include "PrintAll.h"

#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

PrintAll::PrintAll(string logname, string xyzname, int debuglevel)
{
	remove(logname.c_str());
	remove(xyzname.c_str());
	gbhlog_.open(logname.c_str());
	xyz_.open(xyzname.c_str());

	switch (debuglevel)
	{
	case 0:
		printXyz = false;
		debug = false;
		break;

	case 1:
		printXyz = true;
		debug = true;
		break;

	default:
		break;

	}
}

PrintAll::~PrintAll()
{
	gbhlog_.close();
	xyz_.close();
}

void PrintAll::printCoordinates(vector<double> &x)
{
	if (!printXyz)
		return;

	int natm = x.size() / 3;
	xyz_ << natm << endl << "titulo" << endl;
	for (int i = 0; i < natm; i++)
	{
		xyz_ << " H   " << x[i] << "   "
			<< x[i + natm] << "    "
			<< x[i + 2 * natm] << endl;
	}
}

void PrintAll::printInfinityLoop()
{
	if (debug)
	{
		gbhlog_ << endl << "coudln't generate initial cluster - infinity loop" << endl;
	}
}

void PrintAll::printNewFunction(double func_t)
{
	gbhlog_ << "New fitness:  " << func_t << endl;
}

void PrintAll::printAccepted()
{
	gbhlog_ << "point accepted" << endl;
}







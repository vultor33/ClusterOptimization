#ifndef PRINTALL_H
#define PRINTALL_H

#include <vector>
#include <string>
#include <fstream>

class PrintAll
{
public:
	PrintAll::PrintAll(
		std::string logname = "gbh.log",
		std::string xyzname = "gbh-movie.xyz",
		int debuglevel = 1
		);
	PrintAll::~PrintAll();

	void printCoordinates(std::vector<double> &x);
	void printInfinityLoop();
	void printNewFunction(double func_t);
	void printAccepted();

private:
	bool printXyz;
	bool debug;


	std::ofstream gbhlog_;
	std::ofstream xyz_;


};

#endif




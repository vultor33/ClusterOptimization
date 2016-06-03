#ifndef RANDOMNUMBER_H
#define RANDOMNUMBER_H

class RandomNumber
{
public:
	RandomNumber();

	~RandomNumber();

	void setSeed(int seed);

	double generateRandomNumber(double fMin, double fMax);

	int generateRandomNumber(int fMin, int fMax);

private:
	double ran3();

	double randcpp(double min, double max);

	int randcpp(int min, int max);

	int idum;

	int iff, mj, mk, inext, inextp;
	int ma[56];

};

#endif

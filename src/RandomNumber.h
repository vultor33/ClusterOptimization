#ifndef RANDOMNUMBER_H
#define RANDOMNUMBER_H

class RandomNumber
{
public:
	RandomNumber();

	~RandomNumber();

	void setSeed(int seed);

	double ran3();

	double randcpp(double fMin, double fMax);

	int randcpp(int fMin, int fMax);

private:
	int idum;

	int iff, mj, mk, inext, inextp;
	int ma[56];

};

#endif

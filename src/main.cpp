#include <iostream>

#include "RandomNumber.h"
#include "PrintAll.h"
#include "InitializeAtoms.h"
#include "Gsa.h"

using namespace std;

int main()
{
	Gsa gsa(1.0001, 1.0001, 1.0001,100,0.4,0.7,5);


	cout << "ola mundo " << endl;
	return 0;
}


/*
TESTANDO NUMEROS IMAGINARIOS

RandomNumber random_(-43);
for (int i = 0; i < 100; i++)
{
	cout << "random:  " << random_.ran3() << endl;
}
double aux = 0.0e0;
double aux2 = 0.0e0;
for (int i = 0; i < 10000000; i++)
{
aux += init_.dRand(1, 10);
aux2 += random_.ran3();
}
cout << aux / 10000000 << endl;
cout << aux2 / 10000000 << endl;



*/

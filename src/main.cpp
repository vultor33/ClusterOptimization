#include <iostream>
#include <vector>

#include "RandomNumber.h"
#include "PrintAll.h"
#include "InitializeAtoms.h"
#include "Gsa.h"
#include "Derivative.h"
#include "Fitness.h"
#include "RandomNumber.h"

using namespace std;

/*
PROJETO

- Crio um sistema com 10 clusters e 20 condiçoes inicias pra cada.
  (5 - 15)

- Avalio quantas interacoes o Basin Hoping puro sem nada demora
  para encontrar o minimo global dessas estruturas.

- Qualquer operador adicionado no modelo precisa encontrar o
  resultado com menos interacoes do que o basin hoping tradicional.



o basin hoping puro, seco, sem nada.




*/


int main()
{
	//Gsa gsa(1.0001, 1.0001, 1.0001,100,0.4,0.7,5);

	cin.get();
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

TESTE DA DERIVADA ANALITICA

vector<double> x(9);
x[0] = 0;
x[1] = 1;
x[2] = 2;
x[3] = 0;
x[4] = 0;
x[5] = 0;
x[6] = 0;
x[7] = 1;
x[8] = 0;
Fitness fit_;
double f = fit_.fit(x, 0);
double h, f1;
vector<double> xmod;
vector<double> nDerivative(9);
h = 1.0e-6;
for (int i = 0; i < 9; i++)
{
xmod = x;
xmod[i] += h;
nDerivative[i] = (fit_.fit(xmod, 0) - f) / h;
}
Derivative df_;
vector<double> analyDer = df_.Dfit(x, 0);

for (int i = 0; i < 9; i++)
cout << "nder:  " << nDerivative[i] << "  analytical:  " << analyDer[i] << endl;


*/

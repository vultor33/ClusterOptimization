/*
#include "GSA.h"

#include <QDebug>
#include <cmath>
#include <ctime>

#define round_it(d) (static_cast<int>((d)+0.5))

bool GSA::isStopParametrization = false;

GSA::GSA(QObject *parent, const int &dimension_, double *&parameters_0, AbstractParametric *&parametric_) :
AbstractObjCalculation(parent), dimension(dimension_), parametric(parametric_)
{
    this->parameters_0 = parameters_0;

    this->parameters_t = new double[dimension];
    this->parameters_min = new double[dimension];

    this->qAcceptance = 2.5E0;
    this->qTemperature = 2.5E0;
    this->qVisiting = 2.5E0;
    this->qInitialTemperature = 10E0;

    GSA::isStopParametrization = false;
    this->seed = 1;

    this->NStopMax = 15000;

    this->mz = 0;
    this->mj = 0;
    this->mk = 0;
    this->iff = 0;
    this->inext = 0;
    this->inextp = 0;

    for (int i = 0; i < 56; i++)
        this->ma[i] = 0;
}

void GSA::GSAini(const int &seed)
{
    const double pi = 3.14159265359E0;
    this->NRAN = seed;

    D = 0.0E0;

    // Acceptance probability
    this->qAcceptance1 = this->qAcceptance - 1;

    // Temperature
    this->qTemperature1 = this->qTemperature - 1;
    this->temperature = this->qInitialTemperature * (pow(2.0E0, this->qTemperature1) - 1);

    // Visiting probability
    this->qVisiting1 = this->qVisiting - 1;
    this->qVisiting2 = pow(2.0E0, this->qVisiting1) - 1;

    double tmp = 1 / this->qVisiting1 - 0.5E0;
    double gamaDown = dGamma(tmp);
    double gamaUp;

    this->exponent1 = 2.0E0 / (3.0E0 - this->qVisiting);

    double coef1;
    if (D == 0.0E0) {
        coef1 = 1;
        exponent2 = 1 / this->qVisiting1 - 0.5E0;
        gamaUp = gamaDown;
    } else {
        coef1 = pow((this->qVisiting1 / pi), (D * 0.5E0));
        exponent2 = 1 / this->qVisiting1 + 0.5E0 * D - 0.5E0;
        gamaUp = dGamma(this->exponent2);
    }
    this->coef = coef1 * gamaUp / gamaDown;
}

void GSA::Gfunction(const double &T, const double &temperatureUP)
{
    double r, s, DeltaX;

    for (int i = 0; i < this->dimension; i++) {
        r = ran3(NRAN);
        s = ran3(NRAN);

        DeltaX = this->coef * temperatureUP / pow((1 + qVisiting1 * r * r / pow(T, exponent1)), exponent2);

        if (s <= 0.5E0)
            DeltaX = -DeltaX;

        this->parameters_t[i] = this->parameters_0[i] + DeltaX;
    }
}

void GSA::initializeGSA()
{
    double function_0;
    double function_t;
    double function_min;

    //time_t seconds;
    //seconds=time(NULL);
    //int seed = -(int)(seconds%60);

    GSAini((-1)*this->seed);

    for (int i = 0; i < this->dimension; i++) {
        this->parameters_min[i] = parameters_0[i];
        this->parameters_t[i] = parameters_0[i];
    }

    parametric->incrementPointsNumber();
    if (!parametric->runParametrization(dimension, parameters_0)) {
        return;
    }

    function_0 = parametric->getResponseFunction();
    function_min = function_0;
    function_t = function_0;
 
    double OneqAcceptance1 = 1 / this->qAcceptance1;

    double Time = 0.0E0;
    int NCycle = 1;
    // Start Minimization Loop
    do {
        Time += 1;
        NCycle += 1;
        double T = this->temperature / (pow((1 + Time), qTemperature1) - 1); // Temperature T(t)

        double temperatureUP;
        if (D == 0.0E0)
            temperatureUP = 1;
        else
            temperatureUP = pow(T, (D / (this->qTemperature - 3.0E0))); // N�o seria 3-qT  ??

        // Create the new vector  X_t  using the g(qV,t) function.
        Gfunction(T, temperatureUP);

        // Evaluate the Potential function in terms of X_t
        parametric->incrementPointsNumber();
        parametric->runParametrization(dimension, parameters_t);
        function_t = parametric->getResponseFunction();
        
        // Verify if the Potential(X_n+1) is going down. In this case
        // change  X(n) ---> X(n+1). In the other case retains X(n).
        if (function_t <= function_0) {
            for (int i = 0; i < this->dimension; i++)
                parameters_0[i] = this->parameters_t[i];

            function_0 = function_t;
            if (function_t <= function_min) {
                function_min = function_t;

                for (int i = 0; i < this->dimension; i++)
                    this->parameters_min[i] = this->parameters_t[i];
            }
        } else {
            // Evaluate the Acceptance Probability Function [0,1].
            double deltaE = function_t - function_0;

            this->qAcceptance1 = this->qAcceptance - 1;

            double probabilityqAcceptance = 1 / (pow((1 + this->qAcceptance1 * deltaE / T), OneqAcceptance1)); // fun��es q exponenciais

            // If  rand > Acc_Prob retains X_0.
            // If  rand < Acc_Prob replace X_0 by the new X_t.
            if (ran3(NRAN) < probabilityqAcceptance) {
                for (int i = 0; i < this->dimension; i++)
                    parameters_0[i] = this->parameters_t[i];

                function_0 = function_t;
            }
        }
        if (GSA::isStopParametrization)
            return;

    } while (NCycle < this->NStopMax);
    //}

    parametric->endOfParametrization();
}

double GSA::dGamma(const double &r)
{
    const double p0 = 0.999999999999999990E+00;
    const double p1 = -0.422784335098466784E+00;
    const double p2 = -0.233093736421782878E+00;
    const double p3 = 0.191091101387638410E+00;
    const double p4 = -0.024552490005641278E+00;
    const double p5 = -0.017645244547851414E+00;
    const double p6 = 0.008023273027855346E+00;
    const double p7 = -0.000804329819255744E+00;
    const double p8 = -0.000360837876648255E+00;
    const double p9 = 0.000145596568617526E+00;
    const double p10 = -0.000017545539395205E+00;
    const double p11 = -0.000002591225267689E+00;
    const double p12 = 0.000001337767384067E+00;
    const double p13 = -0.000000199542863674E+00;

    double w, y;
    int n, k;

    n = (int) round_it(r - 2.E0);
    w = r - ((double) n + 2.E0);
    y = ((((((((((((p13 * w + p12) * w + p11) * w + p10) * w + p9) * w + p8) * w + p7) * w + p6) * w + p5) *
            w + p4) * w + p3) * w + p2) * w + p1) * w + p0;

    if (n > 0) {
        w = r - 1;
        for (k = 2; k <= n; k++)
            w = w * (r - (double) k);
    } else {
        w = 1.E0;
        for (k = 0; k <= (-n - 1); k++)
            y = y * (r + (double) k);
    }

    return (w / y);
}

double GSA::ran3(int &idum)
{
    //This routine returns an randomic number 0 <= r <= 1
    const double mbig = 1000000000;
    const double mseed = 161803398;
    const double fac = 1.E-9;

    if (idum < 0 || iff == 0) {
        iff = 1;
        mj = mseed - abs(idum);
        ma[55] = mj;
        mk = 1;
        for (int i = 1; i <= 54; i++) {
            int ii = ((21 * i) % 55);
            ma[ii] = mk;
            mk = mj - mk;
            if (mk < mz)
                mk = mk + mbig;

            mj = ma[ii];
        }
        for (int k = 1; k <= 4; k++) {
            for (int i = 1; i <= 55; i++) {
                ma[i] = ma[i] - ma[1 + ((i + 30) % 55)];

                if (ma[i] < mz)
                    ma[i] = ma[i] + mbig;
            }
        }
        inext = 0;
        inextp = 31;
        idum = 1;
    }

    inext = inext + 1;
    if (inext == 56)
        inext = 1;

    inextp = inextp + 1;
    if (inextp == 56)
        inextp = 1;

    mj = ma[inext] - ma[inextp];
    if (mj < mz)
        mj = mj + mbig;

    ma[inext] = mj;

    double ran3_ = mj*fac;

    return (ran3_);
}
*/
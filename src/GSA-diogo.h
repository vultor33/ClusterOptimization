#ifndef GSA_H
#define GSA_H

#include "AbstractParametric.h"

class GSA : public AbstractObjCalculation {
public:
    GSA(QObject *parent, const int &dimension_, double *&parameters_0, AbstractParametric *&parametric_);

    ~GSA() {
        delete(this->parameters_t);
        delete(this->parameters_min);

        /*delete(parametric);*/
    }

    void initializeGSA();

    static bool isStopParametrization;

    void setNStopMax(const int &NStopMax) {
        this->NStopMax = NStopMax;
    }
    
    void setSeed(const int &seed) {
        this->seed = seed;
    }

    void setGSAParameters(const double &qAcceptance, const double &qTemperature, const double &qVisiting, const double &qInitialTemperature) {
        this->qAcceptance = qAcceptance;
        this->qTemperature = qTemperature;
        this->qVisiting = qVisiting;
        this->qInitialTemperature = qInitialTemperature;
    }

private:
    AbstractParametric *parametric;

    int mz;
    int mj;
    int mk;
    int inext;
    int iff;
    int inextp;
    int ma[56];
    
    int seed;

    int NRAN;
    int dimension;
    int NStopMax;

    double qAcceptance;
    double qVisiting;
    double qTemperature;
    double qInitialTemperature;

    double qAcceptance1;
    double qVisiting1;
    double qVisiting2;
    double qTemperature1;
    double temperature;
    double exponent1, exponent2;
    double D, coef;

    double *parameters_0;
    double *parameters_t;
    double *parameters_min;

    void GSAini(const int &seed);
    void Gfunction(const double &T, const double &temperatureUP);

    double dGamma(const double &r);
    double ran3(int &idum);
};

#endif
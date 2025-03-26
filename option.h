#ifndef OPTION_H
#define OPTION_H
#include <vector>
#include <cmath>
#include <iostream>
#include <cstddef>
#include <tuple>

double AmCall(double S, double X, double sigma, double Q, double r, double Tdays, size_t Nofnodes);
double AmPut(double S, double X, double sigma, double Q, double r, double Tdays, size_t Nofnodes);
double CallIV(double S, double X, double Q, double r, double Tdays, size_t Nofnodes, double option_price);
double PutIV(double S, double X, double Q, double r, double Tdays, size_t Nofnodes, double option_price);
std::tuple<double, double> NiceStartVal(double sigma0, double sigma1);

extern "C"
{
    double AmCall_c(double S, double X, double sigma, double Q, double r, double Tdays, size_t Nofnodes);
    double AmPut_c(double S, double X, double sigma, double Q, double r, double Tdays, size_t Nofnodes);
    double CallIV_c(double S, double X, double Q, double r, double Tdays, size_t Nofnodes, double option_price);
    double PutIV_c(double S, double X, double Q, double r, double Tdays, size_t Nofnodes, double option_price);
}






#endif

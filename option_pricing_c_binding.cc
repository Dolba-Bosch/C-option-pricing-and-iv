#include "main.ih"

extern "C"
{
    double AmCall_c(double S, double X, double sigma, double Q, double r, double Tdays, size_t Nofnodes)
    {
        return AmCall(S, X, sigma, Q, r, Tdays, Nofnodes);
    }
    double AmPut_c(double S, double X, double sigma, double Q, double r, double Tdays, size_t Nofnodes)
    {
        return AmPut(S, X, sigma, Q, r, Tdays, Nofnodes);
    }
    double CallIV_c(double S, double X, double Q, double r, double Tdays, size_t Nofnodes, double option_price) 
    {
        return CallIV(S, X, Q, r, Tdays, Nofnodes, option_price);
    }
    double PutIV_c(double S, double X, double Q, double r, double Tdays, size_t Nofnodes, double option_price) 
    {
        return PutIV(S, X, Q, r, Tdays, Nofnodes, option_price);
    }

}

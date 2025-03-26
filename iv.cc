#include "main.ih"


std::tuple<double, double> NiceStartVal(double sigma0, double sigma1)
{
    // find a good starting point such that the secant method has some variation to work with
    std::tuple<double, double> result;
    size_t max_iter = 30;
    while(max_iter-- > 0)
    {
        if(sigma0 == sigma1)
            sigma1 = sigma1*2;
        if(sigma0 == sigma1)
            sigma0 = sigma0*2;
        if(sigma0 != sigma1)
            break;
    }
    return std::make_tuple(sigma0, sigma1);
}


double CallIVSecant(double S, double X, double Q, double r, double Tdays, size_t Nofnodes, double option_price, double sigma)
{
    std::tuple<double, double> start_vals = NiceStartVal(sigma/2, sigma*2);
    double sigma0 = std::get<0>(start_vals);
    double sigma1 = std::get<1>(start_vals);
    double f0 = AmCall(S, X, sigma0, Q, r, Tdays, Nofnodes) - option_price;
    double f1 = AmCall(S, X, sigma1, Q, r, Tdays, Nofnodes) - option_price;
    size_t max_iter = 100;
    while (max_iter-- > 0) 
    {
        double sigma2 = sigma1 - f1 * (sigma1 - sigma0) / (f1 - f0);
        double f2 = AmCall(S, X, sigma2, Q, r, Tdays, Nofnodes) - option_price;
        // if very close, double the sigmas to introduce more variation
        if (fabs(f1 - f2) < 0.001)
        {
            sigma1 = sigma1*2;
            sigma0 = sigma0*2;
            continue;
        }
        if (fabs(f2) < 0.001)
            return sigma2;
        sigma0 = sigma1;
        sigma1 = sigma2;
        f0 = f1;
        f1 = f2;
    }
    return 0;
}

double PutIVSecant(double S, double X, double Q, double r, double Tdays, size_t Nofnodes, double option_price, double sigma)
{
    std::tuple<double, double> start_vals = NiceStartVal(sigma/2, sigma*2);
    double sigma0 = std::get<0>(start_vals);
    double sigma1 = std::get<1>(start_vals);
    double f0 = AmPut(S, X, sigma0, Q, r, Tdays, Nofnodes) - option_price;
    double f1 = AmPut(S, X, sigma1, Q, r, Tdays, Nofnodes) - option_price;
    size_t max_iter = 100;
    while (max_iter-- > 0) 
    {
        double sigma2 = sigma1 - f1 * (sigma1 - sigma0) / (f1 - f0);
        double f2 = AmPut(S, X, sigma2, Q, r, Tdays, Nofnodes) - option_price;
        if (fabs(f1 - f2) < 0.001)
        {
            sigma1 = sigma1*2;
            sigma0 = sigma0*2;
            continue;
        }
        if (fabs(f2) < 0.001)
            return sigma2;
        sigma0 = sigma1;
        sigma1 = sigma2;
        f0 = f1;
        f1 = f2;
    }
    return 0;
}

double CallIV(double S, double X, double Q, double r, double Tdays, size_t Nofnodes, double option_price) 
{
    if (X + option_price < S or option_price <= 0)
        return 0;

    return CallIVSecant(S, X, Q, r, Tdays, Nofnodes, option_price, 0.2);
}

double PutIV(double S, double X, double Q, double r, double Tdays, size_t Nofnodes, double option_price) 
{
    if (X - S > option_price or option_price <= 0)
        return 0;

    return PutIVSecant(S, X, Q, r, Tdays, Nofnodes, option_price, 0.2);
}


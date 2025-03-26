#include "main.ih"

// implementation of binomial tree option pricing

double AmCall(double S, double X, double sigma, double Q, double r, double Tdays, size_t Nofnodes)
{
    if(Tdays <= 0)
        return std::max(S - X, 0.0);
    
    std::vector<double> stock_prices = std::vector<double>(Nofnodes, 0.0);
    std::vector<double> option_prices = std::vector<double>(Nofnodes, 0.0);
    double T = Tdays / 365.0;
    double dt = T / (Nofnodes-1);
    double a = exp((r-Q)*dt);
    double b2 = a * a * (exp(sigma * sigma * dt) - 1);
    double u = ((a*a+b2+1)+sqrt((a*a+b2+1)*(a*a+b2+1)-4*a*a))/(2*a);
    double d = 1/u;
    double p = (a-d)/(u-d);
    double q = 1-p;

    if(p <= 0 || p >= 1)
        return 0;
    stock_prices[0] = S * (pow(d, Nofnodes-1));
    option_prices[0] = std::max(stock_prices[0] - X, 0.0);
    for(size_t i = 1; i != Nofnodes; ++i)
    {
        stock_prices[i] = stock_prices[i-1] * u / d;
        option_prices[i] = std::max(stock_prices[i] - X, 0.0);
    }
    double day_discount = exp(-r * dt);
    for(size_t k = Nofnodes; k != 0; --k)
    {
        for(size_t l = 0; l != k-1; ++l)
        {
            stock_prices[l] = stock_prices[l] * u;
            option_prices[l] = day_discount * (q * option_prices[l] + p * option_prices[l+1]);
            option_prices[l] = std::max(option_prices[l], stock_prices[l] - X);
        }
    }
    return option_prices[0];
}

double AmPut(double S, double X, double sigma, double Q, double r, double Tdays, size_t Nofnodes)
{
    if(Tdays <= 0)
        return std::max(X - S, 0.0);
    std::vector<double> stock_prices = std::vector<double>(Nofnodes, 0.0);
    std::vector<double> option_prices = std::vector<double>(Nofnodes, 0.0);
    double T = Tdays / 365.0;
    double dt = T / (Nofnodes-1);
    double a = exp((r-Q)*dt);
    double b2 = a * a * (exp(sigma * sigma * dt) - 1);
    double u = ((a*a+b2+1)+sqrt((a*a+b2+1)*(a*a+b2+1)-4*a*a))/(2*a);
    double d = 1/u;
    double p = (a-d)/(u-d);
    double q = 1-p;
    if(p <= 0 || p >= 1)
        return 0;
    stock_prices[0] = S * (pow(d, Nofnodes-1));
    option_prices[0] = std::max(X - stock_prices[0], 0.0);
    for(size_t i = 1; i != Nofnodes; ++i)
    {
        stock_prices[i] = stock_prices[i-1] * u / d;
        option_prices[i] = std::max(X - stock_prices[i], 0.0);
    }
    double day_discount = exp(-r * dt);
    for(size_t k = Nofnodes; k != 0; --k)
    {
        for(size_t l = 0; l != k-1; ++l)
        {
            stock_prices[l] = stock_prices[l] * u;
            option_prices[l] = day_discount * (q * option_prices[l] + p * option_prices[l+1]);
            option_prices[l] = std::max(option_prices[l], X - stock_prices[l]);
        }
    }
    return option_prices[0];
}


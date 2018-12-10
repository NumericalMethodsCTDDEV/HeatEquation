#include "abstractSolver.h"
#include "config.h"

Solver::Solver(double (*start_profile_builder)(double))
{
    ConfigSingleton const *configs = ConfigSingleton::getConfigs();
    for (double curx = 0, dx = configs->dx; curx <= 1.; curx += dx)
    {
        T.push_back(start_profile_builder(curx));
        x.push_back(curx);
    }
}

Solver::~Solver() {}

const std::vector<double> &Solver::get_T() const { return T; }

double Solver::get_cur_t() const
{
    return cur_t;
}

const std::vector<double> &Solver::get_x() const
{
    return x;
}

#include "ExplicitAgainstFlowDirection.h"
#include "config.h"

void ExplicitAgainstFlowDirection::do_step()
{
    ConfigSingleton const *configs = ConfigSingleton::getConfigs();
    double r = configs->r;
    double s = configs->s;
    double dt = configs->dt;

    cur_t += dt;

    size_t sz = T.size();
    std::vector<double> new_T(sz, 0.);
    new_T[0] = T[0];
    new_T[sz - 1] = T[sz - 1];

    for (size_t i = 1; i < sz - 1; i++)
        new_T[i] =
            r * (T[i + 1] - 2 * T[i] + T[i - 1]) +
            s * (T[i - 1] - T[i]) +
            T[i];

    T.swap(new_T);
}

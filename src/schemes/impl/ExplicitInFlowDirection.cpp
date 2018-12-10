#include "ExplicitInFlowDirection.h"
#include "config.h"

void ExplicitInFlowDirection::do_step()
{
    ConfigSingleton const *configs = ConfigSingleton::getConfigs();
    double u = configs->u;
    double k = configs->k;
    double dx = configs->dx;
    double dt = configs->dt;

    cur_t += dt;

    size_t sz = T.size();
    std::vector<double> new_T(sz, 0.);
    new_T[0] = T[0];
    new_T[sz - 1] = T[sz - 1];

    for (size_t i = 1; i < sz - 1; i++)
        new_T[i] =
            dt * (k * (T[i + 1] - 2 * T[i] + T[i - 1]) / (dx * dx) - u * (T[i + 1] - T[i]) / dx) +
            T[i];
    T.swap(new_T);
}

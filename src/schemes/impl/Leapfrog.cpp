#include "Leapfrog.h"
#include "config.h"

void Leapfrog::do_step()
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

    if (cur_t == dt) {
        for (long long i = 1; i < sz - 1; ++i) {
            new_T[i] =
                r * (T[i + 1] - 2 * T[i] + T[i - 1]) +
                s / 2 * (T[i - 1] - T[i + 1]) +
                T[i];
        }
    } else {
        for (long long i = 1; i < sz - 1; ++i)
            new_T[i] =
                2 * r * (T[i + 1] - 2 * T[i] + T[i - 1]) +
                s * (T[i - 1] - T[i + 1]) +
                TT[i];
    }
    TT = T;
    T.swap(new_T);
}

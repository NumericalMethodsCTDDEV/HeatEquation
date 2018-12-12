#include "ImplicitAgainstFlowDirection.h"
#include "config.h"

void ImplicitAgainstFlowDirection::do_step()
{
    ConfigSingleton const *configs = ConfigSingleton::getConfigs();
    double r = configs->r;
    double s = configs->s;
    double dt = configs->dt;

    cur_t += dt;

    size_t sz = T.size();
    std::vector<std::vector<double>> matrix(sz);
    matrix[0] = {0, 0, 1, T[0]};
    matrix[sz - 1] = {0, 0, 1, T[sz - 1]};

    for (long long i = 1; i < sz - 1; ++i) {
        matrix[i] = {-r - s, -r, 1 + s + 2 * r, T[i]};
    }

    T = tridiagonal_matrix_algorithm(matrix);
}

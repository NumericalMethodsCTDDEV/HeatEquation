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
const std::vector<double> &Solver::get_TT() const { return TT; }

double Solver::get_cur_t() const
{
    return cur_t;
}

const std::vector<double> &Solver::get_x() const
{
    return x;
}

std::vector<double> Solver::tridiagonal_matrix_algorithm(std::vector<std::vector<double>>& matrix) {
    std::vector<double> a_list, b_list;
    double a = -matrix[0][1] / matrix[0][2], b = matrix[0][3] / matrix[0][2];
    double prev_a, prev_b;
    a_list.push_back(a);
    b_list.push_back(b);
    for (long long i = 1; i < matrix.size() - 1; ++i) {
        prev_a = a;
        prev_b = b;

        a = - matrix[i][1] / (prev_a * matrix[i][0] + matrix[i][2]);
        b = (matrix[i][3] - prev_b * matrix[i][0]) / (prev_a * matrix[i][0] + matrix[i][2]);
        a_list.push_back(a);
        b_list.push_back(b);
    }

    std::vector<double> answer(matrix.size());

    answer[answer.size() - 1] = (matrix.back()[3] - b * matrix.back()[0]) / (matrix.back()[2] + a * matrix.back()[0]);
    for (long long i = answer.size() - 2; i >= 0; --i) {
        answer[i] = a_list[i] * answer[i+1] + b_list[i];
    }

    return answer;
}

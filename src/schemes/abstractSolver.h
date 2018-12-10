#ifndef STATE_H
#define STATE_H

#include <vector>

class Solver
{
protected:
    std::vector<double> T;
    std::vector<double> x;
    double cur_t = 0.;

public:
    Solver(double (*)(double));
    virtual ~Solver();

    virtual void do_step() = 0;

    const std::vector<double> &get_T() const;
    double get_cur_t() const;
    const std::vector<double> &get_x() const;
};

#endif // STATE_H

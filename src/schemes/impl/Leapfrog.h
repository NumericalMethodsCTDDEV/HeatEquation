#ifndef LEAPFROG_H
#define LEAPFROG_H
#include "../abstractSolver.h"

class Leapfrog : public Solver
{
public:
    using Solver::Solver;

    void do_step() override;
};

#endif // LEAPFROG_H

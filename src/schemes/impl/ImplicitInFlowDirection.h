#ifndef IMPLICITINFLOWDIRECTION_H
#define IMPLICITINFLOWDIRECTION_H

#include "../abstractSolver.h"

class ImplicitInFlowDirection : public Solver
{
public:
    using Solver::Solver;

    void do_step() override;

};

#endif // IMPLICITINFLOWDIRECTION_H

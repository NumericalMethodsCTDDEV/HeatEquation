#ifndef EXPLICITINFLOWDIRECTION_H
#define EXPLICITINFLOWDIRECTION_H

#include "../abstractSolver.h"

class ExplicitInFlowDirection : public Solver
{
public:
    using Solver::Solver;

    void do_step() override;
};

#endif // EXPLICITINFLOWDIRECTION_H

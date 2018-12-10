#ifndef IMPLICITAGAINSTFLOWDIRECTION_H
#define IMPLICITAGAINSTFLOWDIRECTION_H

#include "../abstractSolver.h"

class ImplicitAgainstFlowDirection : public Solver
{
public:
    using Solver::Solver;
    void do_step() override;
};

#endif // IMPLICITAGAINSTFLOWDIRECTION_H

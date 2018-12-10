#ifndef EXPLICITAGAINSTFLOWDIRECTION_H
#define EXPLICITAGAINSTFLOWDIRECTION_H

#include "../abstractSolver.h"

class ExplicitAgainstFlowDirection : public Solver
{
public:
    using Solver::Solver;
    void do_step() override;
};

#endif // EXPLICITAGAINSTFLOWDIRECTION_H

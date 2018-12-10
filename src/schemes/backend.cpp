#include "backend.h"
#include "config.h"
#include "impl/ExplicitAgainstFlowDirection.h"
#include "impl/ExplicitInFlowDirection.h"
#include "impl/ImplicitAgainstFlowDirection.h"
#include "impl/ImplicitInFlowDirection.h"
#include "impl/Leapfrog.h"
#include "startProfiles.h"
#include <math.h>
#include <stdexcept>

static constexpr double EPS = 0.0000001;

Solver *create_solver()
{
    ConfigSingleton const *configs = ConfigSingleton::getConfigs();
    double (*profile_creator)(double);
    if (fabs(configs->dx) < EPS)
    {
        throw new std::runtime_error("Too low dx");
    }
    else if (fabs(configs->dt) < EPS)
    {
        throw new std::runtime_error("Too low dt");
    }
    switch (configs->start_profile_id)
    {
    case 0:
        profile_creator = stair;
        break;
    case 1:
        profile_creator = trapezium;
        break;
    default:
        throw new std::runtime_error("Invalid start profile / Not implemented yet");
    }
    switch (configs->method_id)
    {
    case 0:
        return new ExplicitInFlowDirection(profile_creator);
    case 1:
        return new ExplicitAgainstFlowDirection(profile_creator);
    case 2:
        return new ImplicitInFlowDirection(profile_creator);
    case 3:
        return new ImplicitAgainstFlowDirection(profile_creator);
    case 4:
        return new Leapfrog(profile_creator);
    default:
        throw new std::runtime_error("Invalid method / Not implemented yet");
    }
}

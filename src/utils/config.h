#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class ConfigSingleton
{

    static const ConfigSingleton *configSingletonPtr;

    ConfigSingleton(double u, double k, double dt, double dx, int method_id, int start_profile_id)
        : u(u), k(k), dt(dt), dx(dx), s(u / dx), r(k * dt / (dx * dx)), method_id(method_id), start_profile_id(start_profile_id)
    {
    }

    ConfigSingleton() : u(0), k(0), dt(0), dx(0), r(0), s(0), method_id(0), start_profile_id(0) {}

public:
    const double u;
    const double k;
    const double r;
    const double s;
    const double dt;
    const double dx;
    const int method_id;
    const int start_profile_id;

    static const ConfigSingleton *getConfigs()
    {
        if (!configSingletonPtr)
            configSingletonPtr = new ConfigSingleton;
        return configSingletonPtr;
    }

    static const ConfigSingleton *createConfigs(double u, double k, double dt, double dx, int method_id, int start_profile_id)
    {
        if (configSingletonPtr)
            return configSingletonPtr;
        configSingletonPtr = new ConfigSingleton(u, k, dt, dx, method_id, start_profile_id);
        return configSingletonPtr;
    }

    static void releaseConfigs()
    {
        delete configSingletonPtr;
        configSingletonPtr = nullptr;
    }
};

#endif // CONFIG_H

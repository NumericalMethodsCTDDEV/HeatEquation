double stair(double p) { return (p >= 0.35 && p <= 0.65) ? 1.0 : 0.0; }

double trapezium(double p)
{
    static constexpr double a1 = 1. / 8.;
    static constexpr double a2 = 3. / 8.;
    static constexpr double k1 = 1. / (a2 - a1);
    static constexpr double b1 = 5. / 8.;
    static constexpr double b2 = 7. / 8.;
    static constexpr double k2 = 1. / (b2 - b1);

    if (p <= a1)
        return 0.;
    if (p >= b2)
        return 0.;
    if ((a2 <= p) && (p <= b1))
        return 1.0;
    if ((a1 <= p) && (p <= a2))
        return (p - a1) * k1;
    if ((b1 <= p) && (p <= b2))
        return (b2 - p) * k2;
    return 0.;
}

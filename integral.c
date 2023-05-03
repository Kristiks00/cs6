//Sympson's method
double integral(double (*f)(double), double a, double b, double eps2){
    int n = 2;
    double delta = (b - a), r = (b - a) / 6, e = 0;
    double S1 = 2 * f(a + delta / 2), I1 = r * (f(a) + f(b) + 2 * S1), I2 = 0, S2 = 0;
    delta /= 2;
    double i = a + delta / 2;
    for(int j = 0; j < n; j++){
        S2 += f(i);
        i += delta;
    }
    S2 *= 2;
    I2 = I1 / 2 + r * (2 * S2 - S1) / n;
    e = I2 - I1;
    if (e < 0)
        e *= -1;
    while (e > eps2){
        n *= 2;
        I1 = I2, I2 = 0, S1 = S2, S2 = 0;
        delta /= 2, i = a + delta / 2;
        for(int j = 0; j < n; j++){
            S2 += f(i);
            i += delta;
        }
        S2 *= 2;
        I2 = I1 / 2 + r * (2 * S2 - S1) / n;
        e = I2 - I1;
        if (e < 0)
            e *= -1;
    }
    return I2;
}

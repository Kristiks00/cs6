#include <stdio.h>
#include <math.h>

double root(double (*f)(double), double (*df)(double), double (*g)(double), double (*dg)(double), double a, double b, double eps1){ //h(x) = f(x) - g(x)
    double h_a = f(a) - g(a), h_b = f(b) - g(b), c = (a + b) / 2;
    double h_c = f(c) - g(c), y_c = (h_b - h_a) / (b - a) * c + h_a;
    double prev, dh;
    int sign_dh = 1, sign_ddh = 1;
    if (h_a > h_b) sign_dh = -1;
    if (h_c > y_c) sign_ddh = -1;

    if(sign_dh * sign_ddh < 0){ //shift b
        do{
            prev = b;
            dh = df(b) - dg(b);
            b = prev - h_b/dh;
            h_b = f(b) - g(b);
        } while ((prev - b) > eps1);
        return b;
    }
    else{ //shift a
        do{
            prev = a;
            dh = df(a) - dg(a);
            a = prev - h_a/dh;
            h_a = f(a) - g(a);
        } while ((a - prev) > eps1);
        return a;
    }
}

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

double f1(double x){ //y = ln x
    return log(x);
}

double df1(double x){
    return 1 / x;
}

double f2(double x){ //y = -2x + 14
    return (-2) * x + 14;
}

double df2(double x){
    return -2;
}

double f3(double x){ //y = 1 / (2 - x) + 6
    return 1 / (2 - x) + 6;
}

double df3(double x){
    return 1 / (2 - x) / (2 - x);
}

int main(void){
    double eps = 0.001;
    double eps1 = eps / 100;
    double x12 = root(f1, df1,  f2, df2, 6, 7, eps1);
    double x23 = root(f2, df2, f3, df3, 4, 5, eps1);
    double x13 = root(f1, df1, f3, df3, 2.1, 2.2, eps1);
    printf("%lf %lf %lf\n", x12, x23, x13);

    double I = 0;
    I += integral(f2, x23, x12, eps);
    I += integral(f3, x13, x23, eps);
    I -= integral(f1, x13, x12, eps);
    printf("%lf\n", I);

    return 0;
}

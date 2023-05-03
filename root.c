//tangent method
extern int c_root;
double root(double (*f)(double), double (*df)(double), double (*g)(double), double (*dg)(double), double a, double b, double eps1){ //h(x) = f(x) - g(x)
    c_root = 0;
    double h_a = f(a) - g(a), h_b = f(b) - g(b), c = (a + b) / 2;
    double h_c = f(c) - g(c), y_c = (h_b - h_a) / (b - a) * c + h_a;
    double prev, dh;
    int sign_dh = 1, sign_ddh = 1;
    if (h_a > h_b) sign_dh = -1;
    if (h_c < y_c) sign_ddh = -1;

    if(sign_dh * sign_ddh < 0){ //shift b
        do{
            prev = b;
            dh = df(b) - dg(b);
            b = prev - h_b/dh;
            h_b = f(b) - g(b);
            c_root++;
        } while ((prev - b) > eps1);
        return b;
    }
    else{ //shift a
        do{
            prev = a;
            dh = df(a) - dg(a);
            a = prev - h_a/dh;
            h_a = f(a) - g(a);
            c_root++;
        } while ((a - prev) > eps1);
        return a;
    }
}

#include <stdio.h>
#include <string.h>

int c_root; //count of iteration

double f1(double x); //y = lnx
double df1(double x); //y = 1 / x
double f2(double x); //y = -2x + 14
double df2(double x); //y = -2
double f3(double x); //y = 1 / (2 - x) + 6
double df3(double x); //y = 1 / (2 - x) / (2 - x)
double debug1(double x); //y = x ^ 3
double ddebug1(double x); //y = 3 * x ^ 2
double debug2(double x); //y = (x - 2) ^ 2
double ddebug2(double x); //y = 2x - 4
double debug3(double x); //y = -2x + 12
double ddebug3(double x); //y = -2

double root(double (*f)(double), double (*df)(double), double (*g)(double), double (*dg)(double), double a, double b, double eps1);
double integral(double (*f)(double), double a, double b, double eps2);

int main(int args, char *argv[]){
    double eps = 0.001;
    double eps1 = eps / 6, eps2 = eps / 18;
    int i12, i23, i13;
    double x12 = root(f1, df1,  f2, df2, 6, 7, eps1);
    i12 = c_root;
    double x23 = root(f2, df2, f3, df3, 4, 5, eps1);
    i23 = c_root;
    double x13 = root(f1, df1, f3, df3, 2.1, 2.2, eps1);
    i13 = c_root;
    double I = 0;
    I += integral(f2, x23, x12, eps2);
    I += integral(f3, x13, x23, eps2);
    I -= integral(f1, x13, x12, eps2);
    for(int i = 1; i < args; i++){
        if (!strcmp(argv[i], "-help")){
            printf("Write -r to watch roots.\n");
            printf("Write -i to watch count of iteration by tangent method.\n");
            printf("Write -d for debug root and integral.\n\n");
            printf("Functions in debug: f1 = x^3, f2 = (x - 2)^2, f3 = -2x + 12\n");
        }
        else if (!strcmp(argv[i], "-d")){
            //debug roots
            double d12 = root(debug1, ddebug1, debug2, ddebug2, 0, 2, eps1);
            double d23 = root(debug2, ddebug2, debug3, ddebug3, 2, 5, eps1);
            double d13 = root(debug1, ddebug1, debug3, ddebug3, 0, 3, eps1);
            printf("x12_debug = %.4lf\nx23_debug = %.4lf\nx13_debug = %.4lf\n", d12, d23, d13);

            //debug integrals
            double dI = 0;
            dI += integral(debug1, d12, d13, eps);
            dI += integral(debug3, d13, d23, eps);
            dI -= integral(debug2, d12, d23, eps);
            printf("Area_debug = %.4lf\n", dI);
        }
        else{
            while(i < args){
                if (!strcmp(argv[i], "-r")){
                    printf("x12 = %.4lf, x23 = %.4lf, x13 = %.4lf\n", x12, x23, x13);
                    i++;
                }
                else if (!strcmp(argv[i], "-i")){
                    printf("f1, f2: %d\nf2, f3: %d\nf1, f3: %d\n", i12, i23, i13);
                    i++;
                }
                else
                    break;
            }
        }
    }
    printf("Area = %.4lf\n", I);
    return 0;
}

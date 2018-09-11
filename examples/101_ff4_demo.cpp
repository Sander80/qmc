/*
 * Compile without GPU support:
 *   c++ -std=c++11 -pthread -I../src 101_ff4_demo.cpp -o 101_ff4_demo.out -lgsl -lgslcblas
 * Compile with GPU support:
 *   nvcc -std=c++11 -x cu -I../src 101_ff4_demo.cpp -o 101_ff4_demo.out -lgsl -lgslcblas
 */

#include <iostream>
#include <iomanip>

#include "qmc.hpp"

struct formfactor4L_t {
#ifdef __CUDACC__
    __host__ __device__
#endif
    double operator()(const double arg[]) const
    {

        double x0  = arg[0];
        double x1  = (1.-x0)*arg[1];
        double x2  = (1.-x0-x1)*arg[2];
        double x3  = (1.-x0-x1-x2)*arg[3];
        double x4  = (1.-x0-x1-x2-x3)*arg[4];
        double x5  = (1.-x0-x1-x2-x3-x4)*arg[5];
        double x6  = (1.-x0-x1-x2-x3-x4-x5)*arg[6];
        double x7  = (1.-x0-x1-x2-x3-x4-x5-x6)*arg[7];
        double x8  = (1.-x0-x1-x2-x3-x4-x5-x6-x7)*arg[8];
        double x9  = (1.-x0-x1-x2-x3-x4-x5-x6-x7-x8)*arg[9];
        double x10 = (1.-x0-x1-x2-x3-x4-x5-x6-x7-x8-x9)*arg[10];
        double x11 = (1.-x0-x1-x2-x3-x4-x5-x6-x7-x8-x9-x10);

        double wgt =
        (1.-x0)*
        (1.-x0-x1)*
        (1.-x0-x1-x2)*
        (1.-x0-x1-x2-x3)*
        (1.-x0-x1-x2-x3-x4)*
        (1.-x0-x1-x2-x3-x4-x5)*
        (1.-x0-x1-x2-x3-x4-x5-x6)*
        (1.-x0-x1-x2-x3-x4-x5-x6-x7)*
        (1.-x0-x1-x2-x3-x4-x5-x6-x7-x8)*
        (1.-x0-x1-x2-x3-x4-x5-x6-x7-x8-x9);

        if(wgt <= 0.0) return 0;

        double f = x1*(x8*(x3*x4*x6+x4*(x5+x6)*x7+x3*(x4+x5+x6)*x7+(x4+x5+x6)*x7*x9+x11*(x6+x7)*(x3+x4+x9))+x10*((x11*x6+(x11+x5+x6)*x7)*(x8+x9)+x4*x7*(x5+x8+x9)))+x0*(x2*x3*x4*x5+x1*x3*x4*x8+x2*x3*x4*x8+x1*x3*x5*x8+x2*x3*x5*x8+x1*x4*x5*x8+x2*x4*x5*x8+x3*x4*x5*x8+x1*x3*x6*x8+x2*x3*x6*x8+x1*x4*x6*x8+x2*x4*x6*x8+x3*x4*x6*x8+x3*x4*x7*x8+x3*x5*x7*x8+x4*x5*x7*x8+x3*x6*x7*x8+x4*x6*x7*x8+x11*(x3+x4)*(x2*x5+(x1+x2+x5+x6+x7)*x8)+(x4+x5+x6)*(x2*x3+(x1+x2+x3+x7)*x8)*x9+x11*((x1+x3+x4+x5+x6+x7)*x8+x2*(x3+x4+x5+x8))*x9+x10*(x11*(x4*x5+x1*x8+x4*x8+x5*x8+x6*x8+x7*x8+(x1+x4+x5+x6+x7)*x9+x2*(x5+x8+x9)+x3*(x5+x8+x9))+(x1+x2+x3+x7)*((x5+x6)*(x8+x9)+x4*(x5+x8+x9))));
        double u = x10*x11*x2*x5+x10*x11*x3*x5+x11*x2*x3*x5+x10*x11*x4*x5+x10*x2*x4*x5+x11*x2*x4*x5+x10*x3*x4*x5+x2*x3*x4*x5+x10*x11*x2*x6+x10*x11*x3*x6+x11*x2*x3*x6+x10*x11*x4*x6+x10*x2*x4*x6+x11*x2*x4*x6+x10*x3*x4*x6+x2*x3*x4*x6+x10*x11*x2*x7+x10*x11*x3*x7+x11*x2*x3*x7+x10*x11*x4*x7+x10*x2*x4*x7+x11*x2*x4*x7+x10*x3*x4*x7+x2*x3*x4*x7+x10*x2*x5*x7+x10*x3*x5*x7+x2*x3*x5*x7+x10*x4*x5*x7+x2*x4*x5*x7+x10*x2*x6*x7+x10*x3*x6*x7+x2*x3*x6*x7+x10*x4*x6*x7+x2*x4*x6*x7+x10*x11*x2*x8+x10*x11*x3*x8+x11*x2*x3*x8+x10*x11*x4*x8+x10*x2*x4*x8+x11*x2*x4*x8+x10*x3*x4*x8+x2*x3*x4*x8+x10*x11*x5*x8+x10*x2*x5*x8+x10*x3*x5*x8+x11*x3*x5*x8+x2*x3*x5*x8+x11*x4*x5*x8+x2*x4*x5*x8+x3*x4*x5*x8+x10*x11*x6*x8+x10*x2*x6*x8+x10*x3*x6*x8+x11*x3*x6*x8+x2*x3*x6*x8+x11*x4*x6*x8+x2*x4*x6*x8+x3*x4*x6*x8+x10*x11*x7*x8+x11*x3*x7*x8+x10*x4*x7*x8+x11*x4*x7*x8+x3*x4*x7*x8+x10*x5*x7*x8+x3*x5*x7*x8+x4*x5*x7*x8+x10*x6*x7*x8+x3*x6*x7*x8+x4*x6*x7*x8+(x11*x2*(x3+x4+x5+x6+x7)+x10*((x4+x5+x6)*(x2+x3+x7)+x11*(x2+x3+x4+x5+x6+x7))+x11*(x2+x3+x4+x5+x6+x7)*x8+(x4+x5+x6)*(x2*(x3+x7)+(x2+x3+x7)*x8))*x9+x0*(x10*x11*x2+x10*x11*x3+x11*x2*x3+x10*x11*x4+x10*x2*x4+x11*x2*x4+x10*x3*x4+x2*x3*x4+x10*x11*x5+x10*x2*x5+x10*x3*x5+x11*x3*x5+x2*x3*x5+x11*x4*x5+x2*x4*x5+x3*x4*x5+x10*x11*x6+x10*x2*x6+x10*x3*x6+x11*x3*x6+x2*x3*x6+x11*x4*x6+x2*x4*x6+x3*x4*x6+x10*x11*x7+x11*x3*x7+x10*x4*x7+x11*x4*x7+x3*x4*x7+x10*x5*x7+x3*x5*x7+x4*x5*x7+x10*x6*x7+x3*x6*x7+x4*x6*x7+(x4+x5+x6)*(x2+x3+x7)*x9+x11*(x2+x3+x4+x5+x6+x7)*x9+x1*(x3*x4+x3*x5+x4*x5+x3*x6+x4*x6+x10*(x11+x4+x5+x6)+(x4+x5+x6)*x9+x11*(x3+x4+x9)))+x1*(x3*x4*x5+x3*x4*x6+x3*x4*x7+x3*x5*x7+x4*x5*x7+x3*x6*x7+x4*x6*x7+x3*x4*x8+x3*x5*x8+x4*x5*x8+x3*x6*x8+x4*x6*x8+x11*(x3+x4)*(x5+x6+x7+x8)+(x4+x5+x6)*(x3+x7+x8)*x9+x11*(x3+x4+x5+x6+x7+x8)*x9+x10*((x5+x6)*(x7+x8+x9)+x11*(x5+x6+x7+x8+x9)+x4*(x5+x6+x7+x8+x9)));
        double n = x0*x9;
        double d = f*f*u;

        return wgt*n/d;
    }
} formfactor4L;

int main() {

    integrators::Qmc<double,double> integrator;
    integrator.minm = 20;
    integrator.maxeval = 1; // do not iterate

    integrators::transforms::Korobov<double,unsigned long long int,1> integral_transform;

    std::cout << "# n m Re[I] Im[I] Re[Abs. Err.] Im[Abs. Err.]" << std::endl;
    std::cout << std::setprecision(16);

    for(const auto& generating_vector : integrator.generatingvectors)
    {
        integrator.minn = generating_vector.first;
        integrators::result<double> result = integrator.integrate(formfactor4L,11,integral_transform);

        std::cout
        << result.n
        << " " << result.m
        << " " << result.integral
        << " " << result.error
        << std::endl;
    }
}




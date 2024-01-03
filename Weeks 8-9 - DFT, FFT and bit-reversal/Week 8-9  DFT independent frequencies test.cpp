// Week 8-9 - Calculation of number of independent frequencies using DFT algorithm

#include <iostream>
#include<complex>
#include<cmath>

#include "FourierTransforms.h"

double x_function(double t, int N)
{
    double sin_term = sin(t / 2.0);
    return (sin_term != 0.0) ? (sin((N + 0.5) * t) / sin_term - 1.0) : 0.0;
}

int main() {

    // Example usage
    const int N = 256; // Number of samples
    const double dt = 0.1;  // Time step
    const  double T = N * dt; // Total time duration
    const double f_sampling = 1.0 / dt; //Sampling frequency

    // Sample the function x(t)
    double t[N];
    std::complex<double> x[N];
    for (int n = 0; n < N; ++n)
    {
        t[n] = n * dt;
        x[n] = std::complex<double> (x_function(t[n], N), 0.0);
    }

    //Calculate DFT
    std::complex<double> X[N];
    DFT(x, X, N);

    // Analyse the spectrum and count peaks
    int independentFrequencies = 0;
    for (int k = 0; k < N / 2; ++k)
    {
        double magnitude = std::abs(X[k]);
        if (magnitude > 0.1) // Threshold for considering a frequency
        {
            independentFrequencies++;
        }
    }

    // Display DFT results
    std::cout << "DFT: " << std::endl;
    for (int i = 0; i < N; ++i) {
        std::cout << "#" << i << ":\t" << x[i] << " \t>> abs: " << abs(X[i]) << " >> phase: " << arg(X[i]) << std::endl;
    }
    std::cout << std::endl;

    // Display number of independent frequencies
    std::cout << "Number of independent frequencies: " << independentFrequencies << '\n';
}

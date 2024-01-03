// Week 8-9 - Calculation of number of independent frequencies using DFT algorithm

#include <iostream>
#include<complex>
#include<cmath>

//Uncomment to remove debug
//#define NDEBUG
#include<cassert>

#include "FourierTransforms.h"

template<typename T>
void Print(T message) {
    std::cout << message << std::endl;
}

template<typename T>
void Print(std::string message, T data)
{
    std::cout << message << data << std::endl;
}

double x_function(double t, int A)
{
    double sin_term = sin(t / 2.0);
    return (sin_term != 0.0) ? (sin((A + 0.5) * t) / sin_term - 1.0) : 0.0;
}

int main() {

    // Example usage
    const int N = 256; // Number of samples
    const double dt = 0.1;  // Time step
    const  double T = N * dt; // Total time duration
    const double f_sampling = 10.0 / dt; //Sampling frequency

    // Sample the function x(t)
    double t[N];
    std::complex<double> x[N];
    for (int n = 0; n < N; ++n)
    {
        t[n] = n * dt;
        x[n] = std::complex<double> (x_function(t[n], 4.0), 0.0);
    }

    //Calculate DFT
    std::complex<double> X[N];
    DFT(x, X, N);

    // Find maximum frequency
    double f_max = findDominantFrequency(X, N, f_sampling);
    // Check if sampling frequency obeys Nyquist limit
    bool nyquistCompliance = ensureNyquistCompliance(f_sampling, f_max);
    // Analyse the spectrum and count peaks
    int independentFrequencies = findIndependentFrequencies(X, N, 10.0);

    // Display DFT results
    std::cout << "DFT: " << std::endl;
    for (int i = 0; i < N; ++i) {
        std::cout << "#" << i << ":\t" << x[i] << " \t>> abs: " << abs(X[i]) << " >> phase: " << arg(X[i]) << std::endl;
    }
    std::cout << std::endl;

    //Display nyquist compliance
    Print("Nyquist compliance: ", nyquistCompliance);
    //Display f_sampling
    Print("f_sampling: ", f_sampling);
    //Display maximum frequency
    Print("f_max: ", f_max);
    // Display number of independent frequencies
    Print("Number of independent frequencies: ", independentFrequencies);
}

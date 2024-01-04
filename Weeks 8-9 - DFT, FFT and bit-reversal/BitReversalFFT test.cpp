#include <iostream>
#include<vector>
#include<complex>
#include<cmath>

//Uncomment to remove debug
//#define NDEBUG
#include<cassert>

#include "FourierTransforms.h"

void LineBreak() {
    std::cout << '\n';
}

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
    return (sin_term != 0.0) ? ((sin((A + 0.5) * t) / sin_term) - 1.0) : 0.0;
}

typedef std::complex<double> Complex;

int main()
{    
    // Example usage
    const int N = 512; // Number of samples
    const double dt = 0.1;  // Time step
    const  double T = N * dt; // Total time duration
    const double f_sampling = 10.0 / dt; //Sampling frequency

    // Sample the function x(t)
    double t[N];
    std::vector<Complex> xBRFFT(N, (0.0, 0.0)); // Bit reversal FFT
    std::vector<Complex> xFFT(N, (0.0, 0.0)); // Standard FFT

    double A = 4.0; // Abitrary constant
    for (int n = 0; n < N; ++n)
    {
        t[n] = n * dt;
        xBRFFT[n] = Complex(x_function(t[n], 4.0), 0.0);
        xFFT[n] = Complex(x_function(t[n], 4.0), 0.0);
    }

    // Calculate FFT
    std::vector<Complex> XFFT = FFT(xFFT);
    FFT_BitReversal(xBRFFT);

    // Display results
    std::cout << "DFT: " << std::endl;
    for (int i = 0; i < N; ++i) 
    {
        std::cout << "#" << i << ":\t" << xFFT[i] << " \t>> abs DFT: " << abs(xBRFFT[i]) << " >> abs FFT: " << abs(XFFT[i]) << std::endl;
    }
    std::cout << std::endl;
}

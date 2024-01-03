// Weeks 8-9 - DFT, FFT and bit-reversal
//
//File containing  tests and use cases for the DFT and IDFT functions.

#include <iostream>
#include<complex>
#include<cmath>

//Uncomment to remove debug
//#define NDEBUG
#include<cassert>

#include "FourierTransforms.h"


int main() {

    // Example usage
    const int N = 9; // Number of samples
    std::complex<double> x[N]{1, 2, 3, 4, 5, 6,7, 8,  9}; // Input sequence
    std::complex<double> X[N]; // Output sequence (DFT result)

    // Calculate DFT
    DFT(x, X, N);

    // Display results
    std::cout << "DFT: " << std::endl;
    for (int i = 0; i < N; ++i) {
        std::cout << "#" << i << ":\t" << x[i] << " \t>> abs: " << abs(X[i]) << " >> phase: " << arg(X[i]) << std::endl;
    }
    std::cout << std::endl;   

    std::complex<double> inverse_x[N]; //Output sequence of (IDFT result)

    //Calculaate inverse
    IDFT(X, x, N);

    //Display results
    Print("IDFT: ");
    for (int i = 0; i < N; ++i)
    {
        std::cout << "#" << i << ":\tabs: " << abs(X[i]) << " \t>> " << x[i] << std::endl;
    }
}


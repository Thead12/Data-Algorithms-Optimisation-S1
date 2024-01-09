#pragma once

//Week 8-9 challange
// Implementation of various fourier transform algorithms

//============== Required includes ============== 
#include <iostream>
#include<complex>
#include<cmath>
#include<vector>

//Uncomment to remove debug
//#define NDEBUG
#include<cassert>

typedef std::complex<double> Complex;

namespace FT
{
	const double PI = 3.141592653589793238462643383279502884;
}

bool ensureNyquistCompliance(double f_sampling, double  dt)
{
	double f_nyquist = 0.5 * dt;
	return f_sampling > f_nyquist;
}

int findIndependentFrequencies(Complex* X, int N, double threshold)
{
	int independentFrequencies = 0;
	for (int k = 0; k < N / 2; k++)
	{
		double magnitude = std::abs(X[k]);
		if (magnitude > threshold)
		{
			independentFrequencies++;
		}
	}
	return independentFrequencies;
}

double findDominantFrequency(const Complex* X, int N, double sampling_rate)
{
	double sumMagnitudeWeightedIndices = 0.0;
	double sumMagnitude = 0.0;

	for (int k = 0; k < N; ++k)
	{
		double magnitude = std::abs(X[k]);
		sumMagnitude += magnitude;
		sumMagnitudeWeightedIndices += k * magnitude;
	}

	// Avoid division by zero
	if (sumMagnitude > 0.0)
	{
		// Calculate the weighted average of frequency indices
		double dominantFrequency = sumMagnitudeWeightedIndices / sumMagnitude * (sampling_rate / N);
		return dominantFrequency;
	}

	// Return 0 if sumMagnitude is zero to handle special cases
	return 0.0;
}

void DFT(const Complex* x, Complex* X, int N)
{
	for (int k = 0; k < N; ++k)
	{
		X[k] = 0;
		for (int n = 0; n < N; ++n)
		{
			Complex temp = std::polar(1.0, -2.0 * FT::PI * k * n / N);
			X[k] += x[n] * temp;
		}
	}
}

// Overload of standard DFT for use in FFT algorithm
void DFT(std::vector<Complex>& x, int N)
{
	//Initialise X array
	std::vector<Complex> X(N, 0.0);
	for (int k = 0; k < N; ++k)
	{
		for (int n = 0; n < N; ++n)
		{
			Complex temp = std::polar(1.0, -2.0 * FT::PI * k * n / N);
			X[k] += x[n] * temp;
		}
	}
}

void IDFT(const Complex* X, Complex* x, int N)
{
	for (int n = 0; n < N; ++n)
	{
		x[n] = 0;
		for (int k = 0; k < N; ++k)
		{
			Complex temp = std::polar(1.0, 2.0 * FT::PI * k * n / N);
			x[n] += X[k] * temp;
		}
		x[n] = x[n].real() / N;
	}
}

// Function to perform FFT using recursion
void FFTRec(std::vector<Complex>& x)
{
	const int N = x.size();
	if (N <= 1)
	{
		return; // Base case
	}

	// Divide
	std::vector<Complex> even(N / 2);
	std::vector<Complex> odd(N / 2);
	for (int i = 0; i < N / 2; ++i)
	{
		even[i] = x[i * 2];
		odd[i] = x[i * 2 + 1];
	}

	// Conquer
	FFTRec(even);
	FFTRec(odd);

	// Combine	
	for (int i = 0; i < N / 2; ++i)
	{
		Complex t = std::polar(1.0, -2.0 * FT::PI * i / N) * odd[i];
		x[i] = even[i] + t;
		x[i + N / 2] = even[i] - t;
	}
}

std::vector<Complex> FFT(const std::vector<Complex>& x)
{
	std::vector<Complex> X = x;
	FFTRec(X);
	return X;
}

// Function to reverse the bits of an integer
unsigned int reverseBits(unsigned int index, int numOfBits)
{
	unsigned int reversedIndex = 0;

	for (int i = 0; i < numOfBits; ++i)
	{
		// Left shift the reversed number to make room for the next bit
		reversedIndex <<= 1;

		// Extract the rightmost bit from 'num' and set it as the rightmost bit of 'reversedNum'
		reversedIndex |= (index & 1);

		// Right shift 'num' to process the next bit
		index >>= 1;
	}

	return reversedIndex;
}

//Function to reorder data for FFT algorithm using bit reversal
void FFT_BitReversal(std::vector<Complex>& x)
{
	int N = x.size();

	int numOfBits = int(log2(N)); // Assuming N is a power of 2

	unsigned int reversedIndex = 0;

	// Order the data
	for (int index = 0; index < N; ++index)
	{
		reversedIndex = reverseBits(index, numOfBits);

		if (index < reversedIndex)
		{
			std::swap(x[index], x[reversedIndex]);
		}
	}

	// FFT calculation
	for (int s = 1; s < log2(N) + 1; s++)
	{
		double m = pow(2, s);
		Complex omega_m = std::polar(1.0, -2 * FT::PI / m);
		for (int k = 0; k < N; k += m)
		{
			Complex omega = Complex(1, 0);
			for (int j = 0; j < m / 2; ++j)
			{
				Complex t = omega * x[k + j + m / 2];
				Complex u = x[k + j];
				x[k + j] = u + t;
				x[k + j + m / 2] = u - t;
				omega = omega * omega_m;
			}
		}
	}
}

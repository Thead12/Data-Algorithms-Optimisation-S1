#pragma once

//Week 8-9 challange
// Implementation of various fourier transform algorithms

//============== Required includes ============== 
//#include <iostream>
//#include<complex>
//#include<cmath>
//#include<vector>

//Uncomment to remove debug
//#define NDEBUG
//#include<cassert>

namespace FT
{
	const double PI = 3.141592653589793238462643383279502884;
}

bool ensureNyquistCompliance(double f_sampling, double  f_max)
{
	double f_nyquist = f_max * 2.0;
	return f_sampling > f_nyquist;
}

int findIndependentFrequencies(std::complex<double>* X, int N, double threshold)
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

double findDominantFrequency(const std::complex<double>* X, int N, double sampling_rate)
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

void DFT(const std::complex<double>* x, std::complex<double>* X, int N)
{
	for (int k = 0; k < N; ++k)
	{
		X[k] = 0;
		for (int n = 0; n < N; ++n)
		{
			std::complex<double> temp = std::polar(1.0, -2.0 * FT::PI * k * n / N);
			X[k] += x[n] * temp;
		}
	}
}

// Overload of standard DFT for use in FFT algorithm
void DFT(std::vector<std::complex<double>>& x, int N)
{
	//Initialise X array
	std::vector<std::complex<double>> X (N, 0.0);
	for (int k = 0; k < N; ++k)
	{
		for (int n = 0; n < N; ++n)
		{
			std::complex<double> temp = std::polar(1.0, -2.0 * FT::PI * k * n / N);
			X[k] += x[n] * temp;
		}
	}
}

void IDFT(const std::complex<double>* X, std::complex<double>* x, int N)
{
	for (int n = 0; n < N; ++n)
	{
		x[n] = 0;
		for (int k = 0; k < N; ++k)
		{
			std::complex<double> temp = std::polar(1.0, 2.0 * FT::PI * k * n / N);
			x[n] += X[k] * temp;
		}
		x[n] =  x[n].real() / N;
	}
}

// Function to perform FFT
void FFT(std::vector<std::complex<double>>& x) 
{
	const int N = x.size();
	if (N <= 1) 
	{
		return; // Base case
	}

	// Divide
	std::vector<std::complex<double>> even(N / 2);
	std::vector<std::complex<double>> odd(N / 2);
	for (int i = 0; i < N / 2; ++i)
	{
		even[i] = x[i * 2];
		odd[i] = x[i * 2 + 1];
	}

	// Conquer
	FFT(even);
	FFT(odd);

	// Combine	
	for (int i = 0; i < N / 2; ++i) 
	{
		std::complex<double> t = std::polar(1.0, -2.0 * FT::PI *i / N) * odd[i];
		x[i] = even[i] + t;
		x[i + N / 2] = even[i] - t;
	}
}

std::vector<std::complex<double>> calculateFFT(const std::vector<std::complex<double>>& x)
{
	std::vector<std::complex<double>> X = x;
	FFT(X);
	return X;
}

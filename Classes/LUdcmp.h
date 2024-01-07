#pragma once

#include <iostream>
#include<vector>


//Uncomment to remove debug
//#define NDEBUG
#include<cassert>

#include<matrix.h>

namespace LUdcmp
{
	struct LUdcmp
	{
		//Variables
		int n;
		Dense::Matrix<double> lu;	// Stores the decomposition
		std::vector<int> indx;		// Stores the permutation
		double d;					// Used by det

		//Functions
		LUdcmp(Dense::Matrix<double>& a); // Constructor. Argument is the matrix A
		void solve(std::vector<double>& b, std::vector<double>& x); // Solve for the single right-hand side
		void solve(Dense::Matrix<double>& b, Dense::Matrix<double>& x); // Solve for multiple right-hand sides
	};

	// In place LU decomposition algorithm
	LUdcmp::LUdcmp(Dense::Matrix<double>& a) : n(a.getNumRows()), lu(a), indx(n)
	{
		const double TINY = 1.0e-40;// A small number
		int i, imax, j, k;			// Initialising indices
		double big, temp;			// Will be used to store the pivot points
		std::vector<double> vv(n);	// Stores the implicit scaling of each row
		d = 1; // D = 1 as there are no row interchanges yet

		for (int i = 0; i < n; i++) // Loop over rows to get the implicit scaling information
		{
			big = 0;
			for (int j = 0; j < n; j++)
				if ((temp = abs(lu(i, j))) > big) big = temp; // Finds the largest value in the column
			if (big == 0) throw("Singular matrix in LUdcmp"); // Stops algorithm as the matrix is singular
			// else 
			vv[i] = 1 / big; // Save the scaling as there is no nonzero largest element
		}
		for (int k = 0; k < n; k++) // Outermost kij loop
		{
			big = 0; // Initialise search for largest pivot element
			imax = k;

			for (int i = k; i < n; i++)
			{
				temp = vv[i] * abs(lu(i, k)); // Stores scaled value at (i, k) 
				if (big < temp)
				{
					big = temp;	// Sets pivot value
					imax = i;	// Sets index of pivot point
				}
			}

			if (k != imax) // Checks is row swap is necessary
			{
				a.swapRows(imax, k);	// Swaps rows imax and k
				d = -d;					// Change parity of d
				vv[imax] = vv[k];		// Interchange scale factor
			}
			indx[k] = imax;
			if (lu(k, k) == 0) lu(k, k) = 0;
			//if (lu(k, k) == 0) lu(k, k) = TINY;
			for (int i = k + 1; i < n; i++)
			{
				temp = lu(i, k) /= lu(k, k);		// Divide by the pivot element
				for (int j = k + 1; j < n; j++)		// Innermpst loop: reduce remaininf submatrix
					lu(i, j) -= temp * lu(k, j);
			}
		}
	}

	// Solves the set of n linear equations A 8 x = b where b is a vector, and x is the returned solution vector
	void LUdcmp::solve(std::vector<double>& b, std::vector<double>& x)
	{
		int i, ii = 0, ip, j;
		double sum;
		if (b.size() != n || x.size() != n) // Checks if b is a compatible vector
			throw("LUdcmp::solve bad sizes");
		for (int i = 0; i < n; i++) x[i] = b[i]; // Sets x = b
		for (int i = 0; i < n; i++)	// This loop traverses the upper triangular matrix
		{
			ip = indx[i];
			sum = x[ip];
			x[ip] = x[i];
			if (ii != 0)
				for (int j = ii - 1; j < i; j++) sum -= lu(i, j) * x[j]; // Traverse upper triangular columns
			else if (sum != 0)	// Nonzero element encountered
				ii = i + 1;		// So do the sums in the loop above
			x[i] = sum;
		}
		for (int i = n-1; i >= 0; i--) // Now do the back substitution
		{
			sum = x[i];
			for (j = i + 1; j < n; j++) sum -= lu(i, j) * x[j];
			x[i] = sum / lu(i, i);	// Store a component of the solution vector X
		}
	}

	// Solves the set of n linear equations A * X = B where b is a matrix, and X is the returned solution matrix
	void LUdcmp::solve(Dense::Matrix<double>& b, Dense::Matrix<double>& x)
	{
		int i, j, m = b.getNumCols();
		assert(("LUdcmp::solve bad sizes", b.getNumRows() == n && x.getNumRows() == n && b.getNumCols() == x.getNumCols())); // Ensures input matrixes are same size as lu
		std::vector<double> xx(n);
		for (int j = 0; j < m; j++)	// Copy and solve each column in turn
		{
			for (int i = 0; i < n; i++) xx[i] = b(i, j);	// Extract a row and store in x
			solve(xx, xx);									// Use previous solve algorithm
			for (int i = 0; i < n; i++) x(i, j) = xx[i];	// Store output of solve(xx, xx) into solution matrix
		}
	}
}

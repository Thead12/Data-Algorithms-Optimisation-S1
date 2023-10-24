// Week 3 Data and Algorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <array>
#include <chrono>
#include "matrix.h"

//Uncomment to remove debug
//#define NDEBUG
using namespace std;

int main()
{

    vector<vector<double> > arr1 = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };

    vector<vector<double> > arr2 = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };

    int size = 2;

    matrix matrix1(size, size, 4738.3893);

    matrix matrix2(size, size, 3980.1458);


    array<int, 15> v = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    ofstream MyFile("filename.txt");

    for (int i = 1; i <= 15; i++) {

        size = pow(2, i);

        //Start measuring time of divide with initialisation
        auto begin2 = std::chrono::high_resolution_clock::now();
        matrix matrix3 = matrix2.conquer(matrix1);
        //Stop  measuring time
        auto end2 = std::chrono::high_resolution_clock::now();
        //calculate  elapsed time
        auto elapsed2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2);

        MyFile << elapsed2.count() << ", " << size << endl;
        //v[i - 1] = (elapsed2.count() * 1e-9);
        //printf("Time measured for divide and conquer  with initialisation: %.6f seconds.\n", elapsed2.count() * 1e-9);

        
    }
    MyFile.close();

    // write buffer to file
    /*if (std::FILE* f1 = std::fopen("file.txt", "wb"))
    {
        std::fwrite(v.data(), sizeof v[0], v.size(), f1);
        std::fclose(f1);
    }*/

    /*//Start measuring time of naive
    auto begin1 = std::chrono::high_resolution_clock::now();
    matrix3 = matrix2.conquer(matrix1);
    //Stop  measuring time
    auto  end1 = std::chrono::high_resolution_clock::now();
    //calculate  elapsed time
    auto  elapsed1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - begin1);
    printf("Time measured for naive: %.6f seconds.\n", elapsed1.count() * 1e-9);

    //Start measuring time of naive with initialisation
    begin1 = std::chrono::high_resolution_clock::now();
    matrix matrix5 = matrix2.conquer(matrix1);
    //Stop  measuring time
    end1 = std::chrono::high_resolution_clock::now();
    //calculate  elapsed time
    elapsed1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - begin1);
    printf("Time measured for naive with initialisation: %.6f seconds.\n", elapsed1.count() * 1e-9);

    //Start measuring time of divide
    auto begin2 = std::chrono::high_resolution_clock::now();
    matrix4 = matrix2.simpleproduct(matrix1);
    //Stop  measuring time
    auto  end2 = std::chrono::high_resolution_clock::now();
    //calculate  elapsed time
    auto  elapsed2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2);
    printf("Time measured for divide and conquer: %.6f seconds.\n", elapsed2.count() * 1e-9);*/
}

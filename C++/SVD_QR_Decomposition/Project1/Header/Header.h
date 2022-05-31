#ifndef HEADER_
#define HEADER_

#include <vector>
#include <string>
#include<tuple>
#include<iostream>
#include <fstream>
#include <cstdio>		//for remove file operation
#include <random>		//for generate random numbers

//Constants
#define PI 3.14159265358979323846   // pi
#define TOTAL 1.0e-9

using Vector = std::vector<double>;
using Matrix = std::vector<std::vector<double>>;
using namespace std;

/*
my_round check if num is smaller than TOTAL value. If so, then num become zero.
*/
template<typename T>
void my_round(T& num) {
	if (std::abs(num) < TOTAL)
		num = 0;
}

#endif // !HEADER_


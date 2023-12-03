#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;
bool isZero(double x);
bool divison(vector<vector<double>>& matrix, int step);
double maxAbs(vector<double> ar);
void intocheck(vector<vector<double>>& matrix);
void minuss(vector<vector<double>>& matrix, int step, int size);
void lineSwap(vector<vector <double>>& matrix, int step, int size);
void output(vector<vector<double>> const& matrix, int size);
void output(vector<double> const& matrix, int size);
bool triangular(vector<vector<double>>& matrix, int const& numberOfEquations);
void findX(vector<vector<double>> matrix, vector <double>& result, int size);
void findError(vector<vector<double>> const& matrix, vector <double> const& resultX, int size);
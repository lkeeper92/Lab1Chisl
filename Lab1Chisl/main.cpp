//var 8
#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>
#include <limits>
#include "Gaus.h"

using namespace std;

int main()
{
	vector <double> result;
	vector<vector<double>> matrix;
	intocheck(matrix);
	output(matrix, matrix.size());
	findX(matrix, result, matrix.size());
	output(result, matrix.size());
	cout << endl;
	findError(matrix, result, matrix.size());
}
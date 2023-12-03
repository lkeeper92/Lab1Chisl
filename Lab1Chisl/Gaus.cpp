#include "Gaus.h"

using namespace std;
bool isZero(double x) {
	return std::fabs(x) < std::numeric_limits<double>::epsilon();
}
bool divison(vector<vector<double>>& matrix, int step)
{
	double temp = matrix[step][step];
	if (isZero(temp)) return 0;
	for (int j = step; j < matrix[step].size(); j++)
		matrix[step][j] = matrix[step][j] / temp;
	return 1;
}
double maxAbs(vector<double> ar)
{
	double max = 0;
	for (double i : ar)
		if (max < abs(i)) max = abs(i);
	return max;

}
void intocheck(vector<vector<double>>& matrix)
{
	matrix.resize(3);
	matrix[0].push_back(2.31);	matrix[0].push_back(31.49);	matrix[0].push_back(1.52);	matrix[0].push_back(40.95);
	matrix[1].push_back(4.21);	matrix[1].push_back(22.42);	matrix[1].push_back(3.85);	matrix[1].push_back(30.24);
	matrix[2].push_back(3.49);	matrix[2].push_back(4.85);	matrix[2].push_back(28.72);	matrix[2].push_back(42.81);

}
void minuss(vector<vector<double>>& matrix, int step, int size)
{
	for (int i = step + 1; i < size; i++)
	{
		double temp = matrix[i][step];
		for (int j = step; j < matrix[i].size(); j++)
		{
			matrix[i][j] = matrix[i][j] - matrix[step][j] * temp;
		}
	}
}
void lineSwap(vector<vector <double>>& matrix, int step, int size)
{
	double max = 0;
	int position = 0;
	for (int i = step; i < size; i++)
	{
		if (max < abs(matrix[i][step])) {
			max = abs(matrix[i][step]);
			position = i;
		}
	}
	if (step != position) {
		vector<double> temp = matrix[step];
		matrix[step] = matrix[position];
		matrix[position] = temp;
	}
}
void output(vector<vector<double>> const& matrix, int size)
{
	if (size == 0) {
		cout << "Matrix is empty ! ";
		exit(0);
	}
	for (int i = 0; i < size; i++)
	{
		int j;
		cout << "[ ";
		for (j = 0; j < matrix[i].size() - 1; j++)
			cout << setw(12) << matrix[i][j];
		cout << setw(3) << " | " << setw(6) << matrix[i][j] << " ]";
		cout << endl;
	}
	cout << endl;
}
void output(vector<double> const& matrix, int size)
{
	if (size == 0) {
		cout << "Matrix is empty ! ";
		exit(0);
	}
	cout << "{ ";
	for (int i = 0; i < size; i++)
	{
		cout << setprecision(12) << setw(13) << matrix[i] << "  ";
	}
	cout << "} ";
	cout << endl;
	cout << resetiosflags(ios::fixed);
}
bool triangular(vector<vector<double>>& matrix, int const& numberOfEquations)
{
	for (int i = 0; i < numberOfEquations - 1; i++)
	{
		lineSwap(matrix, i, matrix.size());
		if (!divison(matrix, i)) return 0;
		minuss(matrix, i, matrix.size());
	}
	if (!divison(matrix, numberOfEquations - 1)) return 0;
	return 1;
}
void findX(vector<vector<double>> matrix, vector <double>& result, int size)
{
	int numberOfEquations = size;
	if (result.empty()) result.resize(numberOfEquations, 1);
	if (!triangular(matrix, numberOfEquations)) {
		cerr << "Matrix cant been transform in triangular view !!!\n";
		exit(1);
	}
	for (int i = numberOfEquations - 1; i >= 0; i--)
	{
		double temp = matrix[i][numberOfEquations];
		for (int c = numberOfEquations - 1; c > i; c--)
			temp -= matrix[i][c] * result[c];
		result[i] = temp;
	}
}
void findError(vector<vector<double>> const& matrix, vector <double> const& resultX, int size)
{

	if (resultX.empty()) {
		cout << "New B cant be found\n";
		exit(0);
	}
	vector<vector<double>> cloneM = matrix;
	vector <double> resultB;
	resultB.resize(size, 0);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			resultB[i] += (matrix[i][j] * resultX[j]);
	}

	for (int i = 0; i < size; i++)
		cloneM[i][size] = resultB[i];

	output(cloneM, cloneM.size());
	vector<double> resultX_2;
	findX(cloneM, resultX_2, cloneM.size());
	vector<double> norm;
	norm.resize(3, 0);
	double error = 0;

	for (int i = 0; i < size; i++)
		norm[i] = resultX_2[i] - resultX[i]; //вычисление числителя для расчёта погрешности

	error = maxAbs(norm) / maxAbs(resultX);

	for (int i = 0; i < size; i++)
		resultB[i] = matrix[i][size] - resultB[i];

	cout << "Residual vector : ";		//вектор невязки
	output(resultB, size);
	cout << "Norm : " << maxAbs(resultB) << endl; // норма
	cout << "Relative error : " << error; //относительная погрешность	
}
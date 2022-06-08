#include "stdafx.h"
#include "conio.h"
#include <iostream>
#include "string"
#include <vector>
#include <math.h>
#include <D:\My_files\c_cpp\VisualStudio\Half_year_2\Laborathory_4\test_lib\matrix.h>

//do not forget test_lib.dll !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

using namespace std;

double Polinom(double x, const matrix &coeff)
{
	double y = 0;

	for (int i = 0; i < coeff.n; ++i)
	{
		y = y + coeff.arr[i][0] * pow(x, i);
	}

	return y;
}


int main(void)
{
	//get x and y to x.txt and y.txt *******************************************************************
	int i = 0, j = 0;
	int n, m;

	//n = 10;
	n = 11;
	m = 4;

	vector<double> x_initial(n);
	vector<double> y_initial(n);

	x_initial[0] = -2.07;
	x_initial[1] = -1.31;
	x_initial[2] = -0.69;
	x_initial[3] = 0.27;
	x_initial[4] = 0.69;
	x_initial[5] = 1.00;
	x_initial[6] = 1.36;
	x_initial[7] = 1.76;
	x_initial[8] = 2.52;
	x_initial[9] = 3.46;
	x_initial[10] = 3.74;

	y_initial[0] = 17.54;
	y_initial[1] = 13.00;
	y_initial[2] = 10.10;
	y_initial[3] = 5.93;
	y_initial[4] = 4.41;
	y_initial[5] = 3.20;
	y_initial[6] = 1.56;
	y_initial[7] = 0.03;
	y_initial[8] = -2.50;
	y_initial[9] = -6.51;
	y_initial[10] = -7.59;

	matrix Y_initial(y_initial, false);
	matrix X_initial(x_initial);


	cout << "test \n";

	X_initial.print();
	Y_initial.print();

	/*cout << "enter n = ";
	cin >> n;

	cout << "\n";

	cout << "enter m = ";
	cin >> m;*/

	/*FILE * xxx;
	xxx = fopen("x_initial.txt", "w");

	for (int i = 0; i < (n+1); ++i)
	{
		fprintf(xxx, "%lf ", x_initial[i]);
	}
	fclose(xxx);

	FILE * yyy;
	yyy = fopen("y_initial.txt", "w");

	for (int i = 0; i < (n + 1); ++i)
	{
		fprintf(yyy, "%lf ", y_initial[i]);
	}
	fclose(yyy);*/

	//********create matrix X in the file matrix_x.txt ***********************************************************

	FILE * matrix_x;
	matrix_x = fopen("matrix_x.txt", "w");
	fprintf(matrix_x, "%d %d\n", n, m);

	double element;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			element = pow(x_initial[i], j); 
			fprintf(matrix_x, "%lf ", element);
		}
		fprintf(matrix_x, " \n");
	}
	fclose(matrix_x);
	//*****************************************************************************************************

	matrix X, X_transposed, X_inverted, X_temp;

	X.read_data("matrix_x.txt");

	cout << "X: \n";
	cout << "rows = " << X.n << " columns = " << X.m << "\n";
	X.print();

	//cout << "matrix X:" << endl;
	//X.print();

	X_transposed = X.transpose();

	cout << "X_transposed: \n";
	cout << "rows = " << X_transposed.n << " columns = " << X_transposed.m << "\n";
	X_transposed.print();

	X_temp = multiply(X_transposed, X);//1 = (X_transposed * X);
	cout << "X_temp (after 1st multyplying): \n";
	cout << "rows = " << X_temp.n << " columns = " << X_temp.m << "\n";
	X_temp.print();


	X_temp = invert(X_temp);//2 = 1.invert;
	cout << "X_temp (after inverting itself): \n";
	cout << "rows = " << X_temp.n << " columns = " << X_temp.m << "\n";
	X_temp.print();





	X_temp = multiply(X_temp, X_transposed);//3 = 2 * X_transposed;
	cout << "X_temp (after multiplying on X_transposed): \n";
	cout << "rows = " << X_temp.n << " columns = " << X_temp.m << "\n";
	X_temp.print();


	cout << "PROBLEM INCOMING! \n";
	cout << "X_temp : \n";
	cout << "rows = " << X_temp.n << " columns = " << X_temp.m << "\n";
	cout << "Y_initial : \n";
	cout << "rows = " << Y_initial.n << " columns = " << Y_initial.m << "\n";

	/*matrix Y_initial_invert;
	Y_initial_invert = */


	X_temp = multiply(X_temp, Y_initial);//4 = 3 * Y_initial;
	cout << "X_temp (after multiplying on Y_initial): \n";
	cout << "rows = " << X_temp.n << " columns = " << X_temp.m << "\n";
	X_temp.print();


	cout << "Result: \n";
	X_temp.print();

	//count vector "a" (it will be the answer) *************************************************************

	/*(X_transposed * X).invert * X_transposed * y*/

	//X_transposed = X.transpose();

	//CHECKING THE RESULT

	for (i = 0; i < n; ++i)
	{
		printf("x: %15.6lf ", x_initial[i]);

		double y = 0;
		y = Polinom(x_initial[i], X_temp);
		printf("y initial: %15.6lf ; y counted: %15.6lf , delta = %e \n",y_initial[i], y, fabs(y - y_initial[i]));

	}




	int h;
	cout << "end of programm";
	cin >> h;
}
#include "stdafx.h"
#include "conio.h"
#include <iostream>
#include "string"
#include <vector>
#include <math.h>
#include <D:\My_files\c_cpp\VisualStudio\Half_year_2\Laborathory_4\test_lib\matrix.h>

//do not forget test_lib.dll !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

using namespace std;

double function(const vector<double> &x)// returns value of function in certain point (point == vector x)
{
	return pow(7 - x[0], 2) + pow(1 + x[1], 4) + fabs(x[2] - 3);
}

double diff(const vector<double> &x, int i, double delta) // returns partial derivative by certain variable in certain point
{
	vector<double> x_help = x;

	x_help[i] = x[i] + delta;

	return (function(x_help) - function(x)) / delta;
}

vector<double> gradient(const vector<double> &x) // returns a gradient (vector) of function in certain point (point == vector x)
{
	vector<double> grad(x.size());

	double delta = 0.0001;

	for (size_t i = 0; i < x.size(); ++i)
	{
		grad[i] = diff(x, i, delta);
	}

	return grad;
}

void method_gradient(vector<double> &x, double h, double K, double eps)
{
	double delta = 0.0001;
	double f_old = function(x);

	vector<double> x_new = x;
	double f_new;

	while (h >= eps)
	{
		// normal vector
		double sum = 0;
		for (size_t i = 0; i < x.size(); i++)
		{
			sum += pow(diff(x, i, delta), 2);
		}
		double len = sqrt(sum);

		vector<double> dir = x;
		for (size_t i = 0; i < x.size(); ++i)
		{
			dir[i] = diff(x, i, delta) / len;
		}

		for (size_t i = 0; i < x.size(); ++i)// making step in choosen direction
		{
			x_new[i] = x[i] - dir[i] * h;
		}

		f_new = function(x_new);
		if (f_new < f_old)//better in choosen Direction
		{
			f_old = f_new;
			x = x_new;
			//and repeating the algorythm
		}
		else//worse in choosen Direction
		{
			h = h / K;
			printf("h = %lf \n", h);
		}
	}

	printf("end of process\n");
	printf("minimum = %lf\n", f_old);
	for (size_t i = 0; i < x.size(); ++i)
	{
		printf("x%d: %lf\n", i, x[i]);
	}

}

int main(void)
{
	double eps = 0.1;
	double K = 2.0;
	double h = 2.0;
	double delta = 0.0001;

	vector<double> x(3);// initial point
	x[0] = 0;
	x[1] = 0;
	x[2] = 0;

	method_gradient(x, h, K, eps);

	printf("END OF PROGRAMM \n");
	int z;
	cin >> z;
}
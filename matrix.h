#pragma once

#ifndef TEST_LIB_EXPORTS
   #define PASHA_LIB_EXPORT __declspec(dllimport)
#else
   #define PASHA_LIB_EXPORT __declspec(dllexport)
#endif

#include <vector>
using namespace std;
class PASHA_LIB_EXPORT matrix
{
public:
	int n;
	int m;
	vector< vector<double> > arr;

	matrix();
	matrix(const vector<double> &a, bool row = true);
	

	void print();
	void resize(int row, int column);
	bool read_data(const char * name);
	double trace() const;
	//double det() const;
	matrix transpose();
	
	PASHA_LIB_EXPORT friend matrix invert(const matrix &a);
	PASHA_LIB_EXPORT friend bool compare(const matrix &a, const matrix &b);
	PASHA_LIB_EXPORT friend matrix multiply(const matrix &a, const matrix &b);
	PASHA_LIB_EXPORT friend matrix multiply(const matrix &a, const vector<double> &b);
	PASHA_LIB_EXPORT friend matrix multiply(const matrix &a, double x);
	PASHA_LIB_EXPORT friend double deltatrace(const matrix &a, int delta);
};

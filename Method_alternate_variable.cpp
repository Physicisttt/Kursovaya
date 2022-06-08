#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

#define N 3
#define M 19.0 

double Func(double x[N], double opttype)
{
	//return (7 - x1)^2 + (1 + x2)^4 + |x3 - 3| from lection

	//return pow((7 - x[0]), 2) + pow((1 + x[1]), 4) + fabs(x[2] - 3);

	return opttype * (-1) * (
		             pow(-1,M) * ( 
						           fabs(M*x[0] + 1)      +      pow((5 / M) - 4 * x[1], 2)     +      pow(M / 50 - x[2], 4)
						         )
		          );
}

int NewNum(int currnum) //makes new number for variable to modify
{
	if (currnum < (N-1))
	{
		return ++currnum;
	}
	else
	{
		return currnum = 0;
	}
}

void NewDeltaArr(double deltaarr[N], int currnum, double delta, int direction)
{
	deltaarr[currnum] = delta * direction;
}

void CleanDeltaArr(double deltaarr[N], int currnum)
{
	deltaarr[currnum] = 0;
}

void VectorSum(double v1[N], double v2[N], double res[N])
{
	for (int i = 0; i < N; i++)
	{
		res[i] = v1[i] + v2[i];
	}
}

double FindMin(double a, double b)
{
	if (a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

/*double DetermType(double xvector[N], double delta)// IN: base initial X Vector, delta. OUT: min or max optimization
{
	double fpoints[N*2], deltaarr[N], x_minus[N], x_plus[N];
	int direction;
	double InitialFunc;

	InitialFunc = Func(xvector);

	for (int i = 0; i < N; i++)
	{
		deltaarr[i] = 0;
	}

	for (int i = 0; i < N; i++)
	{
		direction = 1;

		NewDeltaArr(deltaarr, i, delta, direction);
		VectorSum(xvector, deltaarr, x_plus);
		fpoints[2*i - 1] = Func(x_plus);
		CleanDeltaArr(deltaarr, i);

		//////////////////////////////

		direction = -1;

		NewDeltaArr(deltaarr, i, delta, direction);
		VectorSum(xvector, deltaarr, x_minus);
		fpoints[2*i] = Func(x_minus);
		CleanDeltaArr(deltaarr, i);

	}

	int imin = 0;
	double min = InitialFunc;
	int imax = 0;
	double max = InitialFunc;
	for (int i = 0; i < N*2; i++)
	{
		//find min and max in array of the many many numbers in the world of happy people living there for ages of empire
		if (fpoints[i] < min)
		{
			min = fpoints[i];
			imin = i;
		}

		if (fpoints[i] > max)
		{
			max = fpoints[i];
			imax = i;
		}
	}
	// max - maximum step from the initial point
	// min - minimum step from the initial point

	if ((min < InitialFunc) || (max > InitialFunc))
	{
		if ( fabs(min) > fabs(max) )
		{
			//minimization
			cout << endl << "determined type - minimization" << endl;
			return 1;
		}
		else
		{
			//maximization
			cout << endl << "determined type - maximization" << endl;
			return -1;
		}
	}
	else //not success
	{
		cout << endl << "error: cannot determine type" << endl;
		return 0;
	}

	//return 1 - minimization
	//return -1 - maximization
}*/


int main(void)
{
//	double x1, x2, x3;
	int K, res, direction, mode, NotSuccessCount, currnum, SuccessCount = 0;
	double h, eps, /*f1, f2, fdefault,*/ F, F_plus, F_minus, F_mod, opttype;
	double xarr[N], yarr[N], modxarr[N], xarr_plus[N], xarr_minus[N], deltaarr[N], ResultXArr[N];
//	double fdefault, fdeltaplus, fdeltaminus;
//	bool success;

	K = 2;
	h = 0.02;
	eps = 0.00001;
	
	for (int i = 0; i < N; i++)
	{
		deltaarr[i] = 0;
	}

	/*for (int i = 0; i < N; i++) //must be
	{
		cin >> xarr[i];
	}*/

	for (int i = 0; i < N; i++) //initial xarr
	{
		xarr[i] = 0;
	}

	//success = true;
	
	currnum = 0;
	NotSuccessCount = 0;
	mode = 1;
	opttype = 1;

	cout << "select optimization type (default: minimization)" << endl;
	cout << "enter 1 if minimization, -1 if maximization " << endl;
	cin >> opttype;
	if (opttype == 1)
	{
		cout << "selected: minimization" << endl;
	}
	else
	{
		cout << "selected: maximization" << endl;
	}

	//opttype = DetermType(xarr, h);

	/*while (eps <= h)
	{
		currnum = NewNum(currnum); // this variable will be modified

		NewDeltaArr(deltaarr, currnum, h, 1);
		VectorSum(modxarr_plus, deltaarr);// then function(modxarr)
		F_plus = Func(modxarr_plus);

		CleanDeltaArr(deltaarr, currnum);

		NewDeltaArr(deltaarr, currnum, h, -1);
		VectorSum(modxarr_minus, deltaarr);// then function(modxarr)
		F_minus = Func(modxarr_minus);

		Func(xarr);

		//need to clean modxarr_plus and modxarr_minus for future

		//so we have F, F_plus, F_minus

		if ((F_plus < F) || (F_minus < F))
		{
			//success
			if (F_plus < F_minus)
			{
				direction = 1;
			}
			else
			{
				direction = -1;
			}
		}
		else
		{
			success = false;
		}
	}//while eps*/

	while (h > eps)
	{
		if (mode == 1)// diagonal ////////////////////////////////////////////////////////
		{

			NewDeltaArr(deltaarr, currnum, h, 1);
			VectorSum(xarr, deltaarr, xarr_plus);// then function(modxarr)
			F_plus = Func(xarr_plus, opttype);
			CleanDeltaArr(deltaarr, currnum);

			NewDeltaArr(deltaarr, currnum, h, -1);
			VectorSum(xarr, deltaarr, xarr_minus);// then function(modxarr)
			F_minus = Func(xarr_minus, opttype);
			CleanDeltaArr(deltaarr, currnum);

			F = Func(xarr, opttype);

			//need to clean xarr_plus and xarr_minus for future

			//so we have F, F_plus, F_minus

			if ((F_plus < F) || (F_minus < F))
			{
				//success
				mode = 2;
				SuccessCount = 0;
				if (F_plus < F_minus)
				{
					direction = 1;
				}
				else
				{
					direction = -1;
				}
			}
			else // not success
			{
				NotSuccessCount++;
				currnum = NewNum(currnum); // this variable will be modified
				if (NotSuccessCount >= N)
				{
					h = h / K;
					NotSuccessCount = 0;
					for (int i = 0; i < N; i++)//saving result
					{
						ResultXArr[i] = xarr[i];
					}
				}
			}
		}///////////////////////////////////////////////////////////////////////

		if (mode == 2)//vertical
		{
			NewDeltaArr(deltaarr, currnum, h, direction);
			VectorSum(xarr, deltaarr, modxarr);// then function(modxarr)
			CleanDeltaArr(deltaarr, currnum);

			F = Func(xarr, opttype);
			F_mod = Func(modxarr, opttype);

			if (F_mod < F)
			{
				//success
				SuccessCount++;
				for (int i = 0; i < N; i++)
				{
					xarr[i] = modxarr[i];
				}
			}
			else 
			{
				//not success
				mode = 1;
				currnum = NewNum(currnum);
			}

			if (SuccessCount >= 20)
			{
				cout << "SEEMS TO BE INFINITE DIRECTION!!!";
				break;
			}
		}
	}



	int stop;
	cout << "now it is finish." << endl;
	
	cout << "h = " << h << endl << "F = " << F << endl;

	for (int i = 0; i < N; i++)
	{
		cout << "x" << i << "  = " << ResultXArr[i] << ";" << endl;
	}
	cout << "finita";
	cin >> stop;
}//end.



























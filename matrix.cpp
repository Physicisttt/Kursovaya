#include "matrix.h"
#include <vector>
#include <algorithm>

void matrix::print()
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			printf("%13.6lf  ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

// c.resize(n,m);
void matrix::resize(int row, int column)
{
	n = row;
	m = column;
	arr.resize(n);
	for (int k = 0; k < n; k++)
	{
		arr[k].resize(m);
	}
}

bool matrix::read_data(const char * name)
{
	int i, j;
	FILE* f4;

	f4 = fopen(name, "r");
	if (f4 == NULL)
	{
		printf("\nERROR: FILE NOT OPEN\n");
		return false;
	}

	fscanf(f4, "%d %d", &(this->n), &(this->m));

	if ((n <= 0) || (m <= 0))
	{
		printf("invalid parameters for matrix size\n");
		return false;
	}

	resize(n, m);

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			fscanf(f4, "%lf", &arr[i][j]);
		}
	}
	fclose(f4);
	return true;
}

double matrix::trace() const
{
	int i;
	double sum = 0;

	int k = min(n, m);

	for (i = 0; i < k; i++)
	{
		sum += arr[i][i];
	}
	
	return sum;
}

double deltatrace(const matrix &a, int delta)
{
	int k;
	double sum = 0;

	if (delta == 0) // D
	{
		return a.trace();
	}

	if (delta > 0) // U
	{
		for (k = 0; k < (a.n - delta); k++)
		{
			//i = k;
			//j = k + delta;
			sum += a.arr[k][k + delta];
		}

		return sum;
	}


	delta *= -1;
	for (k = 0; k < (a.n - delta); k++)
	{
		//i = k + delta;
		//j = k;
		sum += a.arr[k + delta][k];
	}
	return sum;
}


matrix::matrix()//default constructor
{
	n = 0;
	m = 0;
}

matrix::matrix(const vector<double> &a, bool row)
{
	int len = a.size();
	int n, m;
	
	if (row)
	{
		n = 1;
		m = len;
		resize(n, m);

		for (int j = 0; j < m; ++j)
		{
			arr[0][j] = a[j];
		}
	}
	else
	{
		n = len;
		m = 1;
		resize(n, m);


		for (int j = 0; j < n; ++j)
		{
			arr[j][0] = a[j];
		}
	}
	
	
	
}




/*double matrix::det() const
{

}*/

matrix matrix::transpose()
{
	int i, j;
	matrix c;

	c.resize(m, n);

	printf("transpose matrix: \n");

	for (j = 0; j < m; j++)
	{
		for (i = 0; i < n; i++)
		{
			printf("%6lf ", arr[i][j]);
			c.arr[j][i] = arr[i][j];
			
		}
		printf("\n");
	}

	/*printf("\n");
	printf("new matrix:\n");
	c.print();*/
	
	return c;


}

bool compare(const matrix &a, const matrix &b)
{
	int i, j;

	if ((a.n != b.n) || (a.m != b.m))
	{
		return false;
	}

	for (i = 0; i < a.n; i++)
	{
		for (j = 0; j < a.m; j++)
		{
			if (a.arr[i][j] != b.arr[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

matrix multiply(const matrix &a, double x)
{
	int i,j;
	matrix c;

	c.resize(a.n, a.m);

	for (i = 0; i < a.n; i++)
	{
		for (j = 0; j < a.m; j++)
		{
			c.arr[i][j] = a.arr[i][j] * x;
		}
	}

	return c;
}

/*matrix multiply(const matrix &a, const vector<double> &b);
{
	int i, j, r;
	matrix c;


	
	if (a == matrix && b == vector) OR (a == vector && b == matrix)
	{
		if (a == matrix && b == vector)
		{
			//algorithm
		}

		if (a == vector && b == matrix)
		{
			//algorithm
		}
	}
	

	if (((a.n == 1) && (a.m > 1)) || ((a.n > 1) && (a.m == 1))) //if a == vector
	{
		if (((a.n == 1) && (a.m > 1)))
		{
			;
		}

		if (((a.n > 1) && (a.m == 1)))
		{
			;
		}
	}

	if (((b.n == 1) && (b.m > 1)) || ((b.n > 1) && (b.m == 1))) //if b == vector
	{
		if (((a.n == 1) && (a.m > 1)))
		{
			;
		}

		if (((a.n > 1) && (a.m == 1)))
		{
			;
		}
	}
}*/


matrix multiply(const matrix &a, const matrix &b)
{
	int i, j, r;
	matrix c;

	c.resize(a.n, b.m);
	// AxB * CxD => AxD & B=C
	// 4x11 * 1*11 => 4x11 & 11=1
	// 4x11 * 11*1 => 4x1 & 11=11

	if (a.m != b.n) //columns in 1st matrix must be equal to rows in 2nd matrix
	{
		printf("invalid matrix size for multiplying!\n");
		return c;
	}

	for (i = 0; i < a.n; i++)//i
	{
		for (j = 0; j < b.m; j++)//j
		{
			c.arr[i][j] = 0;
			for (r = 0; r < a.m; r++)//r
			{
				c.arr[i][j] += a.arr[i][r] * b.arr[r][j];
			}
		}
	}

	return c;
}

matrix invert(const matrix &a)
{
	double eps1 = 0.00001;
	double eps2 = 10000;

	matrix result_matrix;
	result_matrix.resize(a.n, a.m);
	int i, j;

	if (a.n != a.m)//check for invalid matrix
	{
		printf("Invalid matrix! \n");
		return a; // break?
	}

	matrix help;
	help.resize(a.n, (a.m) * 2);
	
	for (i = 0; i < a.n; ++i) //fill the left part of help matrix
	{
		for (j = 0; j < a.m; ++j)
		{
			help.arr[i][j] = a.arr[i][j];
		}
	}

	for (i = 0; i < a.n; ++i) //fill the right part of help matrix
	{
		for (j = 0; j < a.m; ++j)
		{
			if (i != j)
			{
				help.arr[i][j + a.m] = 0;
			}
			else
			{
				help.arr[i][j + a.m] = 1;
			}
		}
	}

	printf("help matrix after adding right part \n");
	help.print();


	double temp;
	for (i = 0; i < a.n; ++i) // making "1" on : 1st row, 2nd row, 3rd row etc.
	{

		/*printf("\n BEFORE i = %d \n", i);
		help.print();*/

		

		printf("current matrix (BEFORE making *1* ): \n");
		help.print();

		temp = help.arr[i][i];
		//printf("\n temp = %lf, row: %d column: %d \n", temp, i, i);



		/*if (fabs(temp) <= eps1)
		{
		printf("VERY BIG NUMBER FOUND \n");
		printf("this is %lf, it's row: %d column: %d", temp, i, i);
		}*/

		/*if (fabs(temp) >= eps2)
		{
			printf("VERY SMALL NUMBER FOUND \n");
			printf("this is %lf, it's row: %d column: %d", temp, i, i);
			printf("printing help matrix before using it\n");
			help.print();
		}*/

		for (j = 0; j < help.m; ++j) // the process of making "1" in the beginning of the row
		{
			help.arr[i][j] = help.arr[i][j] / temp;
		}

		printf("\n current matrix (AFTER making *1* ): \n");
		help.print();
		

		//printf("used temps in making *0* \n");
		// going through rows, making "0" under/above the "1"
		double temp2;
		for (int k = 0; k < a.n; ++k) 
		{
			temp2 = help.arr[k][i];
			//printf("temp data. row: %d column: %d value: %lf \n", k, i, temp2);
			if (k != i)
			{
				for (j = 0; j < help.m; ++j)
				{

					help.arr[k][j] = help.arr[k][j] - temp2 * help.arr[i][j];
				}
			}
		}

		printf("current matrix (AFTER MAKING *0* ): \n");
		help.print();

		//printf("\n AFTER i = %d \n", i);
		//help.print();

		// getting inverted part
		
	}

	printf("\n Help matrix: \n");
	help.print();

	// getting inverted part
	for (i = 0; i < a.n; ++i) //fill the right part of help matrix
	{
		for (j = 0; j < a.m; ++j)
		{
			result_matrix.arr[i][j] = help.arr[i][j + a.m];
		}
	}
	//printf("\n Result: \n");
	//result_matrix.print();

	return result_matrix;

	//end
}


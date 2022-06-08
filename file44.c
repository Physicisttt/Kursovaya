#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 5
#define M 6
#define E 0.00001


void method_Gauss(double a[N][M], double result[N])
{
	int q = 1;
	while (q>0)
	{
		q = 0;
		for (int i = 0; i < N - 1; i++)
		{
			if (a[i][i] == 0)
			{
				q++;
				for (int j = 0; j < M; j++)
				{
					double c = a[i][j];
					a[i][j] = a[i + 1][j];
					a[i + 1][j] = c;
				}
			}
		}
		if (a[N - 1][N - 1] == 0)
		{
			q++;
			for (int j = 0; j < M; j++)
			{
				double c = a[N - 1][j];
				a[N - 1][j] = a[0][j];
				a[0][j] = c;
			}
		}
	}



	for (int i = 0; i < N; i++)
	{
		double v = a[i][i];
		for (int j = 0; j < M; j++)
		{
			a[i][j] /= v;
		}

		if (i < N - 1)
		{

			for (int j = i + 1; j < N; j++)
			{
				double r = a[j][i];
				for (int y = 0; y < M; y++)
				{
					a[j][y] -= a[i][y] * r;
				}
			}


		}
	}

	for (int i = N - 1; i >= 0; i--)
	{
		result[i] = a[i][M - 1];
		for (int j = i + 1; j < M - 1; j++)
		{
			result[i] -= a[i][j] * result[j];
		}
	}

	/*for (int i = 0; i < N; i++)
	{
		printf("%lf   ", result[i]);
	}*/
}




void method_Gauss_Zeidel(double a[N][M], double result[N])
{
	int q = 1;
	while (q > 0)
	{
		q = 0;
		for (int i = 0; i < N - 1; i++)
		{
			if (a[i][i] == 0)
			{
				q++;
				for (int j = 0; j < M; j++)
				{
					double c = a[i][j];
					a[i][j] = a[i + 1][j];
					a[i + 1][j] = c;
				}
			}
		}
		if (a[N - 1][N - 1] == 0)
		{
			q++;
			for (int j = 0; j < M; j++)
			{
				double c = a[N - 1][j];
				a[N - 1][j] = a[0][j];
				a[0][j] = c;
			}
		}
	}

	double old_r[N];
	double max_error = 1;
	for (int i = 0; i < N; i++)
	{
		old_r[i] = 0;
	}


	while (max_error>E)
	{


		for (int i = 0; i < N; i++)
		{

			result[i] = a[i][M - 1];

			for (int j = 0; j < M - 1; j++)
			{
				if (i > j)
				{
					result[i] -= a[i][j] * result[j];
				}
				else if (i < j)
				{
					result[i] -= a[i][j] * old_r[j];
				}
			}

			result[i] /= a[i][i];

		}



		max_error = fabs((result[0] - old_r[0]) / result[0]);

		for (int i = 0; i < N; i++)
		{
			if (fabs((result[i] - old_r[i]) / result[i]) > max_error)
				max_error = fabs((result[i] - old_r[i]) / result[i]);
		}

		for (int i = 0; i < N; i++)
		{
			old_r[i] = result[i];
		}


	}
}



void read_data(double a[N][M])
{
	int i, j;
	FILE* f4;

	f4 = fopen("data.txt", "r");
	if (f4 == NULL) printf("\nERROR\n");
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			fscanf(f4, "%lf", &a[i][j]);
		}
	}
	fclose(f4);
}


void check(double a[N][M], double result[N])
{
	double res0[N];
	for (int i = 0; i < N; i++)
	{
		res0[i] = 0;
		for (int j = 0; j < N; j++)
		{
			res0[i] += a[i][j] * result[j];
		}
	}

	for (int i = 0; i < N; i++)
	{
		printf("y_exp: %10lf    y_new: %10lf    d_y: %10lf\n", a[i][M - 1], res0[i], fabs(a[i][M - 1] - res0[i]));
	}
}

int main()
{
	int o;
	double a[N][M], result[N];
	read_data(a);
	//method_Gauss_Zeidel(a, result);
	
	method_Gauss(a, result);
	//read_data(a);
	for (int i = 0; i < N; i++)
	{
	printf("%5lf ", result[i]);
	}
	printf("\n");
	check(a, result);
	
	scanf("%d", &o);
}
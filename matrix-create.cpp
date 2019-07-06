#include "pch.h"
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{ 
	// распределение змейкой
  
  /* 
	int n, m;
	cin >> n >> m;
	int a[100][100] = {};
	int b[100][100] = {};
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (i % 2 == 0) {
				a[i][j] = m * i + j + 1;
			}
			else {
				a[i][j] = m * (i + 1) - j;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (a[i][j] != 0) {
				cout << setw(4) << a[i][j];
			}
		}
		cout << endl; 
	}
	*/

	//заполнение по диагоналям

	int n, m, g = 1;
	cin >> n >> m;
	int a[100][100] = {};
	for (int k = 0; k < n + m - 2; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (i + j == k)
				{
					a[i][j] = g;
					g++;
				}
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (a[i][j] > 0) {
				cout << setw(4) << a[i][j];
			}
		}
		cout << endl;
	}
}

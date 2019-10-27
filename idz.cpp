#include<iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Rus");
	int f, x = 1, y = 3, k;
	if ((x * x < y) && (y < 10))
	{
		f = y - x * x;
		k = 1;
	}
	else if ((x * x > y) && (y >= 10))
	{
		f = y * y - x;
		k = 2;
	}
	cout << "Набор значений аргументов функции: " << "x = 1, " << "y = 3" << endl;
	cout << "Номер ветви алгоритма в которой получено значение функции: " << k << endl;
	cout << "Значение функции: " << f;
}

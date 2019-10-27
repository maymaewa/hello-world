#include<iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Rus");
	int f, x, y, k;
	cout << "Введите x\n";
	cin >> x;
	cout << "Введите y\n";
	cin >> y;
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
	else
	{
		k = 3;
	}
	cout << "Набор значений аргументов функции: " << "x = " << x << ", y = " << y << endl;
	if(k == 3)
	{
		cout << "Значение функции не определено";
	}
	else
	{
		cout << "Номер ветви алгоритма в которой получено значение функции: " << k << endl;
		cout << "Значение функции: " << f;
	}
}

#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

void rotate(int a[], unsigned size, int shift)
{
	for (int k = 0; k < shift; k++)
	{
		for (int i = 0; i < size - 1; i++)
		{
			int temp = a[i];
			a[i] = a[i + 1];
			a[i + 1] = temp;
		}
	}
	for (int i = 0; i < size; i++)
	{
		cout << a[i] << " ";
	}
}

//циклический сдвиг

class Human {
public:
	int age;
	int weight;
	string name;
	void print()
	{
		cout << "Name " << name <<
			"\nWeight " << weight <<
			"\nAge " << age;

	}
	Human()
	{
		age = 0;
		name = "";
		weight = 0;
	}
	~Human()
	{

	}
};


class Array {
public:
	int *data;


	Array(int size)
	{
		this->size = size;
		this->data = new int[size];

		for (int i = 0; i < size; i++)
		{
			data[i] = i + 1;
		}
		cout << "Конструктор " << this << endl;
	};
	Array(const Array &other)
	{
		this->data = new int[other.size];

		for (int i = 0; i < other.size; i++)
		{
			this->data[i] = other.data[i];
		}
		cout << "Конструктор копирования " << this << endl;
	}

	~Array() {
		cout << "Деструктор " << this << endl;
		delete[] data;
	};

	private:
		int size;
};


int main()
{
	setlocale(LC_ALL, "ru");
#ifdef DEBUG
	int n = 5;
	int shift = 0;
	cin >> shift;
	int m[5] = { 1, 2, 3, 4, 5 };
	rotate(m, n, shift);
	for (int i = 0; i < n; i++)
	{
		cout << m[i] << " ";
	}
#endif


	Array a(5);
	Array b(a);
}

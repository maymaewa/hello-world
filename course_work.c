#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <conio.h>
#define MAX_SIZE 60

int input_n(int a);
char** input_array(int n, int** len_first);
int new_gets(char* s);
char* input_symb(int n);
void array_output(char** a, int n);
char** array_account(char** a, char** b,int* len, char* s, int n, int k, int* stb);
void result_output(char** b, int n);
char** clear_array(char** a, int n);
int** clear_array_int(int** a, int n);

int main()
{
	setlocale(LC_ALL, "Russian");
	int l = 1,        //переменная, отвечающая за выход из программы
		flag1 = 0,    //переменная, означающая выполенение первого пункта меню
		flagn = 0,    //переменная, означающая введение количества столбцов массива
		flag3 = 0,    //переменная, означающая проведение расчетов
		flags = 0,    //переменная, означающая проведение расчетов
		g = 0,		  //количество строк в результирующем массиве массиве
		k = 0,		  //количество символов-разделителей
		n = 0;        //количество строк в исходном массиве
	char** a = NULL;   //исходный массив
	char** b = NULL;   //результирующий массив
	char* s = NULL;	   //массив-символов разделителей
	int* len = NULL;   //массив длин строк
	printf("Меню:\n1 - ввод данных\n2 - вывод исходного массива\n3 - расчет результата\n4 - вывод результирующего массива\n5 - справка\n0 - выход\n");
	do
	{
		do
		{
			printf("Выберите пункт меню\n");
			scanf_s("%d", &l);
			if ((l < 0) || (l > 5)) printf("Выбран несуществующий пункт меню. \n");
		} while ((l < 0) || (l > 5));
		switch (l)
		{
		case 1:
			if (n != 0)
			{
				flag1 = 0;
				flag3 = 0;
				a = clear_array(a, n);
				free(s);
				s = NULL;
				printf("Если хотите заново ввести количество строк, введите 1\n");
				scanf_s("%d", &flagn);
				if (flagn == 1)
					n = input_n(1);
				printf("Если хотите заново ввести количество символов-разделитетлей, введите 1\n");
				scanf_s("%d", &flagn);
				if (flagn == 1)
					k = input_n(2);
			}
			else
			{
				n = input_n(1);
				k = input_n(2);
				flagn = 1;
			}
			if (((a = input_array(n, &len)) != NULL) && ((s = input_symb(k)) != NULL))
				flag1 = 1;
			else puts("Error at memory allocation!");
			break;
		case 2:
			if (flag1 == 1)
				array_output(a, n);
			else printf("Вы не ввели исходные данные(пункт 1)\n");
			break;
		case 3:
			if (flag1 == 1)
			{
				if (flag3 == 1)
					printf("Вы уже произвели расчет.");
				else
				{
					b = array_account(a, b, len, s, n, k, &g);
					printf("Произведен расчет\n");
					flag3 = 1;
				}
			}
			else printf("Вы еще не ввели исходные данные. Для того, чтобы произвести расчет, введите исходные данные(пункт 1)\n");
			break;
		case 4:
			if (flag3 == 1)
			{
				result_output(b, g);
			}
			else printf("Вы еще не произвели расчет. Для того, чтобы вывести результат, нужно провести расчет(пункт 3)\n");
			break;
		case 0:
			if (flag1 == 1)
				a = clear_array(a, n);
			if (flag3 == 1)
				a = clear_array(b, g);
			break;
		}
	} while (l != 0);
}
int input_n(int a)
{
	int n; //количество строк
	do
	{
		if(a == 1) printf("Введите количество строк(оно должно быть положительным) :\n");
		if(a == 2) printf("Введите количество символов-разделителей(оно должно быть положительным) :\n");
		scanf_s("%d", &n);

		if (n <= 0)
			printf("Неверное число.\n");
	} while (n <= 0);
	return n;
}

char** input_array(int n, int** len_first)
{
	char** a = NULL;
	char s[MAX_SIZE];
	int i, j,   // переменные для организации цикла
		count;  // переменная для очищения памяти
	count = 0;
	int* len = NULL;
	if (((a = (char**)malloc(n * sizeof(char*))) != NULL) && (len = (int*)malloc(n * sizeof(int))) != NULL)
	{
		for (i = 0, count = 0; i < n; i++, count++)
		{
			if (a[i] = (char*)malloc(MAX_SIZE * sizeof(char)))
			{
				printf("Введите %d строку: \n", i + 1);
				if (i == 0) getchar();
				len[i] = new_gets(a[i]);
				printf("Размер %d строки: %d\n", i + 1, len[i]);
			}
			else
			{
				a = clear_array(a, n);
			}
		}
	}
	else
	{
		a = NULL;
		free(a);
	}
	*len_first = len;
	return a;
}
int new_gets(char* s)
{
	char c;
	int i;
	for (i = 0; ((c = getchar()) != '\n') && (i < MAX_SIZE - 1); i++, s++) *s = c;
	*s = '\0';
	if (i == (MAX_SIZE - 1)) puts("Вы ввели максимальное количество символов в строку.");
	return i;
}
void array_output(char** a, int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("Ваша %d строка: %s\n", i+1, a[i]);
}
// Функция ввода массива символов-разделителей
char* input_symb(int n)
{
	char* symb = NULL,
		c;
	int i, j,
		k;
	symb = (char*)malloc((n + 1) * sizeof(char)); 
	if (symb != NULL)
	{
		printf("Построчно введите %d символов разделителей:\n", n);
		//
		for (i = 0; i < n; i++)
		{
			c = getchar();
			k = 1;
			for (j = 0; k && j < i; j++)
				if (c == symb[j])
				{
					puts("Вы уже ввели данный символ-разделитель");
					i--;
					k = 0;
				}
			if (c == '\n')
			{
				i--;
				k = 0;
			}
			if (k)
				symb[i] = c;
		}
		//
		symb[n] = '\0';
	}
	else puts("Memory allocation error.");
	return symb;
}
char** array_account(char** a, char** b, int* len, char* s, int k, int n, int* stb)
{

	int i, //номер строки
		j, //номер символа в строке
		g, //номер символа-разделителя
		h,
		str2 = 0,
		fl1, //нашелся символ-разделитель
		pos,
		word_len_min,
		word_start; //началось слово
	int* word = (int*)malloc(n * sizeof(int)); //массив количества слов в строке
	int** word_len = (int**)malloc(sizeof(int*)); //массив с колонками начало слова и длина слова
	word_len[0] = (int*)malloc(2 * sizeof(int));
	for (i = 0; i < n; i++)
	{
		word[i] = 0;
		word_start = 0;
		pos = 0;
		for(j = 0; j < len[i]; j++)
		{
			fl1 = 0;
			for (g = 0; g < k && !fl1; g++)
			{
				if (a[i][j] == s[g]) fl1 = 1;
			}
			if (!fl1)
			{
				if (!word_start)
				{
					word_len = (int**)realloc(word_len, (word[i] + 1) * sizeof(int*));
					word_len[word[i]] = (int*)malloc(2 * sizeof(int));
					word_len[word[i]][0] = j;
					word_len[word[i]][1] = 1;
					word[i]++;
					word_start = 1;
				}
				else
				{
					word_len[word[i]-1][1]++;
				}
			}
			else
			{
				if (word_start)
				{
					word_start = 0;
				}
			}
		}
		if (word[i] != 0) word_len_min = word_len[0][1];
		printf("Количество слов в %d строке: %d \n", i, word[i]);
		for (j = 0; j < word[i]; j++)
		{
			printf("Начальная позиция слова %d: %d, длина этого слова: %d \n", j+1, word_len[j][0], word_len[j][1]);
			if (word_len_min > word_len[j][1])
			{
				pos = j;
			}
		}
		if(word[i] != 0  && (word[i] % 2 == 1))
		{
			if (str2 == 0)
			{
				str2 = 1;
				b = (char**)malloc(sizeof(char*));
				b[0] = (char*)malloc((len[i] - word_len[pos][1]) * sizeof(char));
				//тут еще создать строку размером соответствующей строки - word_len_min b и скопировать все, кроме того слова
			}
			else//если уже были строки, то реалок
			{
				str2++;
				b = (char**)realloc(b, str2 * sizeof(char*));
				b[str2 - 1] = (char*)malloc((len[i] - word_len[pos][1])* sizeof(char));
			}
			
			for (j = 0, h = 0; j < len[i]; j++)
			{
				if (j < word_len[pos][0] || j >= (word_len[pos][0] + word_len[pos][1]))
				{
					b[str2-1][h] = a[i][j];
					printf("%c", a[i][j]);
					h++;
				}
			}
			printf("\n");
		}
	}
	*stb = str2;
	return b; 
}
void result_output(char** b, int n)
{
	puts("Ваш текст:");
	int i;
	for (i = 0; i < n; i++)
		printf("Ваша %d строка: %s\n", i + 1, b[i]);
}
char** clear_array(char** a, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (a[i] != NULL)
		{
			free(a[i]);
			a[i] = NULL;
		}
	}
	free(a);
	a = NULL;
	return a;
}
int** clear_array_int(int** a, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (a[i] != NULL)
		{
			free(a[i]);
			a[i] = NULL;
		}
	}
	free(a);
	a = NULL;
	return a;
}

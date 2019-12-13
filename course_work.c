#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <conio.h>
#include <errno.h>
#define MAX_SIZE 80

int input_n();
char** input_array(int n, int** len_first);
char** read_text(int n, int** len_first, char* file_name);
int new_gets(char* s);
char* input_symb(int* n);
void symb_output(char* arr);
void array_output(char** a, int n);
char** array_account(char** a, char** b,int* len, char* s, int n, int k, int* stb);
void result_output(char** b, int n);
void result_output_file(char* file_name, char** b, int n);
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
		h = 0,		  //переменная подменю
		i,			  //переменная для организации цикла
		n = 0;        //количество строк в исходном массиве
	char file_name[21]; //название файла
	char* s = NULL;
	char** a = NULL;   //исходный массив
	char** b = NULL;   //результирующий массив
	int* len = NULL;   //массив длин строк
	
	do
	{
		printf("Меню:\n1 - ввод данных\n2 - вывод исходного массива\n3 - расчет результата\n4 - вывод результирующего массива\n5 - справка\n0 - выход\n");
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
				if (flag1)
				{
					a = clear_array(a, n);
					free(s);
					s = NULL;
				}
				printf("Если хотите заново ввести количество строк, введите 1\n");
				scanf_s("%d", &flagn);
				if (flagn == 1)
					n = input_n();
			}
			else
			{
				n = input_n();
				flagn = 1;
			}
			puts("Подменю:");
			puts("1 - ввести через консоль");
			puts("2 - ввести через файл file.txt");
			puts("3 - ввести через другой файл");
			puts("4 - выйти из подменю");
			do
			{
				puts("Выберите способ, которым вы хотите ввести строки");
				scanf_s("%d", &h);
				if ((h < 0) || (h > 4)) printf("Выбран несуществующий пункт меню. \n");
			} while ((h < 0) || (h > 4));
			switch (h)
			{
			case 1:
				if (((a = input_array(n, &len)) != NULL) && ((s = input_symb(&k)) != NULL))
					flag1 = 1;
				else puts("Error at memory allocation!");
				break;
			case 2:
				strcpy(file_name, "file.txt");
				if (((a = read_text(n, &len, file_name)) != NULL) && ((s = input_symb(&k)) != NULL))
					flag1 = 1;
				else puts("Error at memory allocation!");
				break;
			case 3:

				puts("Введите название файла:");
				getchar();
				for(i = 0; i < 8; i++)
				{
					file_name[i] = getchar();
				}
				file_name[i] = '\0';
				if (((a = read_text(n, &len, file_name)) != NULL) && ((s = input_symb(&k)) != NULL))
					flag1 = 1;
				else puts("Error at memory allocation!");
				break;
			case 4:

				break;
			}

		case 2:
			if (flag1 == 1)
			{
				array_output(a, n);
				symb_output(s);
			}
			else printf("Вы не ввели исходные данные(пункт 1)\n");
			break;

		case 3:
			if (flag1 == 1)
			{
				if (flag3 == 1)
					printf("Вы уже произвели расчет.");
				else
				{
					b = array_account(a, b, len, s, k, n, &g);
					printf("Произведен расчет\n");
					flag3 = 1;
				}
			}
			else printf("Вы еще не ввели исходные данные. Для того, чтобы произвести расчет, введите исходные данные(пункт 1)\n");
			break;

		case 4:
			if (flag3 == 1)
			{
				puts("Подменю:");
				puts("1 - вывести через консоль");
				puts("2 - вывести через файл resl.txt");
				puts("3 - вывести через другой файл");
				puts("4 - выйти из подменю");
				do
				{
					puts("Выберите способ, которым вы хотите вывести результат");
					scanf_s("%d", &h);
					if ((h < 0) || (h > 4)) printf("Выбран несуществующий пункт меню. \n");
				} while ((h < 0) || (h > 4));
				switch (h)
				{
				case 1:
					result_output(b, g);
					break;
				case 2:
					strcpy(file_name, "resl.txt");
					result_output_file(file_name, b, g);
					break;
				case 3:
					puts("Введите название файла:");
					getchar();
					for (i = 0; i < 8; i++)
					{
						file_name[i] = getchar();
					}
					file_name[i] = '\0';
					result_output_file(file_name, b, g);
					break;
				case 4:

					break;
				}
			}
			else printf("Вы еще не произвели расчет. Для того, чтобы вывести результат, нужно провести расчет(пункт 3)\n");
			break;

		case 5:
			puts("Данная программа проводит обработку строк, оставляя только");
			puts("строки с нечетным количеством слов. Она удаляет слова, имеющие минимальную длину в строке.");
			break;

		case 0:
			if (flag1 == 1)
				a = clear_array(a, n);
			if (flag3 == 1)
				a = clear_array(b, g);
			break;
		}
		system("pause");
		system("CLS");
	} while (l != 0);
}
//функция для ввода количества строк
int input_n()
{
	int n; //количество строк
	do
	{
		printf("Введите количество строк(оно должно быть положительным) :\n");
		scanf_s("%d", &n);
		if (n <= 0)
			printf("Неверное число.\n");
	} while (n <= 0);
	return n;
}
//функция для ввода строк
char** input_array(int n, int** len_first)
{
	char** a = NULL;
	int i,  // переменные для организации цикла
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
				a = clear_array(a, count);
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
//функция для чтения строк из файла
char** read_text(int n, int** len_first, char* file_name)
{
	int i;
	int* len;
	int count;
	char** a = NULL;
	char str1[MAX_SIZE];
	FILE* df;
	df = fopen(file_name, "r");
	if (df != NULL)
	{
		rewind(df);
		a = (char**)malloc(n * sizeof(char*));
		len = (int*)malloc(n * sizeof(int));
		if ((a != NULL) && (len != NULL))
		{
			for (i = 0, count = 0; i < n; i++)
			{
				a[i] = (char*)malloc(MAX_SIZE * sizeof(char));
				if (a[i] != NULL)
				{
					count++;
					fgets(str1, MAX_SIZE, df);
					len[i] = strlen(str1)-1;
					str1[len[i]] = '\0';
					strcpy(a[i], str1);
				}
				else
				{
					i = n;
					puts("Error at string allocation! Array not completed!");
				}
			}
			*len_first = len;
		}
		else puts("Error at array allocation");
		if (fclose(df) == EOF) perror("Output closing error");
	}
	else perror("Data error");
	return a;
}
//функция для получения новой строки
int new_gets(char* s)
{
	char c;
	int i;
	for (i = 0; ((c = getch()) != '\r')&& (c != '\n') && (i < MAX_SIZE - 1); i++, s++)
	{
		printf("%c", c);
		*s = c;
	}
	puts("\n");
	*s = '\0';
	if (i == MAX_SIZE) puts("Вы ввели максимальное количество символов в строку.");
	return i;
}
//функция для вывода исходных строк
void array_output(char** a, int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("Ваша %d строка: %s\n", i+1, a[i]);
}
//функция для вывода символов-разделителей
void symb_output(char* arr)
{
	int i;
	puts("Массив символов-разделителей:");
	for (i = 0; arr[i] != '\0'; i++)
	{
		printf("'%c' ", arr[i]);
	}
	printf("\n");
}
//функция для ввода символов разделителей
char* input_symb(int* l)
{
	char* symb, //строка символов-разделителей
		c;			   //отдельный символ
	int i,			   //переменная для организации цикла
		j,			   //переменная для организации цикла
		k,			   //переменная, обозначающая, что символ можно добавить в строку
		end,		   //обозначение конца строки
		flag;		   //флаг для добавления буквы в качестве символа-разделителя
	end = 1;
	symb = (char*)malloc(MAX_SIZE * sizeof(char));
	printf("Введите строку символов разделителей:");
	getchar();
	for (i = 0; end; i++)
	{
		c = getch();
		if (i < MAX_SIZE) printf("%c", c);
		else
		{
			printf("Вы не можете ввести больше %d символов разделителей.\n", MAX_SIZE);
			end = 0;
		}
		k = 1;
		if (end)
		{
			for (j = 0; k && (j < i); j++)
				if (c == symb[j])
				{
					i--;
					k = 0;
				}
			if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
			{
				puts("Вы действительно хотите ввести букву в качестве символа-разделителя?");
				puts("Если да, то введите 1");
				scanf_s("%d", &flag);
				if (flag == 1)
					k = 1;
				else
				{
					i--;
					k = 0;
				}
			}
			if (c == '\r')
			{
				i--;
				k = 0;
				end = 0;
				puts("\n");
			}
			if (k)
				symb[i] = c;
		}
	}
	*l = i;
	symb[*l] = '\0';
	symb = (char*)realloc(symb, *l * sizeof(char*));
	return symb;
}
//функция для расчета результата
char** array_account(char** a, char** b, int* len, char* s, int k, int n, int* stb)
{

	int i, //номер строки исходного массива
		j, //номер символа в строке
		g, //номер символа-разделителя
		h, //номер элемента в строке результирующего массива
		str2,// номер строки результирующего массива
		fl1, //нашелся символ-разделитель
		pos, //позиция минимального по длине слова
		word_len_min, //минимальная длина слова в строке
		word_start; //началось слово
	int* word = (int*)malloc(n * sizeof(int)); //массив количества слов в строке
	int** word_len = (int**)malloc(sizeof(int*)); //массив с колонками начало слова и длина слова
	word_len[0] = (int*)malloc(2 * sizeof(int));
	str2 = 0;
	if (word != NULL && word_len != NULL)
	{
		for (i = 0; i < n; i++)
		{
			word[i] = 0;
			word_start = 0;
			pos = 0;
			for (j = 0; j < len[i]; j++)
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
						word_len[word[i] - 1][1]++;
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
			for (j = 0; j < word[i]; j++)
			{
				if (word_len_min > word_len[j][1])
				{
					word_len_min = word_len[j][1];
					pos = j;
				}
			}
			if (word[i] != 0 && (word[i] % 2 == 1))
			{
				if (str2 == 0)
				{
					str2 = 1;
					b = (char**)malloc(sizeof(char*));
					b[0] = (char*)malloc((len[i] - word_len[pos][1]) * sizeof(char));
				}
				else
				{
					str2++;
					b = (char**)realloc(b, str2 * sizeof(char*));
					b[str2 - 1] = (char*)malloc((len[i] - word_len[pos][1] + 1) * sizeof(char));
				}

				for (j = 0, h = 0; j < len[i]; j++)
				{
					if (j < word_len[pos][0] || j >= (word_len[pos][0] + word_len[pos][1]))
					{
						b[str2 - 1][h] = a[i][j];
						h++;
					}
				}
				b[str2 - 1][h] = '\0';
				printf("\n");
			}
		}
		*stb = str2;
	}
	return b; 
}
//функция для вывода результата в консоль
void result_output(char** b, int n)
{
	if (n == 0)
	{
		puts("Нет строк, удовлетворяющих условию.");
	}
	else
	{
		puts("Ваш текст:");
		int i;
		for (i = 0; i < n; i++)
		{
			printf("Ваша %d строка:\n", i + 1);
			printf("%s", b[i]);
			printf("\n");
		}
	}
}
//освобождение памяти из-под массива
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
//вывод результата в файл
void result_output_file(char* file_name, char** b, int n)
{
	int i;
	FILE * outfile;
	if ((outfile = fopen(file_name, "w")) != NULL)
	{
		for (i = 0; i < n; i++)
		{
			fprintf(outfile, "%s", b[i]);
			fprintf(outfile, "\n");
		}
		puts("Результат был записан в нужный файл.");
		if (fclose(outfile) == EOF) perror("Output closing error");
	}
	else perror("Output opening error");
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

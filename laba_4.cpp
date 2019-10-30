#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int main()
{
	setlocale(LC_ALL, "Russian");
	int m, //количество столбцов
		flag, //переменная для организации цикла
		i, j, g, h, // переменные для организации цикла
		n,// количество строк
		count, // переменная для очищения памяти
		** a = NULL,
		** b = NULL;
	bool k; //переменная для обозначения того, что в строке элемениы не убывают
	do
	{
		do
		{
			printf("Введите число столбцов двумерного массива(оно должно быть положительным и не больше 10) :\n");
			scanf_s("%d", &m);

			if ((m <= 0) || (m > 10))
				printf("Неверное число.\n");
		} while ((m <= 0) || (m > 10));

		if ((a = (int**)malloc(1 * sizeof(int*))) != NULL)
		{
			do
			{

				if ((a[0] = (int*)malloc(m * sizeof(int))) != NULL)
				{
					k = false;
					printf("Введите построчно элементы массива. Минимальный положительный элемент из первых %d элементов должен быть по меньше 10 по модулю\n", m);
					scanf_s("%d", &a[0][0]);
					n = abs(a[0][0]);
					do
					{
						for (j = 1; j < m; j++)
						{

							scanf_s("%d", &a[0][j]);
							if (n > abs(a[0][j]))
								n = abs(a[0][j]);
						}
						if (n > 10)
							printf("Невозможно построить массив\n");
					} while (n > 10);

					if ((a = (int**)realloc(a, n * sizeof(int))) != NULL)
					{

						for (i = 1; i < n; i++)
						{
							if ((a[i] = (int*)malloc(m * sizeof(int))) != NULL)
							{
								for (j = 0; j < m; j++)
								{
									scanf_s("%d", &a[i][j]);
								}
							}
							else
							{
								printf("ERROR at rows allocation!\n");
								if (a[i] != NULL)
								{
									free(a[i]);
									a[i] = NULL;
								}
							}
						}

						printf("Ввод прекращен, так как число строк стало равным минимальному по модулю элементу первой сроки. Вы ввели массив:\n");
						for (i = 0; i < n; i++)
						{
							for (j = 0; j < m; j++)
							{
								printf("a[%d][%d] = %d   ", i, j, a[i][j]);
							}
							printf("\n");

						}

						for (i = 0; i < n; i++)
						{
							for (j = 1; j < m; j++)
							{
								if (a[i][j] >= a[i][j - 1])
								{
									k = true;
									j = m;
								}
							}
							if (k)
							{
								for (g = i; g < n - 1; g++)
								{
									for (h = 0; h < m; j++)
									{
										a[g][h] = a[g + 1][h];
									}

								}

								if (((a = (int**)realloc(a, (n - 1) * sizeof(int))) != NULL) && (n != 1))
								{
									i--;
									n--;
									k = false;
								}
								else if (n == 1)
								{
									n--;
									k = true;
									i = n + 1;
									free(a);
									a = NULL;

								}
								else
								{
									i = n;
									printf("ERROR at string allocation!\n");
									for (i = 0; i < n; i++)
									{
										if (a[i] != NULL)
										{
											free(a[i]);
											a[i] = NULL;
										}
									}
								}

							}
						}

						if (n == 0)
							printf("Нет строк с убывающей последовательностью чисел\n");
						if (!k)
						{
							if (n != 0)
							{
								printf("\n Полученный массив:\n");
								if ((b = (int**)malloc(m * sizeof(int*))) != NULL)
								{
									for (i = 0; i < m; i++)
									{
										if ((b[i] = (int*)malloc(n * sizeof(int))) != NULL)
										{
											for (j = 0; j < n; j++)
											{
												b[i][j] = a[j][i];
												printf("a[%d][%d] = %d   ", i, j, b[i][j]);
											}
											printf("\n");
										}
										else
										{
											i = m;
											printf("ERROR at rows allocation B!\n");
											for (i = 0; i < n; i++)
											{
												if (b[i] != NULL)
												{
													free(b[i]);
													b[i] = NULL;
												}
											}
										}

									}
									for (i = 0; i < m; i = i + 1)
									{
										if (b[i] != NULL)
										{
											free(b[i]);
											b[i] = NULL;
										}
									}
									free(b);
									b = NULL;
								}
								else
								{
									printf("ERROR at string allocation B!\n");
									if (b != NULL)
									{
										free(b);
										b = NULL;
									}
								}
							}
							for (i = 0; i < n; i = i + 1)
							{
								if (a[i] != NULL)
								{
									free(a[i]);
									a[i] = NULL;
								}
							}
							free(a);
							a = NULL;
						}
					}
					else
					{
						printf("ERROR at string allocation!\n");
						for (i = 0; i < n; i++)
						{
							if (a[i] != NULL)
							{
								free(a[i]);
								a[i] = NULL;
							}
						}
					}
				}
				else
				{
					printf("ERROR at first string a allocation!\n");
					if (a[0] != NULL)
					{
						free(a[0]);
						a[0] = NULL;
					}
				}
				printf("\nЕсли хотите ввести новый массив с таким же количеством столбцов, введите '1'.\n");
				scanf_s("%d", &flag);
			} while (flag == 1);
			printf("\nЕсли хотите ввести новое количество столбцов, введите '1'.\n");
			scanf_s("%d", &flag);
			for (i = 0; i < m; i = i + 1)
			{
				if (a[i] != NULL)
				{
					free(a[i]);
					a[i] = NULL;
				}
			}
			free(a);
			a = NULL;
		}
		else printf("ERROR at array a allocation!\n");
	} while (flag == 1);
}

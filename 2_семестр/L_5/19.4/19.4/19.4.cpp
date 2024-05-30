//Габдрахманов Е.Н. ПС-21
//Microsoft Visual Studio
//19.4. Спираль (3). 
//Расположить N2  чисел от 1 до N2 в квадрате по спирали.
//Ввод.В единственной строке файла INPUT.TXT задано число N(1 ≤  N ≤ 50).
//Вывод.Выходной файл OUTPUT.TXT содержит N2  чисел  по N  чисел по спирали.
//Пример
//Ввод
//4
//Вывод
//1 2 3 4
//12 13 14 5
//11 16 15 6
//10 9 8 7

#include <iostream>
#include <fstream>;
#include <vector>

void FillMatrix(std::vector<std::vector<int>>& matrix, int N)
{
	int value = 1;
	int minCol = 0;
	int maxCol = N - 1;
	int minRow = 0;
	int maxRow = N - 1;

	while (value <= std::pow(N, 2))
	{
		for (int i = minCol; i <= maxCol; ++i)
		{
			matrix[minRow][i] = value++;
		}
		++minRow;

		for (int i = minRow; i <= maxRow; ++i)
		{
			matrix[i][maxCol] = value++;
		}
		--maxCol;

		for (int i = maxCol; i >= minCol; --i)
		{
			matrix[maxRow][i] = value++;
		}
		--maxRow;

		for (int i = maxRow; i >= minRow; --i)
		{
			matrix[i][minCol] = value++;
		}
		++minCol;
	}
}

int main()
{
	std::ifstream input("INPUT.txt");
	std::ofstream output("OUTPUT.txt");

	int N;
	input >> N;

	std::vector<std::vector<int>> matrix(N, std::vector<int>(N));

	FillMatrix(matrix, N);

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			output << matrix[i][j] << " ";
		}
		output << std::endl;
	}

	return 0;
}
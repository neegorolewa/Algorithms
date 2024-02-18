#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
#include <string>

const int K_MAX = 300;
const int N_MIN = 1;
const int TREE = 1;
const int EMPTY = 0;
const int BORDER = 3;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::string inputFileName;
	std::cout << "Введите файл: ";
	std::cin >> inputFileName;
	std::ifstream input;
	input.open(inputFileName);

	if (!input.is_open()) {
		std::cout << "Failed to open '" << inputFileName << "' for reading\n";
		return 1;
	}

	int lines, columns;
	input >> lines >> columns;

	std::vector<std::vector<int>> field(lines, std::vector<int>(columns));

	// считывание файла
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			char ch;
			input >> ch;
			if (ch == '0' && (i == 0 || i == lines - 1)) field[i][j] = BORDER;
			if (ch == '0' && (j == 0 || j == columns - 1)) field[i][j] = BORDER;
			if (ch == '1') field[i][j] = 1;
		}
	}

	// вывод поля
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			std::cout << field[i][j];
		}
		std::cout << '\n';
	}

	// подсчет заборов (пока не работает)
	int count = 0;
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (field[i][j] == TREE)
			{
				if (i == 0 || field[i - 1][j] == EMPTY) count++; // check North
				if (i == lines - 1 || field[i + 1][j] == EMPTY) count++; // check South
				if (j == 0 || field[i][j - 1] == EMPTY) count++; // check West
				if (j == columns - 1 || field[i][j + 1] == EMPTY) count++; // check East
			}
		}
	}

	std::cout << count << '\n';
	

    return 0;
}


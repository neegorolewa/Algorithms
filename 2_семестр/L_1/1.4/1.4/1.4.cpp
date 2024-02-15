#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
#include <string>

const int K_MAX = 300;
const int N_MIN = 1;
const int TREE = 1;
const int EMPTY = 0;

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

	std::vector<std::vector<int>> field(lines, std::vector<int>(columns, 0));

	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			char ch;
			input >> ch;
			field[i][j] = ch - '0';
			std::cout << field[i][j];
		}
		std::cout << '\n';
	}

	auto val = 0;
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (field[i][j] == 1) {
				if (i == 0 || field[i - 1][j] == 0) val++;
				if (i == lines - 1 || field[i + 1][j] == 0) val++;
				if (j == 0 || field[i][j - 1] == 0) val++;
				if (j == columns - 1 || field[i][j + 1]) val++;
			}
		}
	}

	std::cout << val << '\n';

    return 0;
}


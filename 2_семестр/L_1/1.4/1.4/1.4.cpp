#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
#include <string>

const int K_MAX = 300;
const int N_MIN = 1;
const char TREE = '1';
const char EMPTY = '0';
const char BORDER = '#';
const char PASSED = '.';

struct Coord {
	int x;
	int y;
};

void changeMarker(std::vector<Coord>& stack, std::vector<std::vector<char>>& field, Coord& pos, char changeCh)
{
	while (!stack.empty())
	{
		pos = stack.back();
		stack.pop_back();
		field[pos.x][pos.y] = changeCh;
	}
}

void checkEmptyPlace(std::vector<Coord>& stack, std::vector<std::vector<char>>& field, int i, int j, Coord& pos)
{
	pos.x = i;
	pos.y = j;
	if (field[i][j] != BORDER && field[i][j] != TREE)
	{
		stack.push_back(pos);
		field[i][j] = PASSED;
	}
	if (field[i][j] == BORDER)
	{
		changeMarker(stack, field, pos, BORDER);
	}
	checkEmptyPlace(stack, field, i + 1, j, pos);
	checkEmptyPlace(stack, field, i - 1, j, pos);
	checkEmptyPlace(stack, field, i, j + 1, pos);
	checkEmptyPlace(stack, field, i, j - 1, pos);
}

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

	std::vector<Coord> memory;
	std::vector<std::vector<char>> field(lines, std::vector<char>(columns));

	// считывание файла
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			char ch;
			input >> ch;
			if ((ch == EMPTY) && ((j == 0 || j == columns - 1) || (i == 0 || i == lines - 1)))
			{
				field[i][j] = BORDER;
			} 
			else
			{
				field[i][j] = EMPTY;
			}
			if (ch == TREE)
			{
				field[i][j] = TREE;
			}
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

	Coord pos;

	for (int i = 1; i < lines - 1; i++)
	{
		for (int j = 1; j < columns - 1; j++)
		{
			if (field[i][j] == EMPTY) 
			{
				checkEmptyPlace(memory, field, i, j, pos);
			}
			else
			{
				continue;
			}
			

		}
	}

	// подсчет заборов (пока не работает)
	//int count = 0;
	//for (int i = 0; i < lines; i++)
	//{
	//	for (int j = 0; j < columns; j++)
	//	{
	//		if (field[i][j] == TREE)
	//		{
	//			if (i == 0 || field[i - 1][j] == EMPTY) count++; // check North
	//			if (i == lines - 1 || field[i + 1][j] == EMPTY) count++; // check South
	//			if (j == 0 || field[i][j - 1] == EMPTY) count++; // check West
	//			if (j == columns - 1 || field[i][j + 1] == EMPTY) count++; // check East
	//		}
	//	}
	//}

	//std::cout << count << '\n';
	

    return 0;
}


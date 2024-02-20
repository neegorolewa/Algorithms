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
const std::string IN_FILE = "input4.txt";
 
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

void checkEmptyPlace(std::vector<Coord>& stack, std::vector<std::vector<char>>& field, int i, int j, Coord& pos, bool& flag)
{
	pos.x = i;
	pos.y = j;
	if (field[i][j] == EMPTY)
	{
		stack.push_back(pos);
		field[i][j] = PASSED;
	}
	if (field[i][j] == BORDER)
	{
		changeMarker(stack, field, pos, BORDER);
		flag = true;
		return;
	}
	if (field[i][j] == TREE)
	{
		if (!flag)
		{
			changeMarker(stack, field, pos, TREE);
		}
		return;
	}
	checkEmptyPlace(stack, field, i + 1, j, pos, flag);
	checkEmptyPlace(stack, field, i - 1, j, pos, flag);
	checkEmptyPlace(stack, field, i, j + 1, pos, flag);
	checkEmptyPlace(stack, field, i, j - 1, pos, flag);
}

int countFenceBlock(std::vector<std::vector<char>>& field, int& lines, int& columns)
{
	 // подсчет заборов (пока не работает)
	int count = 0;
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (field[i][j] == TREE)
			{
				if (i == 0 || field[i - 1][j] == BORDER) count++; // check North
				if (i == lines - 1 || field[i + 1][j] == BORDER) count++; // check South
				if (j == 0 || field[i][j - 1] == BORDER) count++; // check West
				if (j == columns - 1 || field[i][j + 1] == BORDER) count++; // check East
			}
		}
	}

	return count;
}

int main()
{
	std::ifstream input(IN_FILE);

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

	Coord pos;

	// Обход поля для нулей
	for (int i = 1; i < lines - 1; i++)
	{
		for (int j = 1; j < columns - 1; j++)
		{
			if (field[i][j] == EMPTY) 
			{
				bool isBorder = false;
				checkEmptyPlace(memory, field, i, j, pos, isBorder);
			}
			else
			{
				continue;
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

	int count = countFenceBlock(field, lines, columns);
	std::cout << count << '\n';
	
    return 0;
}


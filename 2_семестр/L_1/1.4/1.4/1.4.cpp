// Габдрахманов Е.Н. ПС-21
// Microsoft Visual Studio 2022
// 
//1.4. Заповедная роща (6)
// 
//В заповеднике растет роща редких деревьев.Для их защиты требуется обнести рощу забором.Но для обеспечения доступа к остальной территории заповедника площадь участка, 
//окруженного забором, должна быть минимальной.Деревья растут точно в узлах координатной сетки на расстоянии одного метра друг от друга.Любое из деревьев имеет хотя бы 
//одного соседа(с юга, севера, востока или запада).Забор состоит из блоков длиной в один метр.Чтобы огородить одно дерево необходимо 4 блока забора
//По заданной конфигурации рощи найти минимально необходимое число блоков для забора.
// 
//ВВОД:В первой строке записаны через пробел два числа N и K(1 ≤ N, K ≤ 300)– количество строк и столбцов данных.
//В следующих N строках содержатся последовательности из K символов(единиц или нулей).
//Единицей обозначается расположение дерева, а нулем – его отсутствие в узле координатной сетки.
//ВЫВОД: В единственной строке выводится число блоков забора, необходимое для огораживания.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
#include <string>

const char VIZITED = '+';
const char TREE = '1';
const char EMPTY = '0';
const char BORDER = '#';

struct Coord {
	int x;
	int y;
};

// Процедура, изменяющая пройденные нули на "#" или "1", в зависмости от состояния
void ChangeMarker(std::vector<Coord>& stack, std::vector<std::vector<char>>& field, Coord& pos, char changeCh)
{
	while (!stack.empty())
	{
		pos = stack.back();
		stack.pop_back();
		field[pos.x][pos.y] = changeCh;
	}
}

// Процедура, проверящая пустое пространстов (нули) на их состояния (окружены 1-ми или нет)
void CheckEmptyPlace(std::vector<Coord>& stack, std::vector<std::vector<char>>& field, int i, int j, Coord& pos)
{
	pos.x = i;
	pos.y = j;

	if (i >= 0 && i < field.size() && j >= 0 && j < field[i].size())
	{
		if (field[i][j] == EMPTY)
		{
			if (field[i][j] == VIZITED) return;

			stack.push_back(pos);
			field[i][j] = VIZITED;

			bool hasEmptyNeighbor = false;
			bool hasBorderNeighbor = false;

			if (i + 1 < field.size() && field[i + 1][j] == EMPTY) hasEmptyNeighbor = true;
			if (i - 1 >= 0 && field[i - 1][j] == EMPTY) hasEmptyNeighbor = true;
			if (j + 1 < field[i].size() && field[i][j + 1] == EMPTY) hasEmptyNeighbor = true;
			if (j - 1 >= 0 && field[i][j - 1] == EMPTY) hasEmptyNeighbor = true;

			//---------------------------------------------------------------

			if (i + 1 < field.size() && j - 1 >= 0 && field[i + 1][j - 1] == EMPTY) hasEmptyNeighbor = true;
			if (i - 1 >= 0 && j + 1 < field[i - 1].size() && field[i - 1][j + 1] == EMPTY) hasEmptyNeighbor = true;
			if (i + 1 < field.size() && j + 1 < field[i - 1].size() && field[i + 1][j + 1] == EMPTY) hasEmptyNeighbor = true;
			if (i - 1 >= 0 && j - 1 >= 0 && field[i - 1][j - 1] == EMPTY) hasEmptyNeighbor = true;

			//---------------------------------------------------------------------

			if (i + 1 < field.size() && field[i + 1][j] == BORDER) hasBorderNeighbor = true;
			if (i - 1 >= 0 && field[i - 1][j] == BORDER) hasBorderNeighbor = true;
			if (j + 1 < field[i].size() && field[i][j + 1] == BORDER) hasBorderNeighbor = true;
			if (j - 1 >= 0 && field[i][j - 1] == BORDER) hasBorderNeighbor = true;

			//--------------------------------------------------------------------

			if (i + 1 < field.size() && j - 1 >= 0 && field[i + 1][j - 1] == BORDER) hasBorderNeighbor = true;
			if (i - 1 >= 0 && j + 1 < field[i - 1].size() && field[i - 1][j + 1] == BORDER) hasBorderNeighbor = true;
			if (i + 1 < field.size() && j + 1 < field[i - 1].size() && field[i + 1][j + 1] == BORDER) hasBorderNeighbor = true;
			if (i - 1 >= 0 && j - 1 >= 0 && field[i - 1][j - 1] == BORDER) hasBorderNeighbor = true;


			if (hasBorderNeighbor)
			{
				field[i][j] = BORDER;
			}

			if (hasEmptyNeighbor)
			{
				CheckEmptyPlace(stack, field, i + 1, j, pos);
				CheckEmptyPlace(stack, field, i - 1, j, pos);
				CheckEmptyPlace(stack, field, i, j + 1, pos);
				CheckEmptyPlace(stack, field, i, j - 1, pos);
				CheckEmptyPlace(stack, field, i + 1, j - 1, pos);
				CheckEmptyPlace(stack, field, i - 1, j - 1, pos);
				CheckEmptyPlace(stack, field, i + 1, j + 1, pos);
				CheckEmptyPlace(stack, field, i - 1, j + 1, pos);
			}
			else
			{
				if (hasBorderNeighbor)
				{
					ChangeMarker(stack, field, pos, BORDER);
				}
				else
				{
					ChangeMarker(stack, field, pos, TREE);
				}
			}
		}
	}
}

// Подсчет количества блоков забора
int CountFenceBlock(std::vector<std::vector<char>>& field, int lines, int columns)
{
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

void ReadFile(std::vector<std::vector<char>>& field, int lines, int columns)
{
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			char ch;
			std::cin >> ch;
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
}

int main()
{
	int lines, columns;
	std::cin >> lines >> columns;

	std::vector<Coord> memory;
	std::vector<std::vector<char>> field(lines, std::vector<char>(columns));

	// считывание файла
	ReadFile(field, lines, columns);

	Coord pos;

	// Обход поля для нулей
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (field[i][j] == EMPTY)
			{
				CheckEmptyPlace(memory, field, i, j, pos);
			}
			else
			{
				continue;
			}
		}
	}



	int count = CountFenceBlock(field, lines, columns);
	std::cout << count << '\n';

	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			std::cout << field[i][j];
		}
		std::cout << '\n';
	}

	return 0;
}


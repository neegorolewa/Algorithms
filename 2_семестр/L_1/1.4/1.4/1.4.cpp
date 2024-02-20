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

const char TREE = '1';
const char EMPTY = '0';
const char BORDER = '#';
const char PASSED = '.';
const std::string IN_FILE = "input5.txt";
const std::string OUT_FILE = "output.txt";
 
struct Coord {
	int x;
	int y;
};

// Процедура, изменяющая пройденные нули на "#" или "1", в зависмости от состояния
void changeMarker(std::vector<Coord>& stack, std::vector<std::vector<char>>& field, Coord& pos, char changeCh)
{
	while (!stack.empty())
	{
		pos = stack.back();
		stack.pop_back();
		field[pos.x][pos.y] = changeCh;
	}
}

// Процедура, проверящая пустое пространстов (нули) на их состояния (окружены 1-ми или нет)
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

// Подсчет количества блоков забора
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

void readFile(std::vector<std::vector<char>>& field, int lines, int columns, std::ifstream input)
{
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
}

int main()
{
	std::ifstream input(IN_FILE);
	std::ofstream output(OUT_FILE);

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
			if ((ch == EMPTY) && ((j == 0 || j == columns - 1) || (i == 0 || i == lines - 1))) // нули на границе -> #
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

	int count = countFenceBlock(field, lines, columns);
	output << count << '\n';
	
    return 0;
}


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
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

void floodFill(vector < vector < int>>& matrix, int row, int col) {
	queue < pair<int, int>> q;
	q.push(make_pair(row, col));

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		if (x >= 0 && x < matrix.size() && y >= 0 && y < matrix[0].size() && matrix[x][y] == 0) {
			matrix[x][y] = 2;
			q.push(make_pair(x - 1, y));
			q.push(make_pair(x + 1, y));
			q.push(make_pair(x, y - 1));
			q.push(make_pair(x, y + 1));
		}
	}
}

void fillOuterBorderWithTwos(vector < vector < int>>& matrix) {
	int rows = matrix.size();
	int cols = matrix[0].size();

	for (int i = 0; i < rows; i++) {
		floodFill(matrix, i, 0);
		floodFill(matrix, i, cols - 1);
	}

	for (int j = 0; j < cols; j++) {
		floodFill(matrix, 0, j);
		floodFill(matrix, rows - 1, j);
	}
}

void fillInnerBorderWithOnes(vector < vector < int>>& matrix) {
	int rows = matrix.size();
	int cols = matrix[0].size();

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (matrix[i][j] == 0) {
				matrix[i][j] = 1;
			}
		}
	}
}

int main() {
	int rows, cols;
	cin >> rows >> cols;

	vector < vector < int>> matrix(rows, vector<int>(cols));
	char c;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cin >> c;
			matrix[i][j] = c - '0';
		}
	}

	fillOuterBorderWithTwos(matrix);
	fillInnerBorderWithOnes(matrix);

	int fence = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (matrix[i][j] == 1) {
				fence += 4;
				if (i > 0 && matrix[i - 1][j] == 1) fence -= 2;
				if (j > 0 && matrix[i][j - 1] == 1) fence -= 2;
			}
		}
	}
	cout << fence << endl;
}
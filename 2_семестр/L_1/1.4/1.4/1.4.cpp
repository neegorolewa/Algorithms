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

	int Lines, Columns;
	char ch;


    return 0;
}


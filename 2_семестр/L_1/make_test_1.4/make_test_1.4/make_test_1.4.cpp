#include <fstream>
#include <string>

const int MAX_LINES = 10;
const int MAX_COLUMNS = 10;
const char TREE = '1';
const char EMPTY = '0';
const std::string OUT_FILE = "input_test.txt";

int main()
{
	std::ofstream outputFile(OUT_FILE);
	for (int i = 0; i < MAX_LINES; i++)
	{
		for (int j = 0; j < MAX_COLUMNS; j++)
		{
			if (i == 0 || i == MAX_LINES - 1)
			{
				outputFile << TREE;
			}
			else
			{
				if ((i != 0) && (j == 0 || j == MAX_COLUMNS - 1))
				{
					outputFile << TREE;
				}
				else
				{
					outputFile << EMPTY;
				}
			}
		}
		outputFile << '\n';
	}

	return 0;
}
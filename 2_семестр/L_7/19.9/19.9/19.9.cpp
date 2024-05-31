#include <iostream>
#include <fstream>
#include <map>
//Габдрахманов Е.Н. ПС-21
//Microsoft Visual Studio
// -----------------------------------
//19.9.Повторяющиеся числа(3)
//Задан массив целых чисел  A1, A2, …, AN(-109 ≤  Ai ≤ 109; 1 ≤  N ≤ 2×105).
//Найти элемент, который повторяется наибольшее количество раз.
//Если таких элементов несколько, то вывести наименьший из них.
// 
//Ввод.В первой строке файла INPUT.TXT задается значение N.Во второй - числа через пробел.
//Вывод.В единственной строке файла OUTPUT.TXT вывести два числа : наименьший элемент с максимальным количеством повторений и количество повторений этого элемента.
//
//Примеры
//Ввод 1             Ввод 2
//5                  5
//- 3 0 5 0 - 3        5 4 3 2 7
//Вывод 1            Вывод 2
//- 3 2               2 1
//------------------------------------


#include <vector>
#include <algorithm>

int main() {
    std::ifstream input("INPUT.TXT");
    std::ofstream output("OUTPUT.TXT");

    int N;
    input >> N;

    std::map<int, int> count;

    for (int i = 0; i < N; ++i) 
    {
        int num;
        input >> num;
        ++count[num];
    }

    int maxCount = 0;
    int minNum = INT_MAX;
    for (const auto& pair : count) 
    {
        if (pair.second > maxCount || (pair.second == maxCount && pair.first < minNum)) 
        {
            maxCount = pair.second;
            minNum = pair.first;
        }
    }

    output << minNum << " " << maxCount << std::endl;

    return 0;
}
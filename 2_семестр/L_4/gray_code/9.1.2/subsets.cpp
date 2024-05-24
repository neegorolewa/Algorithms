//Габдрахманов Е.Н. ПС-21
//Microsoft Visual Studio
// 9.1 Простые примеры на подмножества (4)
//Составить программы для решения следующих задач:
//2) задано множество символов, выдать его подмножества из заданного числа элементов в лексикографическом порядке;
//Входные данные задавать с клавиатуры, вывод результатов - на экран.
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::string> getSubsets(const std::string& set, int subsetSize) {
    std::vector<std::string> subsets;
    int setSize = set.size();
    unsigned int subsetCount = 1 << setSize; 

    for (unsigned int i = 0; i < subsetCount; i++) 
    {
        std::string subset;

        for (int j = 0; j < setSize; j++) 
        {

            if (i & (1 << j)) 
            {
                subset += set[j];
            }
        }

        if (subset.size() == subsetSize) 
        {
            subsets.push_back(subset);
        }
    }

    std::sort(subsets.begin(), subsets.end());
    return subsets;
}

int main() {
    std::string set;
    int subsetSize;

    std::cout << "set: ";
    std::cin >> set;
    std::cout << "length subsets: ";
    std::cin >> subsetSize;

    // Получаем подмножества и выводим их на экран
    std::vector<std::string> subsets = getSubsets(set, subsetSize);
    for (const auto& subset : subsets) 
    {
        std::cout << subset << std::endl;
    }

    return 0;
}
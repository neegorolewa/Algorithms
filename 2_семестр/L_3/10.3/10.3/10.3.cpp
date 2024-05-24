//Габдрахманов Е.Н. ПС-21
//Microsoft Visual Studio 2022
//10.3 Провода(5)
//Дано N отрезков провода длиной L1, L2, ..., LN сантиметров.Требуется с помощью разрезания получить из них K равных отрезков как можно большей длины, выражающейся целым числом сантиметров.Если нельзя получить K отрезков длиной даже 1 см, вывести 0.
//Ограничения: 1 ≤ N ≤ 10 000, 1 ≤ K ≤ 10 000, 100 ≤ Li ≤ 10 000 000, все числа целые, время 1 с.
//Ввод из файла INPUT.TXT.В первой строке находятся через пробел числа N и К.В следующих N строках - L1, L2, ..., LN, по одному числу в строке.
//Вывод в файл INPUT.TXT.Вывести одно число - полученную длину отрезков.
//Пример
//Ввод
//4 11
//802
//743
//457
//539
//Вывод
//200

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool isPossible(const vector<int>& lengths, int K, int length) {
    int count = 0;
    for (int L : lengths) {
        count += L / length;
    }
    return count >= K;
}

int main() {
    ifstream inFile("input.txt");
    ofstream outFile("output.txt");

    int N, K;
    inFile >> N >> K;

    vector<int> lengths(N);
    for (int i = 0; i < N; ++i) {
        inFile >> lengths[i];
    }

    int left = 1;
    int right = *max_element(lengths.begin(), lengths.end());
    int result = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (isPossible(lengths, K, mid)) {
            result = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    outFile << result << endl;

    return 0;
}
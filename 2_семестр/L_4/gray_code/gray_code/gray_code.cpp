//Габдрахманов Е.Н. ПС-21
//Microsoft Visual Studio
// 9.1 Простые примеры на подмножества (4)
//Составить программы для решения следующих задач:
//1) выдать слова кода Грея заданной размерности, используя рекурсию и генерацию слов по их номерам;
//Входные данные задавать с клавиатуры, вывод результатов - на экран.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

string grayCodeWord(int n, int num) {
    string result = "";
    for (int i = 0; i < n; i++) {
        result = to_string((num ^ (num >> 1)) & 1) + result;
        num >>= 1;
    }
    return result;
}

void grayCode(int n) {
    for (int i = 0; i < (1 << n); i++) {
        cout << grayCodeWord(n, i) << endl;
    }
}

int main() {
    int n;
    cin >> n;

    grayCode(n);

    return 0;
}
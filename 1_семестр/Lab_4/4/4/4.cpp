//7. Имеются  расписания вылетов самолетов в ряде аэропортов.
//Требуется методом поиска в глубину по начальному  и  конечному
//пунктам   предложить    маршрут  с   возможными   пересадками,
//оптимальный по одному из следующих критериев :
//1) наименьшая суммарная стоимость билетов;
//2) минимальное число пересадок;
//3) наименьшее  время  в  пути, включая  время  ожидания  в
//аэропортах.
//При выборе маршрута считать, что пересадка допустима, если
//интервал времени между прилетом самолета и последующим вылетом
//составляет не менее двух часов и не более суток(8).
//Габдрахманов Е.Н. ПС-21

#include <iostream>
#include <vector>
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include <iterator>
#include <conio.h>
#include <algorithm>
#include <map>


using namespace std;

const string EMPTY = "";
const int PLUS_TRANSFER = 1;
const int TWO_HOURS = 120;
const int DAY = 1440;

struct Flight {
    string arrivAirport; // Конечный аэропорт
    int depTime; // Время вылета
    int arrTime; // Время прилета
    int price; // Стоимость билета
};

struct Connect {
    string depAirport; //Начальный аэропорт
    vector<Flight> flight;
};

vector<Connect> flights;

// Функция для добавления рейса в матрицу
void addFlight(int count, string dep, string arriv, int depTime, int arrTime, int cost) {

    Flight newFlight = { arriv, depTime, arrTime, cost };

    for (int i = 0; i < flights.size(); i++) {
        if (flights[i].depAirport == EMPTY) {
            flights[i].depAirport = dep;
            flights[i].flight.push_back(newFlight);
            break;
        }
        else {
            if (flights[i].depAirport == dep) {
                flights[i].flight.push_back(newFlight);
                break;
            }
            else {
                continue;
            };
        }
    };
};

vector<pair<vector<string>, int>> allPathsPrice;
int price;

void minTicketPrice(string curr, string arriv, vector<string> path, int currTime, int price, map<string, bool> visited, bool firstFlight) {
    
    path.push_back(curr);
    visited[curr] = true;

    if (curr == arriv) {
        pair<vector<string>, int> newPath = make_pair(path, price);
        allPathsPrice.push_back(newPath);
        return;
    };

    for (auto connect : flights) {
        if (connect.depAirport == curr) {
            for (auto flight : connect.flight) {
                if (firstFlight) {
                    if ((flight.depTime >= currTime) and (!visited[flight.arrivAirport])) {
                        minTicketPrice(flight.arrivAirport, arriv, path, flight.arrTime, price + flight.price, visited, false);
                    }
                }
                else {
                    if ((flight.depTime > currTime) and (flight.depTime - currTime >= TWO_HOURS) and
                        (flight.depTime - currTime <= DAY) and (!visited[flight.arrivAirport])) {
                        minTicketPrice(flight.arrivAirport, arriv, path, flight.arrTime, price + flight.price, visited, false);
                    }
                }
            }
        }
    }

};

vector<pair<vector<string>, int>> allPathsTransfer;
int transfer;

void minTransfer(string curr, string arriv, vector<string> path, int currTime, int transfer, map<string, bool> visited, bool firstFlight) {

    path.push_back(curr);
    visited[curr] = true;

    if (curr == arriv) {
        pair<vector<string>, int> newPath = make_pair(path, transfer);
        allPathsTransfer.push_back(newPath);
        return;
    };

    for (auto connect : flights) {
        if (connect.depAirport == curr) {
            for (auto flight : connect.flight) {
                if (firstFlight) {
                    if ((flight.depTime >= currTime) and (!visited[flight.arrivAirport])) {
                        minTransfer(flight.arrivAirport, arriv, path, flight.arrTime, transfer + PLUS_TRANSFER, visited, false);
                    }
                }
                else {
                    if ((flight.depTime > currTime) and (flight.depTime - currTime >= TWO_HOURS) and
                        (flight.depTime - currTime <= DAY) and (!visited[flight.arrivAirport])) {
                        minTransfer(flight.arrivAirport, arriv, path, flight.arrTime, transfer + PLUS_TRANSFER, visited, false);
                    }
                }
            }
        }
    }

};

vector<pair<vector<string>, int>> allPathsTimeFlight;

void minTimeFlight(string curr, string arriv, vector<string> path, int currTime, int time, map<string, bool> visited, bool firstFlight) {

    path.push_back(curr);
    visited[curr] = true;

    if (curr == arriv) {
        pair<vector<string>, int> newPath = make_pair(path, time);
        allPathsTimeFlight.push_back(newPath);
        return;
    };

    for (auto connect : flights) {
        if (connect.depAirport == curr) {
            for (auto flight : connect.flight) {
                if (firstFlight) {
                    if ((flight.depTime >= currTime)) {
                        minTimeFlight(flight.arrivAirport, arriv, path, flight.arrTime, time + (flight.arrTime - flight.depTime), visited, false);
                    }
                }
                else {
                    if ((flight.depTime > currTime) and (flight.depTime - currTime >= TWO_HOURS) and
                        (flight.depTime - currTime <= DAY) and (!visited[flight.arrivAirport])) {
                        minTimeFlight(flight.arrivAirport, arriv, path, flight.arrTime, time + (flight.arrTime - flight.depTime) + (flight.depTime - currTime), visited, false);
                    }
                }
            }
        }
    }

};

bool sortInt(const pair<vector<string>, int>& a, const pair<vector<string>, int>& b) {
    return a.second < b.second;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string iFile;
    cout << "Введите файл: ";
    cin >> iFile;
    ifstream inFile(iFile);

    if (!inFile) {
        cout << "Не удалось открыть файл!" << endl;
        return 1;
    }

    string depart, arriv;
    
    int n;
    inFile >> n;
    flights.resize(n);
    map<string, bool> visited;

    while (!inFile.eof()) {
        int depTimeHour, depTimeMinute, arrTimeHour, arrTimeMinute, price = 0;
        string depart, arriv;
        char colon;
        inFile >> depTimeHour >> colon >> depTimeMinute >> depart >> arriv >> arrTimeHour >> colon >> arrTimeMinute >> price;
        int depTime = depTimeHour * 60 + depTimeMinute;
        int arrTime = arrTimeHour * 60 + arrTimeMinute;
        addFlight(n, depart, arriv, depTime, arrTime, price);
    }

    inFile.close();
    int menu = 0;

    while (menu != 5)
    {
        system("cls");
        cout << "1 - Показать расписание \n"
            << "2 - Маршрут с наименьшей суммарной стоимостью билетов \n"
            << "3 - Маршрут с минимальным числом пересадок \n"
            << "4 - Наименьшее время в пути \n"
            << "5 - Завершить работу \n";
        cin >> menu;
        system("cls");
        switch (menu)
        {
        case 1:
            for (int i = 0; i < flights.size(); i++) {

                for (Flight fl: flights[i].flight) {

                    int depTimeHour, depTimeMinute, arrTimeHour, arrTimeMinute, price = 0;
                    depTimeMinute = fl.depTime % 60;
                    depTimeHour = fl.depTime / 60;
                    char colon = ':';
                    arrTimeMinute = fl.arrTime % 60;
                    arrTimeHour = fl.arrTime / 60;
                    price = fl.price;
                    cout << setw(2) << setfill('0') << depTimeHour << colon;
                    cout << setw(2) << setfill('0') << depTimeMinute;
                    cout << ' ' << flights[i].depAirport << ' ' << fl.arrivAirport << ' ';
                    cout << setw(2) << setfill('0') << arrTimeHour << colon;
                    cout << setw(2) << setfill('0') << arrTimeMinute << ' ' << price << '\n';

                };

            };
            cout << "Нажмите любую клавишу чтобы продолжить...";
            _getch();
            break;
        case 2:
            cout << "Введите начальный аэропорт < НазваниеГорода >: " << '\n';
            cin >> depart;
            cout << "Введите конечный аэропорт < НазваниеГорода >: " << '\n';
            cin >> arriv;
            int departTime;
            minTicketPrice(depart, arriv, {}, 0, 0, {}, true);
            sort(allPathsPrice.begin(), allPathsPrice.end(), sortInt);
            if (!allPathsPrice.empty()) {
                for (const auto& airport : allPathsPrice[0].first) {
                    cout << airport << " -> ";
                }
                cout << allPathsPrice[0].second << '\n';
                allPathsPrice.clear();
            }
            else {
                cout << "Путей не найдено" << '\n';
            }
            cout << "Нажмите любую клавишу чтобы продолжить...";
            _getch();
            break;
        case 3:
            cout << "Введите начальный аэропорт < НазваниеГорода >: " << '\n';
            cin >> depart;
            cout << "Введите конечный аэропорт < НазваниеГорода >: " << '\n';
            cin >> arriv;
            minTransfer(depart, arriv, {}, 0, 0, {}, true);
            sort(allPathsTransfer.begin(), allPathsTransfer.end(), sortInt);
            if (!allPathsTransfer.empty()) {
                for (const auto& airport : allPathsTransfer[0].first) {
                    cout << airport << " -> ";
                }
                cout << allPathsTransfer[0].second << '\n';
                allPathsTransfer.clear();
            }
            else {
                cout << "Путей не найдено" << '\n';
            }
            cout << "Нажмите любую клавишу чтобы продолжить...";
            _getch();
            break;
        case 4:
            cout << "Введите начальный аэропорт < НазваниеГорода >: " << '\n';
            cin >> depart;
            cout << "Введите конечный аэропорт < НазваниеГорода >: " << '\n';
            cin >> arriv;
            minTimeFlight(depart, arriv, {}, 0, 0, {}, true);
            sort(allPathsTimeFlight.begin(), allPathsTimeFlight.end(), sortInt);
            if (!allPathsTimeFlight.empty()) {
                for (const auto& airport : allPathsTimeFlight[0].first) {
                    cout << airport << " -> ";
                }
                cout << setw(2) << setfill('0') << abs(allPathsTimeFlight[0].second / 60) << ":" << setw(2) << setfill('0') << abs(allPathsTimeFlight[0].second % 60) << '\n';
                allPathsTimeFlight.clear();
            }
            else {
                cout << "Путей не найдено" << '\n';
            }
            cout << "Нажмите любую клавишу чтобы продолжить...";
            _getch();
            break;
        case 5:
            cout << "Программа завершена";
        };
    }

    return 0;
}

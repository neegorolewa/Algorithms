#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include <conio.h>
using namespace std;

struct Node {
	int key;
	int info;
	Node* next;
};

int hashFunc(int key, int size) {
	return key % size;
}

void insert(vector<Node>& table, int key, int info) {
	int index = hashFunc(key, table.size());
	Node* newNode = new Node;
	newNode->key = key;
	newNode->info = info;
	newNode->next = nullptr;

	if (table[index].next == nullptr) {
		table[index].next = newNode;
	}
	else {
		Node* current = table[index].next;
		while (current->next != nullptr) {
			current = current->next;
		};
		current->next = newNode;
	}
} 

Node* search(vector<Node>& table, int key) {
	int index = hashFunc(key, table.size());
	Node* current = table[index].next;
	while (current != nullptr) {
		if (current->key == key) {
			return current;
		}
		current = current->next;
	};
	return nullptr;
}

bool remove(vector<Node>& table, int key) {
	int index = hashFunc(key, table.size());
	Node* current = &table[index];
	while (current->next != nullptr) {
		if (current->next->key == key) {
			Node* temp = current->next;
			current->next = temp->next;
			delete temp;
			return true;
		}
		current = current->next;
	}
	return false;
}

void printTable(vector<Node>& table) {
	for (int i = 0; i < table.size(); i++) {
		cout << "[" << i << "]: ";
		Node* current = table[i].next;
		while (current != nullptr) {
			cout << "(" << current->key << ", " << current->info << ") -> ";
			current = current->next;
		}
		cout << "NULL" << endl;
	}
}

int main()
{
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

	int size, key, info;;
	inFile >> size;
	
	vector<Node> table(size);

	while (!inFile.eof()) {
		inFile >> key >> info;
		insert(table, key, info);
	}

	inFile.close();

	Node* res;
	bool del;

	int numOp = 0;
	while (numOp != 5) {

		system("cls");
		cout << "(1) Вывести хеш-массив \n"
			<< "(2) Вставить элемент \n"
			<< "(3) Найти элемент \n"
			<< "(4) Удалить элемент \n"
			<< "(5) Завершить работу \n"
			<< "Введите номер операции: ";
		cin >> numOp;

		switch (numOp) {
		case 1:
			system("cls");
			printTable(table);
			cout << "Нажмите любую клавишу для продолжения...";
			_getch();
			break;
		case 2:
			system("cls");
			cout << "Введите ключ <int>: ";
			cin >> key;
			cout << "Введите инфомрацию <int>: ";
			cin >> info;
			insert(table, key, info);
			cout << "Нажмите любую клавишу для продолжения...";
			_getch();
			break;
		case 3:
			system("cls");
			cout << "Введите ключ <int>: ";
			cin >> key;
			res = search(table, key);
			if (res != nullptr) {
				cout << "(" << res->key << ", " << res->info << ")" << '\n';
			}
			else {
				cout << "Элемент с ключом " << key << " не найден" << '\n';
			}
			cout << "Нажмите любую клавишу для продолжения...";
			_getch();
			break;
		case 4:
			system("cls");
			cout << "Введите ключ <int>: ";
			cin >> key;
			del = remove(table, key);
			if (del) {
				cout << "Элемент удален!" << '\n';
			}
			else {
				cout << "Элемент не найден..." << '\n';
			}
			cout << "Нажмите любую клавишу для продолжения...";
			_getch();
			break;
		case 5:
			cout << "Программа завершена";
		};
		
	}
	return 0;
}
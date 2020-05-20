// Tree.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Tree.h"

int menu() {
	int key;
	cout << "1.Добавить элемент \n";
	cout << "2.Удалить элемент \n";
	cout << "3.Поиск элемента \n";
	cout << "4.Прямой обход \n";
	cout << "5.Центрированный обход \n";
	cout << "6.Обратный обход \n";
	cout << "0.Выход \n";
	cout << "Выберите действие: \n";
	cin >> key;
	return key;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int key;
	string data;
	Tree* tree = new Tree();
	while (true) {
		switch (menu()) {
		case 1:
			cout << "Введите ключ: ";
			cin >> key;
			cout << "\nВведите данные: ";
			cin >> data;
			tree->Insert(key, data);
			break;
		case 2: 
			cout << "Введите ключ удаляемого элемента: ";
			cin >> key;
			tree->Delete(key);
			break;
		case 3:
			cout << "Введите ключ элемента: ";
			cin >> key;
			tree->Search(key);
			break;
		case 4:
			tree->NLR();
			break;
		case 5:
			tree->LNR();
			break;
		case 6:
			tree->LRN();
			break;
		default:
			return 0;
		}
	}
}

#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <Windows.h>

using namespace std;

ifstream fin;
ofstream fout;

string path = "sample.txt";

string fromFile(string& str) {
	try
	{
		fin.open(path);
		getline(fin, str);
		fin.close();
		return str;
	}
	catch (const exception&)
	{
		cout << "Ошибка открытия файла" << endl;
		system("pause");
	}
}

int ans() {
	int choice = 0;
	int options = 2;
	int ch;
	while (true) {
		system("cls");
		cout << "Выберите способ ввода последовательности:" << endl << endl;
		choice = (choice + options) % options;

		if (choice == 0) cout << "-> Вручную" << endl;
		else  cout << "   Вручную" << endl;

		if (choice == 1) cout << "-> Прочитать из файла" << endl;
		else  cout << "   Прочитать из файла" << endl;

		ch = _getch();
		if (ch == 224)
		{
			ch = _getch();
			if (ch == 80) choice++;
			if (ch == 72) choice--;
		}
		if (ch == 119)
		{
			choice--;
		}
		if (ch == 115)
		{
			choice++;
		}
		if (ch == 13) break;
	}
	system("cls");
	return choice;
}

string menu(string &str)
{
	switch (ans())
	{
	case 0:
		getline(cin, str);
		break;
	case 1:
		str = fromFile(str);
		break;
	}
	return str;
}

string delDuplicate(string &str) {
	for (int i = 0; i < size(str); i++)
	{

	}
	return str;
}

string format(string &str) {
	str = delDuplicate(str);
	return str;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string str;
	str = menu(str);
	cout << "Ваша строка:" << endl << str << endl;
	format(str);
	system("pause");
}

#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <Windows.h>

using namespace std;

ifstream fin;
ofstream fout;

string path = "sample.txt";

void fromFile(string& str) {
	try
	{
		fin.open(path);
		getline(fin, str);
		fin.close();
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

void menu(string &str)
{
	switch (ans())
	{
	case 0:
		getline(cin, str);
		break;
	case 1:
		fromFile(str);
		break;
	}
}

string cutStr(string str) {
	char ch;
	string formattedStr;
	for (int i = 0, j = 0; i < size(str); i++, j++)
	{
		ch = str[i];
		if (ch == 0x2e) {
			break;
		}
		formattedStr += str[i];
	}
	return formattedStr;
}

string delDuplicate(string str) {
	char ch;
	string formattedStr;
	for (int i = 0, j = 0; i < size(str); i++, j++)
	{
		ch = str[i];
		if (
			( (ch >= 0x20) && (ch <= 0x47) || // Проверка на знак пунктуации
			(ch >= 0x3a) && (ch <= 0x40) ||
			(ch >= 0x5b) && (ch <= 0x60) ||
			(ch >= 0x7b) && (ch <= 0x7e) ||
			(ch >= 0xf8) && (ch <= 0xfa) &&
			(ch != 0x2e) ) && // Не точка
			(str[i] == str[i - 1]) // Дублируется
			) 
		{
			continue;
		}
		formattedStr += str[i];
	}
	return formattedStr;
}

void fixCase(string& str) {
	bool firstDone = false;
	char ch;
	for (int i = 0; i < size(str); i++)
	{
		ch = str[i];
		if (
			(ch >= 0x41) && (ch <= 0x5a) || //Проверка на буквы
			(ch >= 0x61) && (ch <= 0x7a) ||
			(ch >= 0xc0) && (ch <= 0xff)
			) 
		{
			if (
				(firstDone == false) && //Если первая встреченная буква строчная
				((ch >= 0x61) && (ch <= 0x7a) ||
				(ch >= 0xe0) && (ch <= 0xff))
				)
			{
				ch -= 32;
				str[i] = ch;
				firstDone == true;
				continue;
			}
			if ((ch >= 0x41) && (ch <= 0x5a) || //Если буква заглавная
				(ch >= 0xc0) && (ch <= 0xdf))
			{
				ch += 32;
				str[i] = ch;
			}
		}
	}
}

void format(string &str) {
	str = cutStr(str);
	str = delDuplicate(str);
	fixCase(str);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string str;
	menu(str);
	cout << "Ваша строка:" << endl << str << endl << endl;
	format(str);
	cout << "Отформатировання строка:" << endl << str << endl;
	system("pause");
}

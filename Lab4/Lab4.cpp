#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <Windows.h>

using namespace std;

string samplePath = "sample.txt",
	   outputPath = "output.txt";

void doATask(string& str);

//Работа с файлами
void readFromFile(string& str) {
	try
	{
		ifstream fin;
		fin.open(samplePath);
		getline(fin, str);
		fin.close();
	}
	catch (const exception&)
	{
		cout << "Ошибка открытия файла" << endl;
		system("pause");
	}
}
void writeToFile(string str)
{
	ofstream fout;
	try
	{
		fout.open(outputPath, ofstream::app);
		fout << str << endl;
		fout.close();
	}
	catch (const exception&)
	{
		cout << "Ошибка открытия файла" << endl;
	}
}
void clearFile()
{
	ofstream fout;
	try
	{
		fout.open(outputPath);
		fout.close();
		cout << "Файл вывода очищен!" << endl;
	}
	catch (const exception&)
	{
		cout << "Ошибка открытия файла" << endl;
	}
}

//Меню ввода строки
int ans() {
	int choice = 0;
	int options = 4;
	int ch;
	while (true) {
		system("cls");
		cout << "Выберите способ ввода последовательности:" << endl << endl;
		choice = (choice + options) % options;

		if (choice == 0) cout << "-> Вручную" << endl;
		else  cout << "   Вручную" << endl;

		if (choice == 1) cout << "-> Прочитать из файла" << endl;
		else  cout << "   Прочитать из файла" << endl;

		if (choice == 2) cout << "-> Очистить файл вывода" << endl;
		else  cout << "   Очистить файл вывода" << endl;

		if (choice == 3) cout << "-> Выход" << endl;
		else  cout << "   Выход" << endl;

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
void menu(string& str)
{
	switch (ans())
	{
	case 0:
		getline(cin, str);
		doATask(str);
		break;
	case 1:
		readFromFile(str);
		doATask(str);
		break;
	case 2:
		clearFile();
		break;
	case 3:
		exit(0);
		break;
	}
}

//Форматирование строки
string cutStr(string str) {
	char ch;
	string formattedStr;
	for (int i = 0, j = 0; i < size(str); i++, j++)
	{
		ch = str[i];
		formattedStr += str[i];
		if (ch == 0x2e) {
			break;
		}
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
			((ch >= 0x20) && (ch <= 0x47) || // Проверка на знак пунктуации
			(ch >= 0x3a) && (ch <= 0x40) ||
				(ch >= 0x5b) && (ch <= 0x60) ||
				(ch >= 0x7b) && (ch <= 0x7e) ||
				(ch >= 0xf8) && (ch <= 0xfa) &&
				(ch != 0x2e)) && // Не точка
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
			(firstDone == false) && //Если первая встреченная буква строчная
			((ch >= 0x61) && (ch <= 0x7a) ||
			(ch >= -32) && (ch <= -1))
			)
		{
			ch -= 32;
			str[i] = ch;
			firstDone = true;
			continue;
		}
		if (
			(firstDone == false) && //Если первая встреченная буква заглавная
			((ch >= 0x41) && (ch <= 0x5a) ||
			(ch >= -64) && (ch <= -33))
			)
		{
			firstDone = true;
			continue;
		}
		if ((ch >= 0x41) && (ch <= 0x5a) || //Если буква заглавная
			(ch >= -64) && (ch <= -33))
		{
			ch += 32;
			str[i] = ch;
		}
	}
}
void format(string& str) {
	str = cutStr(str);
	str = delDuplicate(str);
	fixCase(str);
}

//Фильтрация строки по заданию
string filter(string str) {
	string word, list;
	char ch, localCh;
	bool isRight = false;
	for (int i = 0; i < size(str); i++)
	{
		ch = str[i];
		if ((ch >= 0x20) && (ch <= 0x47) || // Проверка на знак пунктуации
			(ch >= 0x3a) && (ch <= 0x40) ||
			(ch >= 0x5b) && (ch <= 0x60) ||
			(ch >= 0x7b) && (ch <= 0x7e) ||
			(ch >= 0xf8) && (ch <= 0xfa))
		{
			for (int j = 1; j < size(word); j++)
			{
				if (word[0] == word[j])
				{
					isRight = true;
					break;
				}
			}
			if (isRight)
			{
				list += word + ", ";
				isRight = false;
			}
			word = "\0";
		}
		else
		{
			word += ch;
		}
	}
	return list;
}

void doATask(string& str)
{
	writeToFile("Исходная строка: " + str);
	cout << "Ваша строка:" << endl << str << endl << endl;

	format(str);
	writeToFile("Отформатированная строка: " + str);
	cout << "Отформатированная строка:" << endl << str << endl << endl;

	str = filter(str);
	writeToFile("Отфильтрованная строка: " + str);
	cout << "Cлова, в которых первая буква встречается ещё раз:" << endl << str << endl << endl;

	writeToFile("\n============================================================\n");
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	while (true)
	{
		string str;
		menu(str);
		system("pause");
	}
}
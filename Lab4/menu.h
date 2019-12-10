#pragma once

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

void menu(string& str)
{
	switch (ans())
	{
	case 0:
		getline(cin, str);
		break;
	case 1:
		readFromFile(str);
		break;
	}
}
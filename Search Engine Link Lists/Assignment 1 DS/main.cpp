#include<iostream>
#include<string.h>
#include"Term_Info.h"
#include"List.h"
#include"Search_Engine.h"

using namespace std;

int main()
{
	int size = 5;
	string* name_of_files = new string[size];
	name_of_files[0] = "Documents\\Doc1.txt";
	name_of_files[1] = "Documents\\Doc2.txt";
	name_of_files[2] = "Documents\\Doc3.txt";
	name_of_files[3] = "Documents\\Doc4.txt";
	name_of_files[4] = "Documents\\Doc5.txt";
	
	Search_Engine Engine;
	Engine.Creat_Index(name_of_files, size);

	int menu_option = 0;

	do
	{
		cout << "	|Select an option from the menu below" << endl;
		cout << "	|------------------------------------" << endl;
		cout << "	|1->Search A Query " << endl;
		cout << "	|__________________" << endl;
		cout << "	|2->Add A Document " << endl;
		cout << "	|__________________" << endl;
		cout << "	|3->Print All Terms" << endl;
		cout << "	|__________________" << endl;
		cout << "	|0->Exit           " << endl;
		cout << "	|__________________" << endl;
		cout << "	";
		cin >> menu_option;
		cin.ignore();
		if (menu_option == 1)
		{
			system("CLS");

			char Query[100];
			cout << "	Enter a Query To Search : ";
			cin.getline(Query, 100);

			Engine.Search_Documents(Query);
			system("	pause");
			system("CLS");
		}
		else if (menu_option == 2)
		{
			system("CLS");

			string Doc_Name;
			cout << "	Enter a Doc Name To Add : ";
			cin >> Doc_Name;

			string* temp_array = new string[size];
			for (int i = 0; i < size; i++)
			{
				temp_array[i] = name_of_files[i];
			}

			delete[]name_of_files;

			size++;
			name_of_files = new string[size];

			for (int i = 0; i < size - 1; i++)
			{
				name_of_files[i] = temp_array[i];
			}
			name_of_files[size - 1] = Doc_Name;

			Engine.Creat_Index(name_of_files, size);
			system("CLS");
		}
		else if (menu_option == 3)
		{
			system("CLS");
			Engine.print_lists();
			system("	pause");
			system("CLS");
		}
		else if (menu_option != 0)
		{
			system("CLS");
			cout << endl;
			cout << "	Invalid Option Selected " << endl;
			cout << endl;
			system("	pause");
			system("CLS");
		}
	} while (menu_option != 0);

}
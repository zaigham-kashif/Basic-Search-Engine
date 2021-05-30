#include<iostream>
#include<string>
#include"Search_Engine.h"

using namespace std;

int main()
{
	int size = 5;//number of files
	string* name_of_files = new string[size];//name of each file is stored in an array of strings
	name_of_files[0] = "Documents\\Doc1.txt";
	name_of_files[1] = "Documents\\Doc2.txt";
	name_of_files[2] = "Documents\\Doc3.txt";
	name_of_files[3] = "Documents\\Doc4.txt";
	name_of_files[4] = "Documents\\Doc5.txt";

	Search_Engine search_engine(13);
	search_engine.create_index(name_of_files, size);//tree is created


	int menu_option = 0;//a variable to keep track of selected option

	do
	{
		// menu to selecte an option
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
			cin.getline(Query, 100);//query is stored in an array of type char

			search_engine.search_query(Query,size);//query is passed to search query fuction
			system("	pause");
			system("CLS");
		}
		else if (menu_option == 2)
		{
			system("CLS");

			string Doc_Name;
			cout << "	Enter a Doc Name To Add : ";
			cin >> Doc_Name;// file name is stored in a string 

			search_engine.add_document(name_of_files, Doc_Name, size);//document is added 
			search_engine.create_index(name_of_files, size);//tree is constucted again 
			system("CLS");
		}
		else if (menu_option == 3)
		{
			system("CLS");
			search_engine.print_hash_table();// all the terms are printed
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

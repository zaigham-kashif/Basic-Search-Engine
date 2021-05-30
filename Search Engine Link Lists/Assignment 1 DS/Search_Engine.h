#pragma once
#include"Term_Info.h"
#include"List.h"

class Search_Engine
{
private:
	List pr_List_of_Terms;
public:
	Search_Engine();

	void Creat_Index(string file_name[],int size_of_array);
	Term_Info* Search_Term(string term);
	void print_lists();
	void Search_Documents(string query);


	~Search_Engine();


};


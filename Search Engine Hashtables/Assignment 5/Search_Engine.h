#pragma once
#include"Hash_Table.h"
#include<fstream>

class Search_Engine
{
private:
	Hash_Table pr_hash_table;
public:

	Search_Engine(int size);

	void create_index(string file_names[],int no);//this function reads files word by word and call add doc to index function 
	void add_doc_to_index(string term, string doc_id);//this function cheaks if the word is already a part of the table its frequency is incresed else it is added to the table
	void print_hash_table();//prints the hash table with the indexs
	void search_query(string query, int no_of_doc);//searches for a query in the hash table
	void add_document(string *&name_of_files, string doc_name, int& no_of_files);//adds a document name 

	~Search_Engine();
};


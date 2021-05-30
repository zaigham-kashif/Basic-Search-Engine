#pragma once
#include"AVLTree.h"
#include"Term_Info.h"
#include<string.h>

//a class containing an AVL tree of objects of term_info
class Search_Engine
{
private:
	AVLTree<string, Term_Info> pr_tree;//object of class AVL tree with key being a string and data being term info of a term

public:
	Search_Engine();//default constructor

	void print_tree();//prints the tree in linear form
	void print_tree_rec(AVLnode<string, Term_Info>* temp_root);//a recursive tree to print the function

	void Create_Index(string file_name[], int size_of_array);//reads data from a given number of files word by word and the information to the tree
	void update_tree(string key,string doc_id);//updates the tree (if a term in already in the tree its frequency is incremented if the term is new it is added to the tree)
	void search_query(string query);//seraches for a query a prints the results
	void add_document(string *&name_of_files, string doc_name, int& no_of_files);//a function to add a document to list of documents 

	~Search_Engine();
};


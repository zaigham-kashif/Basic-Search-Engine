#pragma once
#include<string>
#include"List.h"
#include"Node.h"
#include"Term_Info.h"

class Hash_Table
{
private:
	list<Term_Info>** pr_hash_table;
	int pr_current_size;
	int pr_max_size;

	int hash_function(string word);
	void expand_insert(list<Term_Info>** hash_table, Term_Info& term_info);

public:
	Hash_Table();//default constructor 
	Hash_Table(int max_size);//parameterized constructor

	void set_size(int size);//sets the size of hash table
	void insert(string term, string doc_id);// add the term to the hash table
	void expand();//doubles the size of the hash table and rehashes the terms accordig to the new size
	void print_table();//prints the hash table

	list<Doc_Info>* search(string term);//searches for a term in the table. If found returns a pointer to its doc_info list

	~Hash_Table();
};
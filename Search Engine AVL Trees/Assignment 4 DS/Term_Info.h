#pragma once
#include"Doc_Info.h"
#include"List.h"
#include<string.h>
#include<iostream>

using namespace std;
// a class to store information about a term
class Term_Info
{
private:
	string pr_term;//the term
	list<Doc_Info> pr_term_info;//a linked list to store the information about different documents  

public:
	Term_Info();//default constructor
	Term_Info(string& term, string& doc_id);//parameterized constructor

	void add_doc(string doc_id);//adds a document name to the list
	bool find_doc_id(string doc_id);//finds a document from the list
	void inc_frequency(string doc_id);//increments the frequency of a specific document in the list by one
	void print_term_info();//prints the informatio about a term

	Term_Info& operator =(Term_Info& term_in);//overloaded assignment opperator
	list<Doc_Info>* get_list();//returns a pointer pointing to the list of the documents

	int get_no_of_docs();//returns the number of documents in the list

	~Term_Info();//destructor
};


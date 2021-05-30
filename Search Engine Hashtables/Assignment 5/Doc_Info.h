#pragma once
#include<string.h>
#include<iostream>

using namespace std;

//this class is used to store information about a document
class Doc_Info
{
private:

	int pr_term_fre;//frequency of the term
	string pr_doc_id;// name of the document

public:

	Doc_Info();//default constructor
	Doc_Info(int frequency, string doc_id);//parameterized constructor
	Doc_Info(int frequency, string doc_id, Doc_Info* next, Doc_Info* pre);//parameterized constructor
	Doc_Info(Doc_Info& obj_in);//copy constructor

	friend class Term_Info;

	void set_frequency(int frequency);//sets the frequency of the term
	void set_doc_id(string id);//sets the name of the document
	void increment_frequency();//increment the document frequency by one

	int get_word_frequency();//return the frequency of the document
	string get_doc_id();//return the name of the document

	Doc_Info& operator = (const Doc_Info& obj_in);//overloded assignemnt operator

	~Doc_Info();//destructor
};


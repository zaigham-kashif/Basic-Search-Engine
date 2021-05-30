#pragma once
#include<string.h>
#include<iostream>

using namespace std;

class Doc_Info
{
private:

	int pr_term_fre;
	string pr_doc_id;
	Doc_Info* pr_next;
	Doc_Info* pr_pre;


public:

	Doc_Info();
	Doc_Info(int frequency, string doc_id);
	Doc_Info(int frequency, string doc_id, Doc_Info* next, Doc_Info* pre);

	friend class Term_Info;

	void set_frequency(int frequency);
	void set_doc_id(string id);
	void increment_frequency();

	int get_word_frequency();
	string get_doc_id();

	~Doc_Info();
};


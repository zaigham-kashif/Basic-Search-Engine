#include "Doc_Info.h"
#include<iostream>
#include<string.h>

using namespace std;



Doc_Info::Doc_Info()
{
	pr_term_fre = 0;
	pr_doc_id = "\0";
	pr_next = nullptr;
	pr_pre = nullptr;
}

Doc_Info::Doc_Info(int frequency, string doc_id)
{
	pr_doc_id = doc_id;
	pr_term_fre = frequency;
	pr_next = nullptr;
	pr_pre = nullptr;
}

Doc_Info::Doc_Info(int frequency, string doc_id, Doc_Info* next, Doc_Info* pre)
{
	pr_doc_id = doc_id;
	pr_term_fre = frequency;
	pr_next = next;
	pr_pre = pre;
}

void Doc_Info::set_frequency(int frequency)
{
	pr_term_fre = frequency;
}

void Doc_Info::set_doc_id(string id)
{
	pr_doc_id = id;
}

void Doc_Info::increment_frequency()
{
	pr_term_fre++;
}

int Doc_Info::get_word_frequency()
{
	return pr_term_fre;
}

string Doc_Info::get_doc_id()
{
	return pr_doc_id;
}

Doc_Info::~Doc_Info()
{
	pr_doc_id = "\0";
	pr_term_fre = 0;
}

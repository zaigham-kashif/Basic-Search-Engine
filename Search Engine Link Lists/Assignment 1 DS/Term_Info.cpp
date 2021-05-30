#include "Term_Info.h"
#include<iostream>

using namespace std;

class Term_Info_Iterator;
typedef Term_Info_Iterator T_Iterator;

Term_Info::Term_Info()
{
	pr_term = '\0';
	pr_no_of_docs = 0;

	pr_head = new Doc_Info();
	pr_tail = new Doc_Info();

	pr_head->pr_next = pr_tail;
	pr_tail->pr_pre = pr_head;
}

Term_Info::Term_Info(string term)
{
	pr_term = term;
	pr_no_of_docs = 0;

	pr_head = new Doc_Info();
	pr_tail = new Doc_Info();

	pr_head->pr_next = pr_tail;
	pr_tail->pr_pre = pr_head;
}

void Term_Info::add_doc_info(int frequency, string id)
{
	Doc_Info* temp_ptr = pr_tail->pr_pre;
	pr_tail->pr_pre = new Doc_Info(frequency, id,pr_tail,temp_ptr);
	temp_ptr->pr_next = pr_tail->pr_pre;

	pr_no_of_docs++;
}

void Term_Info::print_doc_info()
{
	T_Iterator TI1 = this->begin();
	cout << "	" << pr_term << " ->";
	while (TI1 != this->end())
	{
		cout << " Doc Name : " << TI1.get_ptr()->pr_doc_id << " || Frequency : " << TI1.get_ptr()->pr_term_fre;
		if (TI1 != pr_tail->pr_pre)
		{
			cout << "->";
		}

		TI1++;
	}
	cout << endl;
}

bool Term_Info::check_doc(string doc_id)
{

	Doc_Info* temp_ptr = pr_head->pr_next;

	while (temp_ptr != pr_tail)
	{

		if (temp_ptr->pr_doc_id == doc_id)
		{
			return true;
		}

		temp_ptr = temp_ptr->pr_next;
	}

	return false;
}

bool Term_Info::increment_frequency(string doc_id)
{
	Doc_Info* temp_ptr = pr_head->pr_next;

	while (temp_ptr != pr_tail)
	{

		if (temp_ptr->pr_doc_id == doc_id)
		{
			temp_ptr->pr_term_fre = temp_ptr->pr_term_fre + 1;
			return true;
		}

		temp_ptr = temp_ptr->pr_next;
	}

	return false;
}

bool Term_Info::is_empty()
{
	if (pr_term == "\0" || pr_no_of_docs == 0)
		return false;
	return true;
}

int Term_Info::no_of_doc()
{
	return pr_no_of_docs;
}

Doc_Info* Term_Info::get_head()
{
	return pr_head->pr_next;
}

Doc_Info* Term_Info::get_tail()
{
	return pr_tail;
}

Doc_Info* Term_Info::inc_ptr(Doc_Info* ptr_in)
{
	ptr_in = ptr_in->pr_next;
	return ptr_in;
}

Doc_Info* Term_Info::search_doc(string doc_id)
{

	Doc_Info* temp_ptr = pr_head->pr_next;

	while (temp_ptr != pr_tail)
	{
		if (temp_ptr->pr_doc_id == doc_id)
		{
			return temp_ptr;
		}

		temp_ptr = temp_ptr->pr_next;
	}

	return nullptr;
}

Term_Info::~Term_Info()
{
	Doc_Info* temp_ptr = pr_head;

	while (temp_ptr != nullptr)
	{
		temp_ptr = temp_ptr->pr_next;
		delete pr_head;
		pr_head = temp_ptr;
	}

	pr_tail = nullptr;
	pr_no_of_docs = 0;
}


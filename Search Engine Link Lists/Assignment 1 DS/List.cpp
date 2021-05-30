#include "List.h"
#include<iostream>

using namespace std;

class list_iterator;
typedef list_iterator Iterator;

List::List()
{
	pr_head = nullptr;
	pr_tail = nullptr;
	pr_no_of_term = 0;
}


void List::add_term(string term)
{
	if (pr_head == nullptr && pr_tail == nullptr)
	{
		pr_head = new Term_Info(term);
		pr_tail = pr_head;

		pr_no_of_term++;
	}
	else if (pr_head == pr_tail)
	{
		pr_tail = new Term_Info(term);
		pr_head->pr_next = pr_tail;
		pr_tail->pr_pre = pr_head;

		pr_no_of_term++;
	}
	else 
	{
		Term_Info* temp_ptr = pr_tail;
		pr_tail= new Term_Info(term);
		pr_tail->pr_pre = temp_ptr;
		temp_ptr->pr_next = pr_tail;

		pr_no_of_term++;
	}
}

Term_Info* List::search_term(string term)
{
	Term_Info* temp_ptr = pr_head;

	while (temp_ptr != nullptr)
	{
		if (temp_ptr->pr_term == term)
		{
			return temp_ptr;
		}

		temp_ptr = temp_ptr->pr_next;
	}

	return nullptr;
}

void List::add_doc_info(string term, string doc_id, int frequency)
{
	Term_Info* temp_ptr = this->search_term(term);

	if (temp_ptr!= nullptr)
	{
		temp_ptr->add_doc_info(frequency,doc_id);
	}
}

void List::update(string term, string doc_id)
{
	Term_Info* temp_ptr = this->search_term(term);

	if (temp_ptr != nullptr)
	{
		Doc_Info* temp_doc_ptr;
		temp_doc_ptr = temp_ptr->search_doc(doc_id);

		if (temp_doc_ptr == nullptr)
		{
			temp_ptr->add_doc_info(1, doc_id);
		}
		else
		{
			temp_doc_ptr->increment_frequency();
		}
	}
	else
	{
		this->add_term(term);
		pr_tail->add_doc_info(1, doc_id);
	}
}

void List::print_list()
{
	Iterator I1=this->begin();

	while (I1 != this->end())
	{
		I1.get_ptr()->print_doc_info();
		if (I1 != pr_tail)
		{
			cout << "	 |" << endl;
			cout << "	\\_/" << endl;
		}

		I1++;
	}

	cout << endl;
	cout << endl;
	cout << "	Total Terms:" << pr_no_of_term << endl;
}

List::~List()
{
	Term_Info* temp_ptr = pr_head;

	while (temp_ptr!=nullptr)
	{
		temp_ptr = temp_ptr->pr_next;
		delete pr_head;
		pr_head = temp_ptr;
	}

	pr_tail = nullptr;
	pr_no_of_term = 0;
}

List::list_iterator::list_iterator()
{
	pr_i_ptr = nullptr;
}

List::list_iterator::list_iterator(Term_Info* ptr_in)
{
	pr_i_ptr = ptr_in;
}


#pragma once
#include<string>
#include"Doc_Info.h"
#include"Term_Info.h"

using namespace std;

class Term_Info
{
private:

	string pr_term;
	Doc_Info* pr_head;
	Doc_Info* pr_tail;
	int  pr_no_of_docs;
	Term_Info* pr_next;
	Term_Info* pr_pre;

	class Term_Info_Iterator
	{
	private:
		Doc_Info* pr_i_ptr;
	public:
		Term_Info_Iterator()
		{
			pr_i_ptr = nullptr;
		}

		Term_Info_Iterator(Doc_Info* ptr_in)
		{
			pr_i_ptr = ptr_in;
		}

		Term_Info_Iterator& operator++()
		{
			if (pr_i_ptr != nullptr)
				pr_i_ptr = pr_i_ptr->pr_next;

			return *this;
		}
		Term_Info_Iterator& operator++(int)
		{
			if (pr_i_ptr != nullptr)
			{
				Term_Info_Iterator old = *this;
				++(*this);

				return old;
			}
		}

		Term_Info_Iterator& operator--()
		{
			if (pr_i_ptr != nullptr)
				pr_i_ptr = pr_i_ptr->pr_pre;

			return *this;
		}
		Term_Info_Iterator& operator--(int)
		{
			if (pr_i_ptr != nullptr)
			{
				Term_Info_Iterator old = *this;
				--(*this);

				return old;
			}
		}

		Doc_Info* get_ptr()
		{
			return pr_i_ptr;
		}

		bool operator == (const Term_Info_Iterator& Ite_in) const
		{
			return pr_i_ptr == Ite_in.pr_i_ptr;
		}

		bool operator != (const Term_Info_Iterator& Ite_in) const
		{
			return !(pr_i_ptr == Ite_in.pr_i_ptr);
		}

		Term_Info_Iterator& operator =(const Term_Info_Iterator& Ite_in)
		{
			pr_i_ptr = Ite_in.pr_i_ptr;
			return *this;
		}
	};

public:
	typedef Term_Info_Iterator T_Iterator;
	T_Iterator begin()
	{
		T_Iterator I(pr_head->pr_next);
		return I;
	}

	T_Iterator end()
	{
		T_Iterator I(pr_tail);
		return I;
	}

	Term_Info();
	Term_Info(string term);

	friend class List;

	void add_doc_info(int frequency, string id);
	void print_doc_info();

	bool check_doc(string doc_id);
	bool increment_frequency(string doc_id);
	bool is_empty();
	int no_of_doc();
	Doc_Info* get_head();
	Doc_Info* get_tail();
	Doc_Info* inc_ptr(Doc_Info* ptr_in);
	Doc_Info* search_doc(string doc_id);

	~Term_Info();
};


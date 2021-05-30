#pragma once
#include"Term_Info.h"

class List
{
private:
	Term_Info* pr_head;
	Term_Info* pr_tail;
	int pr_no_of_term;

	class list_iterator
	{
	private:
		Term_Info* pr_i_ptr;
	public:
		list_iterator();
		list_iterator(Term_Info* ptr_in);

		list_iterator& operator++()
		{
			if(pr_i_ptr!=nullptr)
				pr_i_ptr = pr_i_ptr->pr_next;

			return *this;
		}
		list_iterator& operator++(int)
		{
			if (pr_i_ptr != nullptr)
			{
				list_iterator old = *this;
				++(*this);

				return old;
			}
		}

		list_iterator& operator--()
		{
			if (pr_i_ptr != nullptr)
				pr_i_ptr = pr_i_ptr->pr_pre;

			return *this;
		}
		list_iterator& operator--(int)
		{
			if (pr_i_ptr != nullptr)
			{
				list_iterator old = *this;
				--(*this);

				return old;
			}
		}

		Term_Info* get_ptr()
		{
			return pr_i_ptr;
		}

		Doc_Info* operator*()
		{
			return pr_i_ptr->pr_head;
		}

		bool operator == (const list_iterator& Ite_in) const
		{
			return pr_i_ptr == Ite_in.pr_i_ptr;
		}

		bool operator != (const list_iterator& Ite_in) const
		{
			return !(pr_i_ptr == Ite_in.pr_i_ptr);
		}

		list_iterator& operator =(list_iterator& Ite_in)
		{
			pr_i_ptr = Ite_in.pr_i_ptr;
		}
	};

public:
	typedef list_iterator Iterator;

	Iterator begin()
	{
		Iterator I(pr_head);
		return I;
	}
	Iterator end()
	{
		Iterator I(nullptr);
		return I;
	}

	List();

	void add_term(string term);
	Term_Info* search_term(string term);

	void add_doc_info(string term, string doc_id, int frequency);
	void update(string term,string doc_id);
	void print_list();

	~List();

};


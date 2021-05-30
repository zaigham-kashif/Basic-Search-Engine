#pragma once
#include"Node.h"
#include<iostream>

using namespace std;

// a template list class
template<typename any>
class list
{
private:

	node<any>* pr_start;	 //points to the start of th list
	node<any>* pr_end;		//points to the end of the list
	int pr_number_of_nodes;//total number of nodes in the list


	//iterator class for the tree
	class list_iterator
	{
	private:
		node<any>* pr_i_ptr;//points to a node

	public:
		list_iterator()//default constructor
		{
			pr_i_ptr = nullptr;
		}

		list_iterator(node<any>* ptr_in)//parameterized constructor
		{
			pr_i_ptr = ptr_in;
		}

		list_iterator operator++()//postfix addition operator overload
		{
			if (pr_i_ptr)
				pr_i_ptr = pr_i_ptr->pr_next;
			

			return *this;
		}

		list_iterator operator++(int)//prefix addition operator overload
		{
			if (pr_i_ptr)
			{
				node<any>* old = pr_i_ptr;
				++(*this);

				return old;
			}

			return *this;
		}

		any& operator*()//derefrance operator overload
		{
			return pr_i_ptr->pr_data;
		}

		node<any>* get_ptr()//funtion to get pr_i_ptr
		{
			return pr_i_ptr;
		}

		bool operator ==(const list_iterator& ite_in) const//eqal to operator overload
		{
			return pr_i_ptr == ite_in.pr_i_ptr;
		}

		bool operator !=(const list_iterator& ite_in)const//not equal to operator overload
		{
			return !(pr_i_ptr == ite_in.pr_i_ptr);
		}

		list_iterator& operator =(const list_iterator& ite_in)//assignment operator overload
		{
			pr_i_ptr = ite_in.pr_i_ptr;
			return *this;
		}
	};

public:
	typedef list_iterator l_iterator;

	l_iterator begin()//return an itertor with its pointer set at the start of the list
	{
		l_iterator I(pr_start);
		return I;
	}

	l_iterator end()//return an itertor with its pointer set at the end of the list
	{
		l_iterator I(pr_end);
		return I;
	}

	list()// default constructor
	{
		pr_start = nullptr;
		pr_end = nullptr;
		pr_number_of_nodes = 0;
	}

	list(list<any>& list_in)//copy constructor
	{
		node<any>* temp_ptr = list_in.pr_start;

		while (temp_ptr != nullptr)
		{
			this->add_node_at_end(temp_ptr->pr_data);
			temp_ptr = temp_ptr->pr_next;
		}
	}

	void add_node_at_end(any& data)//adds node at end of the list
	{
		if (pr_start == nullptr && pr_end == nullptr)
		{
			pr_start = pr_end = new node<any>(data, nullptr);
		}
		else
		{
			pr_end->pr_next = new node<any>(data, nullptr);
			pr_end= pr_end->pr_next;
		}
		pr_number_of_nodes++;
	}

	void add_node_at_start(any& data)//add node at start of the list
	{
		if (pr_start == nullptr && pr_end == nullptr)
		{
			pr_start = pr_end = new node<any>(data, nullptr);
		}
		else
		{
			pr_start= new node<any>(data, pr_start);
		}
		pr_number_of_nodes++;
	}

	bool is_empty()//cheacks if list if empty
	{
		return pr_start == 0;
	}

	void print_list()//prints the list
	{
		node<any>* temp_ptr = nullptr;

		temp_ptr = pr_start;

		while (temp_ptr != nullptr)
		{
			if (temp_ptr != pr_start && temp_ptr!= nullptr)
			{
				cout << "->";
			}
			cout << " " << temp_ptr->pr_data << " ";
			temp_ptr = temp_ptr->pr_next;
		}
		cout << endl;
	}

	node<any>* find(any value)//searches for a value in the list
	{
		node<any>* temp_ptr = nullptr;

		temp_ptr = pr_start;

		while (temp_ptr!=nullptr)
		{
			if (temp_ptr->pr_data == value)
			{
				return temp_ptr;
			}
			else
			{
				temp_ptr = temp_ptr->pr_next;
			}
		}

		return nullptr;
	}

	list<any>& operator =(const list<any>& list_in)//overloaded assignment operator
	{
		this->~list();

		node<any>* temp_ptr = list_in.pr_start;

		while (temp_ptr != nullptr)
		{
			this->add_node_at_end(temp_ptr->pr_data);
			temp_ptr = temp_ptr->pr_next;
		}

		return *this;
	}

	int get_no_nodes()//returns the total number of nodes in the list
	{
		return pr_number_of_nodes;
	}


	~list()//destructor
	{
		if (pr_start != nullptr && pr_end != nullptr)
		{
			if (pr_start == pr_end)
			{
				delete pr_start;
				pr_start = pr_end = nullptr;
			}
			else
			{
				node<any>* temp_ptr = nullptr;
				while (pr_start != 0)
				{
					temp_ptr = pr_start->pr_next;
					delete pr_start;
					pr_start = temp_ptr;
				}

				pr_start = pr_end = nullptr;
			}
		}
	}

};

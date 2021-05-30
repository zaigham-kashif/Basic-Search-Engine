#pragma once

//node class for the list class
template<typename any>
class node
{
private:
	any pr_data;//data of any type
	node<any> *pr_next;//a pointer pointing to the next node in the list

public:

	node()//default constructor
	{
		pr_data = 0;
		pr_next = nullptr;
	}

	node(any data, node<any>* ptr)////parameterrized constructor
	{
		pr_data = data;
		pr_next = ptr;
	}

	~node()//dec=structor
	{
		pr_next = nullptr;
	}

	template<typename any>
	friend class list;
};



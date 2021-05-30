#pragma once

// a node class for AVLtree
template<typename T1,typename T2>
class AVLnode
{
private:
	T1 pr_key;//stores the key 
	T2 pr_data;//stores the data
	int pr_height;//stores height of the tree
	AVLnode* pr_left;//points to the left of the node
	AVLnode* pr_right;//points to the right of the node

public:

	AVLnode()//default constructor
	{
		pr_key = 0;
		pr_height = 0;
		pr_left = nullptr;
		pr_right = nullptr;
	}

	AVLnode(T1& key, T2& data, int height)//parameterized constructor
	{
		pr_key = key;
		pr_data = data;
		pr_height = height;
		pr_left = 0;
		pr_right = 0;
	}


	AVLnode(T1 key,T2 data, int height, AVLnode<T1, T2>* left, AVLnode<T1, T2>* right)//parameterized constructor
	{
		pr_key = key;
		pr_data = data;
		pr_height = height;
		pr_left = left;
		pr_right = right;
	}

	void inc_height()//increments the height of the tree by one 
	{
		pr_height++;
	}

	T2* get_data()//returns a refrance to the data of a node
	{
		return &pr_data;
	}

	T1* get_key()//returns a refrance to the key of a node
	{
		return &pr_key;
	}

	int get_height()//return the height of a node
	{
		return pr_height;
	}

	AVLnode<T1, T2>* get_right()//returns the pointer pointing to the right of the node
	{
		return pr_right;
	}

	AVLnode<T1, T2>* get_left()//returns the pointer pointing to the left of the node
	{
		return pr_left;
	}

	~AVLnode()//destructor
	{
		pr_height = 0;
		pr_left = nullptr;
		pr_right = nullptr;
	}

	template<typename T1,typename T2>
	friend class AVLTree;
};


#pragma once
#include"AVLnode.h"
#include<iostream>

using namespace std;

//a template class for AVL tree
template<typename T1, typename T2>
class AVLTree
{
private:
	AVLnode<T1, T2>* pr_root;//points to the root of a tree
	int pr_noof_nodes;//total number of nodes in a tree

	void insert(T1& key, T2& data, AVLnode<T1, T2>*& temp_root)//to insert data into tree
	{
		if (temp_root == nullptr)
		{
			temp_root = new AVLnode<T1, T2>(key, data, 0);
			pr_noof_nodes++;
		}
		else
		{
			if (key < temp_root->pr_key)
			{
				insert(key, data, temp_root->pr_left);
				if (temp_root->pr_right == nullptr)
					temp_root->inc_height();
				else if (temp_root->pr_right->pr_height < temp_root->pr_left->pr_height)
					temp_root->inc_height();
				
				balance(temp_root);
			}
			else if (key > temp_root->pr_key)
			{
				insert(key, data, temp_root->pr_right);
				if (temp_root->pr_left == nullptr)
					temp_root->inc_height();
				else if (temp_root->pr_left->pr_height < temp_root->pr_right->pr_height)
					temp_root->inc_height();

				balance(temp_root);
			}
		}
	}

	void balance(AVLnode<T1, T2>* &temp_root)//a function to balance the tree
	{
		int height_left = 0, height_right = 0;//height of left and right of the tree
		int height_right_right = 0;//height of right of right of the tree
		int height_right_left = 0;// height of left of right of the tree
		int height_left_left = 0;// height of left of left of the tree
		int height_left_right = 0;// height of right of left of the tree

		//checks to determine the heights of left part of the tree
		if (temp_root->pr_left == nullptr) {
			height_left = -1;
			height_left_left = -2;
			height_left_right = -2;
		}
		else {
			height_left = temp_root->pr_left->pr_height;

			if (temp_root->pr_left->pr_left == nullptr)
				height_left_left = -1;
			else
				height_left_left = temp_root->pr_left->pr_left->pr_height;

			if (temp_root->pr_left->pr_right == nullptr)
				height_left_right = -1;
			else
				height_left_right = temp_root->pr_left->pr_right->pr_height;
		}

		//checks to determine the heights of right part of the tree
		if (temp_root->pr_right == nullptr) {
			height_right = -1;
			height_right_right = -2;
			height_right_left = -2;

		}
		else {
			height_right = temp_root->pr_right->pr_height;

			if (temp_root->pr_right->pr_left == nullptr)
				height_right_left = -1;
			else	   
				height_right_left = temp_root->pr_right->pr_left->pr_height;

			if (temp_root->pr_right->pr_right == nullptr)
				height_right_right = -1;
			else
				height_right_right = temp_root->pr_right->pr_right->pr_height;
		}

		if (height_right - height_left >= 2)// cheak if tree is imbalanced from the right side
		{
			if (height_right_left >= height_right_right)// cheak for a zig zag pattern
			{
				rotate_right(temp_root->pr_right);
			}

			if (temp_root == pr_root)
			{
				rotate_left(pr_root);
			}
			else
			{
				rotate_left(temp_root);
			}
		}
		else if (height_right - height_left <= -2)// cheak if tree is imbalanced from the left side
		{
			if (height_left_right >= height_left_left)//cheak for a zig zag pattern
			{
				rotate_left(temp_root->pr_left);
			}

			if (temp_root == pr_root)
			{
				rotate_right(pr_root);
			}
			else
			{
				rotate_right(temp_root);
			}
		}

		temp_root->pr_height = height(temp_root);// update the height
	}

	void print_tree_l(AVLnode<T1, T2>* temp_root)//prints tree in a linear form
	{
		if (temp_root)
		{
			print_tree_l(temp_root->pr_left);
			std::cout << "	{" << temp_root->pr_key << " , " << temp_root->pr_height << " , " << temp_root->pr_data << " }" << std::endl;
			print_tree_l(temp_root->pr_right);
		}
	}

	void rotate_right(AVLnode<T1, T2>* &temp_root)//rotates the tree right from of given point i.e temp_root
	{
		AVLnode<T1, T2>* orphan = temp_root->pr_left->pr_right;
		AVLnode<T1, T2>* old_left = temp_root->pr_left;

		old_left->pr_right = temp_root;
		temp_root->pr_left = orphan;

		temp_root->pr_height = height(temp_root);
		old_left->pr_height = height(old_left);

		temp_root = old_left;
	}

	void rotate_left(AVLnode<T1, T2>* &temp_root)//rotates the tree left from of given point i.e temp_root
	{
		AVLnode<T1, T2>* orphan = temp_root->pr_right->pr_left;
		AVLnode<T1, T2>* old_right = temp_root->pr_right;

		old_right->pr_left = temp_root;
		temp_root->pr_right = orphan;

		temp_root->pr_height = height(temp_root);
		old_right->pr_height = height(old_right);

		temp_root = old_right;
	}

	int height(AVLnode<T1, T2>* temp_ptr)//returns the updated height of a node 
	{
		int height;
		if (temp_ptr->pr_left != nullptr && temp_ptr->pr_right != nullptr)
		{
			if (temp_ptr->pr_left->pr_height < temp_ptr->pr_right->pr_height)
				height = temp_ptr->pr_right->pr_height;
			else
				height = temp_ptr->pr_left->pr_height;
		}
		else if (temp_ptr->pr_left == nullptr && temp_ptr->pr_right == nullptr)
		{
			return 0;
		}
		else if(temp_ptr->pr_left==nullptr)
		{
			height = temp_ptr->pr_right->pr_height;
		}
		else if (temp_ptr->pr_right == nullptr)
		{
			height = temp_ptr->pr_left->pr_height;
		}

		return ++height;
	}

	bool remove(int key, AVLnode<T1, T2>*& temp_root)//removes a given node from the tree
	{
		if (temp_root == nullptr)
		{
			return false;
		}
		if (key < temp_root->pr_key)
			remove(key, temp_root->pr_left);
		else if (key > temp_root->pr_key)
			remove(key, temp_root->pr_right);
		else if (temp_root->pr_left != nullptr && temp_root->pr_right != nullptr)
		{
			temp_root->pr_key = min(temp_root->pr_right);
			remove(temp_root->pr_key, temp_root->pr_right);
		}
		else
		{
			AVLnode<T1, T2>* old = temp_root;
			if (temp_root->pr_left != nullptr)
				temp_root = temp_root->pr_left;
			else
				temp_root = temp_root->pr_right;

			delete old;
			pr_noof_nodes--;
		}
		if (temp_root != nullptr)
			balance(temp_root);
	}

	void search(T1 key, AVLnode<T1, T2>* temp_ptr, AVLnode<T1, T2>* &ptr)//searches for a given value in the tree
	{
		if (temp_ptr == nullptr)
		{
			ptr = nullptr;
		}
		else if (temp_ptr->pr_key == key)
		{
			ptr = temp_ptr;
		}
		else if (key>temp_ptr->pr_key)
		{
			search(key, temp_ptr->pr_right, ptr);
		}
		else if (key<temp_ptr->pr_key)
		{
			search(key, temp_ptr->pr_left, ptr);
		}
	}

	void delete_tree(AVLnode<T1, T2>* temp_root)//deletes the tree node by node
	{
		if (temp_root == nullptr)
		{
			return;
		}
		else
		{
			delete_tree(temp_root->pr_left);
			delete_tree(temp_root->pr_right);
			delete temp_root;
		}
	}

public:
	AVLTree()//default constructor
	{
		pr_root = nullptr;
		pr_noof_nodes = 0;
	}

	void insert(T1& key, T2& data)// parameterized constructor
	{
		if (pr_root == nullptr)
		{
			pr_root = new AVLnode<T1, T2>(key, data, 0);
			pr_noof_nodes++;
		}
		else
		{
			AVLnode<T1, T2>* temp_root = pr_root;
			insert(key, data, temp_root);
		}
	}

	void print_tree_l()//prints the tree
	{
		AVLnode<T1, T2>* temp_root = pr_root;
		print_tree_l(temp_root);
	}

	void deletedata(T1 key)// deletes a given node
	{
		AVLnode<T1, T2>* temp_root = pr_root;
		remove(key, temp_root);
	}

	int get_no_of_nodes()// return number of nodes
	{
		return pr_noof_nodes;
	}

	AVLnode<T1, T2>* get_root()// returns the root of the tree
	{
		return pr_root;
	}


	AVLnode<T1, T2>* search(T1 key)//searches for a specific node
	{
		AVLnode<T1, T2>* temp_root = pr_root;
		AVLnode<T1, T2>* ptr;

		search(key, temp_root, ptr);
		return ptr;
	}

	~AVLTree()//destructor
	{
		AVLnode<T1, T2>* temp_root = pr_root;
		delete_tree(temp_root);
	}
};


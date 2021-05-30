#include "Hash_Table.h"

using namespace std;

bool is_prime(int no)
{
	for (int i = 2; i < no - 1; i++)
	{
		if (no % i == 0)
			return false;
	}
	return true;
}

int next_prime(int no)
{
	int pr = no;
	while (is_prime(pr) == false)
	{
		pr++;
	}

	return pr;
}

int Hash_Table::hash_function(string word)
{
	int seed = (word[0] + word[word.length() - 1]) * word[word.length() / 2];
	//seed = next_prime(seed);

	unsigned long hash = 0;
	for (int i = 0; i < word.length(); i++)
	{
		hash = (hash * seed) + word[i];
	}
	return hash % pr_max_size;
}

void Hash_Table::expand_insert(list<Term_Info>** hash_table, Term_Info& term_info)
{
	int index = hash_function(term_info.get_term());
	if (hash_table[index] == nullptr)
	{
		hash_table[index] = new list<Term_Info>;
		hash_table[index]->add_node_at_end(term_info);

		pr_current_size++;
	}
	else
	{
		hash_table[index]->add_node_at_end(term_info);
	}
}

Hash_Table::Hash_Table()
{
	pr_hash_table = nullptr;
	pr_current_size = 0;
	pr_max_size = 0;
}

Hash_Table::Hash_Table(int max_size)
{
	pr_max_size = max_size;
	pr_current_size = 0;
	pr_hash_table = new list<Term_Info> * [max_size];
	for (int i = 0; i < pr_max_size; i++)
	{
		pr_hash_table[i] = nullptr;
	}
}

void Hash_Table::set_size(int size)
{
	pr_max_size = size;
	pr_current_size = 0;
	pr_hash_table = new list<Term_Info> * [pr_max_size];
	for (int i = 0; i < pr_max_size; i++)
	{
		pr_hash_table[i] = nullptr;
	}
}

void Hash_Table::insert(string term, string doc_id)
{
	if (pr_current_size > pr_max_size * 0.75)
	{
		this->expand();
	}

	int index = hash_function(term);
	if (pr_hash_table[index] == nullptr)
	{
		pr_hash_table[index] = new list<Term_Info>;
		Term_Info data(term, doc_id);
		pr_hash_table[index]->add_node_at_end(data);

		pr_current_size++;
	}
	else
	{
		bool term_flag = 0;
		for (list<Term_Info>::l_iterator i = pr_hash_table[index]->begin(); i != nullptr; i++)
		{
			if (i.get_ptr()->get_data()->get_term() == term)
			{
				bool doc_flag = 0;
				for (list<Doc_Info>::l_iterator j = i.get_ptr()->get_data()->get_list()->begin(); j != nullptr; j++)
				{
					if (j.get_ptr()->get_data()->get_doc_id() == doc_id)
					{
						j.get_ptr()->get_data()->increment_frequency();
						doc_flag = 1;
						break;
					}
				}

				if (doc_flag == 0)
				{
					i.get_ptr()->get_data()->add_doc(doc_id);
				}

				term_flag = 1;
				break;
			}
		}

		if (term_flag == 0)
		{
			Term_Info data(term, doc_id);
			pr_hash_table[index]->add_node_at_end(data);
		}
	}
}

void Hash_Table::expand()
{
	int old_size = pr_max_size;
	pr_max_size = pr_max_size * 2;
	list<Term_Info>** hash_table = new list<Term_Info> * [pr_max_size];
	for (int i = 0; i < pr_max_size; i++)
	{
		hash_table[i] = nullptr;
	}

	pr_current_size = 0;
	for (int i = 0; i < old_size; i++)
	{
		if (pr_hash_table[i] != nullptr)
		{
			for (list<Term_Info>::l_iterator ite = pr_hash_table[i]->begin(); ite != nullptr; ite++)
			{
				expand_insert(hash_table, *ite.get_ptr()->get_data());
			}
		}
	}

	for (int i = 0; i < old_size; i++)
	{
		if (pr_hash_table[i] != nullptr)
			delete pr_hash_table[i];
	}

	pr_hash_table = hash_table;
}

void Hash_Table::print_table()
{
	cout << "	" << pr_max_size << endl;
	for (int i = 0; i < pr_max_size; i++)
	{
		if (pr_hash_table[i] != nullptr)
		{
			cout << "	|_______________________________________________________________________________" << endl;
			for (list<Term_Info>::l_iterator ite = pr_hash_table[i]->begin(); ite != nullptr; ite++)
			{
				cout << "	|" << i << "|";
				ite.get_ptr()->get_data()->print_term_info();
			}
			cout << "	|_______________________________________________________________________________" << endl;
		}
	}
}

list<Doc_Info>* Hash_Table::search(string term)
{
	int index = hash_function(term);

	for (list<Term_Info>::l_iterator ite = pr_hash_table[index]->begin(); ite != nullptr; ite++)
	{
		if (ite.get_ptr()->get_data()->get_term() == term)
		{
			return ite.get_ptr()->get_data()->get_list();
		}
	}

	return nullptr;
}

Hash_Table::~Hash_Table()
{
	for (int i = 0; i < pr_max_size; i++)
	{
		if (pr_hash_table[i] != nullptr)
			delete pr_hash_table[i];
	}
}

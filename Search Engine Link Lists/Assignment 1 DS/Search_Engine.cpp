#include "Search_Engine.h"
#include"Term_Info.h"
#include"QueryInfo.h"
#include<fstream>
#include<iostream>

using namespace std;

char** tokenizer(string query,int& size)
{
	char** tokens;

	for (unsigned int i = 0; i < query.size(); i++)
	{
		if (query[i] == ' ')
		{
			size++;
		}
	}
	size++;

	tokens = new char* [size];
	for (int i = 0; i < size; i++)
	{
		tokens[i] = new char[25];
	}

	int counter = 0;
	int i = 0;
	for (unsigned int j = 0; j < query.size(); j++)
	{
		if(query[j] != ' ' && query[j] != '\0')
		{
			tokens[counter][i] = query[j];
			if (tokens[counter][i] >= 65 && tokens[counter][i] <= 90)
			{
				tokens[counter][i] = tokens[counter][i] + 32;
			}
			i++;
		}

		if (query[j] == ' ')
		{
			tokens[counter][i] = '\0';
			i = 0;
			counter++;
		}
	}
	tokens[counter][i] = '\0';

	return tokens;

}

string doc_tokenizer(string str_in)
{
	int size = str_in.size();
	char* token_str;
	int start = 0, end = 0;

	for (int i = 0; i < size; i++)
	{
		if (str_in[i] == '\\')
		{
			start = i;
		}

		if (str_in[i] == '.')
		{
			end = i;
		}
	}

	token_str = new char[end - start];
	size = 0;
	for (int i = start + 1; i < end; i++)
	{
		token_str[size] = str_in[i];
		size++;
	}
	token_str[size] = '\0';
	return token_str;
}


int find_query_info(QueryInfo** arr,int size,string doc_name)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i][0].get_doc_name() == doc_name)
		{
			return i;
		}
	}
	return -1;
}

void sort_query_info(QueryInfo**& arr, int size)
{
	QueryInfo *temp_ptr = nullptr;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - 1; j++)
		{
			if (arr[j][0].get_frequency() > arr[j + 1][0].get_frequency())
			{
				temp_ptr = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp_ptr;
			}
			else if (arr[j][0].get_frequency() == arr[j + 1][0].get_frequency()&& arr[j][0].get_rank() > arr[j + 1][0].get_rank())
			{
				temp_ptr = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp_ptr;
			}
			else if (arr[j][0].get_frequency() == arr[j + 1][0].get_frequency() && arr[j][0].get_rank() == arr[j + 1][0].get_rank()&& arr[j][0].get_doc_name() < arr[j + 1][0].get_doc_name())
			{
				temp_ptr = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp_ptr;
			}
		}
	}
}


Search_Engine::Search_Engine()
{

}

void Search_Engine::Creat_Index(string file_name[], int size_of_array)
{
	ifstream fin;
	string data, doc_id;


	for (int i = 0; i < size_of_array; i++)
	{
		fin.open(file_name[i]);
		doc_id = doc_tokenizer(file_name[i]);

		if (fin.is_open())
		{
			while (!fin.eof())
			{
				fin >> data;
				for (unsigned int i = 0; i < data.size(); i++)
				{
					if (data[i] >= 65 && data[i] <= 90)
					{
						data[i] = data[i] + 32;
					}
				}

				pr_List_of_Terms.update(data, doc_id);
			}
		}

		fin.close();
	}

}

Term_Info* Search_Engine::Search_Term(string term)
{
	Term_Info* temp_ptr = pr_List_of_Terms.search_term(term);
	return temp_ptr;
}

void Search_Engine::print_lists()
{
	pr_List_of_Terms.print_list();
}

void Search_Engine::Search_Documents(string query)
{
	int size = 0;
	char **tokens=tokenizer(query,size);

	Term_Info** Terms = new Term_Info * [size];
	Term_Info* temp_ptr;
	int term_no = 0;

	for (int i = 0; i < size; i++)
	{
		temp_ptr=pr_List_of_Terms.search_term(tokens[i]);

		if (temp_ptr != nullptr)
		{
			Terms[term_no] = temp_ptr;
			term_no++;
		}
	}

	int total_number_of_doc = 0;

	for (int i = 0; i < term_no; i++)
	{
		total_number_of_doc = total_number_of_doc + Terms[i]->no_of_doc();
	}


	int key = 0;
	QueryInfo** Info_Query = new QueryInfo * [total_number_of_doc];
	int no_of_Query_Terms = 0;
	Term_Info::T_Iterator Doc_iterator;

	for (int i = 0; i < term_no; i++)
	{
		Doc_iterator = Terms[i]->begin();
		for (;Doc_iterator!=Terms[i]->end();Doc_iterator++)
		{
			key = find_query_info(Info_Query, no_of_Query_Terms, Doc_iterator.get_ptr()->get_doc_id());
			if (key == -1)
			{
				Info_Query[no_of_Query_Terms] = new QueryInfo(Doc_iterator.get_ptr()->get_doc_id(), 1, Doc_iterator.get_ptr()->get_word_frequency());
				no_of_Query_Terms++;
			}
			else
			{
				Info_Query[key]->Inc_frequency(1);
				Info_Query[key]->Inc_rank(Doc_iterator.get_ptr()->get_word_frequency());
			}
		}
	}

	sort_query_info(Info_Query, no_of_Query_Terms);

	for (int i = no_of_Query_Terms-1; i >= 0; i--)
	{
		cout << "	Document Name :  " << Info_Query[i]->get_doc_name() << endl;
		cout << "	----------------------"<<endl;
	}

	if (no_of_Query_Terms == 0)
	{
		cout << endl;
		cout << "	No results found for this Query" << endl;
		cout << endl;
	}
}

Search_Engine::~Search_Engine()
{

}



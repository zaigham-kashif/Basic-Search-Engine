#include "Search_Engine.h"
#include"QueryInfo.h"

//this function recives documents name in formate "Documents/Doc1.txt" and returns in formate "Doc1"
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

//this function recives a string of words and returns a 2D array of typr char with each index containing a seprate word
//each word in the input string is seprate by a space
char** tokenizer(string query, int& size)
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
		if (query[j] != ' ' && query[j] != '\0')
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

//this fuctions searches for an object containg a provided document name from an array of objects of type query info
//if object is found function returs its index else returns -1
int find_query_info(QueryInfo** arr, int size, string doc_name)
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

//this function recives an array of objects of query info and sort the array according to the conditions given in the assignment
void sort_query_info(QueryInfo**& arr, int size)
{
	QueryInfo* temp_ptr = nullptr;

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
			else if (arr[j][0].get_frequency() == arr[j + 1][0].get_frequency() && arr[j][0].get_rank() > arr[j + 1][0].get_rank())
			{
				temp_ptr = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp_ptr;
			}
			else if (arr[j][0].get_frequency() == arr[j + 1][0].get_frequency() && arr[j][0].get_rank() == arr[j + 1][0].get_rank() && arr[j][0].get_doc_name() < arr[j + 1][0].get_doc_name())
			{
				temp_ptr = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp_ptr;
			}
		}
	}
}


Search_Engine::Search_Engine(int size)
{
	pr_hash_table.set_size(size);
}

void Search_Engine::create_index(string file_names[], int no)
{
	ifstream fin;
	string data, doc_id;


	for (int i = 0; i < no; i++)
	{
		fin.open(file_names[i]);
		doc_id = doc_tokenizer(file_names[i]);//name of file 

		if (fin.is_open())
		{
			while (!fin.eof())
			{
				fin >> data;// one word is read at a time

				//term is converted into lower case
				for (unsigned int i = 0; i < data.size(); i++)
				{
					if (data[i] >= 65 && data[i] <= 90)
					{
						data[i] = data[i] + 32;
					}
				}


				this->add_doc_to_index(data, doc_id);//tree is updated with respected to the specific term
			}
		}

		fin.close();//file is closed
	}
}

//prints the sorted array of the query terms
void print_result(QueryInfo** query_info,int no_of_query_terms)
{
	//sorted array is printed
	cout << "	Results : " << endl;
	for (int i = no_of_query_terms - 1; i >= 0; i--)
	{
		cout << "	**********" << endl;
		cout << "	Document Name :  " << query_info[i]->get_doc_name() << endl;
		cout << "	----------------------" << endl;
	}

	if (no_of_query_terms == 0)
	{
		cout << endl;
		cout << "	No results found for this Query" << endl;
		cout << endl;
	}
}



void Search_Engine::add_doc_to_index(string term, string doc_id)
{
	pr_hash_table.insert(term, doc_id);
}

void Search_Engine::print_hash_table()
{
	pr_hash_table.print_table();
}

void Search_Engine::search_query(string query, int no_of_doc)
{
	int no_of_tokens = 0;
	char** tokens = tokenizer(query, no_of_tokens);//given query is converted into tokens

	list<Doc_Info>* temp_l_ptr = nullptr;
	list<Doc_Info>** list_arr = new list<Doc_Info> * [no_of_tokens];
	int no_of_lists = 0;

	for (int i = 0; i < no_of_tokens; i++)
	{
		temp_l_ptr = pr_hash_table.search(tokens[i]);
		if (temp_l_ptr != nullptr)
		{
			list_arr[no_of_lists] = temp_l_ptr;
			no_of_lists++;
		}
	}

	QueryInfo** Query_Info = new QueryInfo * [no_of_doc];
	int no_of_query = 0;
	string doc_id;
	int frequency = 0;
	int key = 0;

	for (int i = 0; i < no_of_lists; i++)
	{
		for (list<Doc_Info>::l_iterator ite = list_arr[i]->begin(); ite != nullptr; ite++)
		{
			doc_id = ite.get_ptr()->get_data()->get_doc_id();
			frequency = ite.get_ptr()->get_data()->get_word_frequency();
			key = find_query_info(Query_Info, no_of_query, doc_id);

			if (key == -1)
			{
				Query_Info[no_of_query] = new QueryInfo(doc_id, 1, frequency);
				no_of_query++;
			}
			else
			{
				Query_Info[key]->Inc_frequency(1);
				Query_Info[key]->Inc_rank(frequency);
			}
		}
	}

	sort_query_info(Query_Info, no_of_query);
	print_result(Query_Info, no_of_query);
}


void Search_Engine::add_document(string *&name_of_files, string doc_name, int& no_of_files)
{
	string* temp_array = new string[no_of_files + 1];
	for (int i = 0; i < no_of_files; i++)
	{
		temp_array[i] = name_of_files[i];
	}
	temp_array[no_of_files] = doc_name;
	no_of_files++;

	delete[]name_of_files;
	name_of_files = nullptr;

	name_of_files = temp_array;
}

Search_Engine::~Search_Engine()
{

}




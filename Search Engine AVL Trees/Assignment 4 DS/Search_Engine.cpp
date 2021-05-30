#include<fstream>
#include "Search_Engine.h"
#include"QueryInfo.h"
#include"List.h"

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


Search_Engine::Search_Engine()
{

}

void Search_Engine::update_tree(string key, string doc_id)
{
	AVLnode<string, Term_Info>* temp_ptr = pr_tree.search(key);

	if (temp_ptr == nullptr)
	{
		Term_Info temp_term(key, doc_id);
		pr_tree.insert(key, temp_term);
	}
	else
	{
		if (temp_ptr->get_data()->find_doc_id(doc_id))
		{
			temp_ptr->get_data()->inc_frequency(doc_id);
		}
		else
		{
			temp_ptr->get_data()->add_doc(doc_id);
		}
	}
}

void Search_Engine::search_query(string query)
{
	int no_of_tokens = 0;
	char** tokens = tokenizer(query, no_of_tokens);//given query is converted into tokens

	Term_Info** terms = new Term_Info * [no_of_tokens];
	int term_no = 0;

	AVLnode<string, Term_Info>* temp_ptr;

	for (int i = 0; i < no_of_tokens; i++)
	{
		temp_ptr = pr_tree.search(tokens[i]);//each token is searched in the tree 

		if (temp_ptr)//if token is found a pointer pointing to the link list of its doc info is added to an array of of pointer of object of term_info
		{
			terms[term_no] = temp_ptr->get_data();
			term_no++;
		}
	}


	int total_no_of_doc = 0;

	for (int i = 0; i < term_no; i++)
	{
		total_no_of_doc = total_no_of_doc + terms[i]->get_no_of_docs();//total number of documents for the tokens is calculated
	}

	int key = 0;
	QueryInfo** query_info = new QueryInfo * [total_no_of_doc];// 2D array of objects of type query_info
	int no_of_query_terms = 0;
	Doc_Info temp_doc;

	for (int i = 0; i < term_no; i++)//this loop traverse through the array of terms
	{
		for (list<Doc_Info>::l_iterator doc_ptr(terms[i]->get_list()->begin()); doc_ptr != nullptr; doc_ptr++)//inner loop travers through the list of documents of each array
		{
			temp_doc = *doc_ptr;
			key = find_query_info(query_info, no_of_query_terms, temp_doc.get_doc_id());// a specific doc id is searched in the array of query_info
			if(key==-1)//if the doc is not found it is added to the array
			{
				query_info[no_of_query_terms] = new QueryInfo(temp_doc.get_doc_id(), 1, temp_doc.get_word_frequency());
				no_of_query_terms++;
			}
			else//else if the doc is found its frequency and rank is update
			{
				query_info[key]->Inc_frequency(1);
				query_info[key]->Inc_rank(temp_doc.get_word_frequency());
			}

		}
	}

	sort_query_info(query_info, no_of_query_terms);//array od query_info is sorted

	//sorted array is printed
	for (int i = no_of_query_terms - 1; i >= 0; i--)
	{
		cout << "	Results : " << endl;
		cout << "	**********"<<endl;
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

void Search_Engine::add_document(string*& name_of_files, string doc_name, int& no_of_files)
{
	string* temp_array = new string[no_of_files];
	for (int i = 0; i < no_of_files; i++)
	{
		temp_array[i] = name_of_files[i];
	}

	delete[]name_of_files;

	no_of_files++;
	name_of_files = new string[no_of_files];

	for (int i = 0; i < no_of_files - 1; i++)
	{
		name_of_files[i] = temp_array[i];
	}
	name_of_files[no_of_files - 1] = doc_name;
}

Search_Engine::~Search_Engine()
{

}


void Search_Engine::print_tree()
{
	AVLnode<string, Term_Info>* temp_root = pr_tree.get_root();
	print_tree_rec(temp_root);
}

void Search_Engine::print_tree_rec(AVLnode<string, Term_Info>* temp_root)
{
	if (temp_root)
	{
		print_tree_rec(temp_root->get_left());
		cout << "	Height : " << temp_root->get_height() << endl;
		temp_root->get_data()->print_term_info();
		cout << endl;
		print_tree_rec(temp_root->get_right());
	}
}

void Search_Engine::Create_Index(string file_name[], int size_of_array)
{
	ifstream fin;
	string data, doc_id;


	for (int i = 0; i < size_of_array; i++)
	{
		fin.open(file_name[i]);
		doc_id = doc_tokenizer(file_name[i]);//name of file 

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


				this->update_tree(data, doc_id);//tree is updated with respected to the specific term
			}
		}

		fin.close();//file is closed
	}

}






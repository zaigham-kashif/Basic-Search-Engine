#include "Term_Info.h"

Term_Info::Term_Info()
{
	pr_term = '\0';	
}

Term_Info::Term_Info(string& term, string& doc_id)
{
	Doc_Info temp_doc(1, doc_id);
	pr_term_info.add_node_at_start(temp_doc);

	pr_term = term;
}

void Term_Info::add_doc(string doc_id)
{
	Doc_Info temp_doc(1, doc_id);
	pr_term_info.add_node_at_end(temp_doc);
}

bool Term_Info::find_doc_id(string doc_id)
{
	Doc_Info temp_doc;

	for (list<Doc_Info>::l_iterator i(pr_term_info.begin()); i != nullptr; i++)
	{
		temp_doc = *i;
		if (temp_doc.get_doc_id() == doc_id)
			return true;
	}

	return false;
}

void Term_Info::inc_frequency(string doc_id)
{
	for (list<Doc_Info>::l_iterator i(pr_term_info.begin()); i != nullptr; i++)
	{
		Doc_Info& temp_doc = *i;
		if (temp_doc.get_doc_id() == doc_id)
			temp_doc.increment_frequency();
	}
}

void Term_Info::print_term_info()
{
	cout << "	" << pr_term;

	cout << " {";
	Doc_Info temp_doc;
	for (list<Doc_Info>::l_iterator i(pr_term_info.begin()); i != nullptr; i++)
	{
		temp_doc = *i;
		cout << " (" << temp_doc.get_doc_id() << " , " << temp_doc.get_word_frequency() << ") ";
	}
	cout << " }" << endl;
}

Term_Info& Term_Info::operator=(Term_Info& term_in)
{
	pr_term = term_in.pr_term;
	pr_term_info = term_in.pr_term_info;

	return *this;
}

list<Doc_Info>* Term_Info::get_list()
{
	return &pr_term_info;
}

string Term_Info::get_term()
{
	return pr_term;
}

int Term_Info::get_no_of_docs()
{
	return pr_term_info.get_no_nodes();
}

Term_Info::~Term_Info()
{
	pr_term = '\0';
}

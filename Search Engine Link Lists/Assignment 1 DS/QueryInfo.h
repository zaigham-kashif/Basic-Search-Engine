#pragma once

#include<string.h>
#include<iostream>

using namespace std;

class QueryInfo
{
private:
	string pr_doc_name;
	int pr_frequency;
	int pr_rank;

public:
	QueryInfo();
	QueryInfo(string doc_name, int frequency, int rank);

	void Inc_frequency(int inc);
	void Inc_rank(int inc);

	string get_doc_name();
	int get_frequency();
	int get_rank();

	friend class Search_Engine;
};


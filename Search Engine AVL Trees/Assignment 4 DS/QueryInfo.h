#pragma once

#include<string.h>
#include<iostream>

using namespace std;
//class to store infomation about a query word
class QueryInfo
{
private:
	string pr_doc_name;//name of the document
	int pr_frequency;//total number of times a word occuered in the document
	int pr_rank;//frequency of the document

public:
	QueryInfo();//default constructor
	QueryInfo(string doc_name, int frequency, int rank);//parameterized constructor

	void Inc_frequency(int inc);//increments frequency by a factor of one
	void Inc_rank(int inc);//increments rank by a factor of one

	string get_doc_name();//returns name of the document
	int get_frequency();//returns frequency
	int get_rank();//returns rank

	friend class Search_Engine;
};


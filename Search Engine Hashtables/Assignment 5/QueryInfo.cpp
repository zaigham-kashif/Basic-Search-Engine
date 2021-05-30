#include "QueryInfo.h"
#include "QueryInfo.h"

QueryInfo::QueryInfo()
{
	pr_doc_name = '\0';
	pr_frequency = 0;
	pr_rank = 0;
}

QueryInfo::QueryInfo(string doc_name, int frequency, int rank)
{
	pr_doc_name = doc_name;
	pr_frequency = frequency;
	pr_rank = rank;
}

void QueryInfo::Inc_frequency(int inc)
{
	pr_frequency = pr_frequency + inc;
}

void QueryInfo::Inc_rank(int inc)
{
	pr_rank = pr_rank + inc;
}

string QueryInfo::get_doc_name()
{
	return pr_doc_name;
}

int QueryInfo::get_frequency()
{
	return pr_frequency;
}

int QueryInfo::get_rank()
{
	return pr_rank;
}

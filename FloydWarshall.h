#pragma once
#include <iostream>
#include "List.h"
using std::string;

List<string*> ConvertInfo(List<string>& info);
List<string> GetCities(List<std::string*>& info);

class Graph
{
private:
	List <string> Cities; //list of unique cities
	int** matrix;
	size_t size;
	void make_matrix(List<string*> &info, List<string> Cities, int**& matrix);
	size_t max_num_len(); //helps to print "beautiful" matrix
	void find_minimal_path();
public:
	void print_matrix(); //prints the matrix. Amazing, right? ^^
	Graph(List<string*>& info, List<string>& cities);
	~Graph();
	string minimal_way(const string &city1, const string &city2);
};

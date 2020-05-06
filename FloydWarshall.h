#pragma once
#include <iostream>
#include "List.h"
using std::string;

List<string*> ConvertInfo(List<string>& info); //convets info from file
List<string> GetCities(List<std::string*>& info); //stores unique cities

class FloydWarshall
{
private:
	List <string> Cities; //list of unique cities
	int** matrix; // two-dimensional matrix
	size_t size;
	void make_matrix(List<string*> &info, List<string> Cities, int**& matrix);
	size_t max_num_len(); //helps to print "beautiful" matrix
public:
	void print_matrix(); //prints the matrix. Amazing, right? ^^
	FloydWarshall(List<string*>& info, List<string>& cities);
	~FloydWarshall();
	string minimal_way(const string &city1, const string &city2); //finds a minimal way between elements of rhe graph
};

#include <iostream>
#include <sstream>
#include <fstream>
#include "List.h"
#include "FloydWarshall.h"

using namespace std;


void main()
{
	ifstream file("info.txt");
	List<string> lines;
	if (file.is_open())  //if the file was opened,read
	{
		while (file) {
			string line;
			getline(file, line);
			lines.push_back(line);
			
		}
		lines.pop_back();
	}
	else throw out_of_range("File can't be opened!");
	file.close();
	List<string*> FormatedInfo = ConvertInfo(lines);
	List<string> Cities = GetCities(FormatedInfo);
	
	cout << "List of all cities: "<<endl;
	Cities.print_to_console();
	
	cout << endl;
	FloydWarshall graph(FormatedInfo, Cities);
	cout << "Initial matrix of all flights with tickets' cost: " << endl;
	graph.print_matrix();
	cout << endl;
	string FirstCity, SecondCity;
	cout << "Enter the departure city: " << endl;
	cin >> FirstCity;
	cout << "Enter the arrival city: " << endl;
	cin >> SecondCity;
	string min_path = graph.minimal_way(FirstCity, SecondCity);
	cout << endl << "Matrix of cheapest flights: " << endl;
	graph.print_matrix();
	cout << endl;
	cout << min_path;
	cout << endl<<endl;
	for (size_t i = 0; i < FormatedInfo.get_size(); ++i)
	{
		delete[] FormatedInfo.at(i);
	}
	
}

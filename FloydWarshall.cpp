#include "FloydWarshall.h"
#include <iostream>
#include <string>  
#include <iomanip>
using std::string;

#define INPUT_WORDS_AMOUNT 4
#define DEPARTURE_CITY 0
#define	ARRIVAL_CITY 1
#define DEPARTURE_PRICE 2
#define ARRIVAL_PRICE 3
#define INF 99999
List<string*> ConvertInfo(List<string>& info)
{
	List<string*> FormatedInfo;
	if (info.get_size() == 0)
		throw std::length_error("Input was empty!");
	
	
	for (size_t i = 0; i < info.get_size(); i++)
	{
		const auto line = new std::string[INPUT_WORDS_AMOUNT];
		size_t word_number = 0;

		for (auto symbol : info.at(i))
		{
			if (symbol != ';') //записываем посимвольно слова в элемент массива пока не соберем все слово
				line[word_number] += symbol;
			else
				word_number++; //если встречаем ; переходим к следущему элементу массива - новому слову
		}
		
		if (INPUT_WORDS_AMOUNT < word_number)
			throw std::invalid_argument("Wrong format of the input data");

		if (line[DEPARTURE_PRICE] == "N/A" && line[ARRIVAL_PRICE] == "N/A")
			throw std::logic_error("Flight from one city to another is impossible in both directions!");

		if (line[DEPARTURE_PRICE] == "N/A")
			line[DEPARTURE_PRICE] = "0";

		if (line[ARRIVAL_PRICE] == "N/A")
			line[ARRIVAL_PRICE] = "0";

		FormatedInfo.push_back(line);
	}
	return FormatedInfo;
}

List<string> GetCities(List<std::string*>& info)
{
	List<string> Cities;
	for (size_t i = 0; i < info.get_size(); i++)
	{
		auto line = info.at(i);
		if (!Cities.contains(line[DEPARTURE_CITY]))
			Cities.push_back(line[DEPARTURE_CITY]);

		if (!Cities.contains(line[ARRIVAL_CITY]))
			Cities.push_back(line[ARRIVAL_CITY]);
	}
	return Cities;
}

Graph::Graph(List<string*>& info, List<string> &cities)
{
	this->size = cities.get_size();
	this->Cities = cities;
	this->matrix = new int* [size]; //размер матрицы равен количесву городов
	for (size_t i = 0; i < size; i++)  //create a two-dimensional matrix
		matrix[i] = new int [size];
	
	make_matrix( info,  Cities, matrix);
}

Graph::~Graph()
{
	for (size_t count = 0; count < Cities.get_size(); count++)
		delete[] matrix[count];
}
void Graph::make_matrix(List<string*>& info, List<string> Cities, int** &matrix)
{
	int city1, city2;
	
	//заполнение массива
	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
		{
			if (i==j)
				matrix[i][j] = 0;
			else matrix[i][j] = INF;
		}
	for (size_t i =0; i < info.get_size(); i++)
	{
		auto line = info.at(i);
		city1 = Cities.find(line[DEPARTURE_CITY]);
		city2 = Cities.find(line[ARRIVAL_CITY]);
		if (city1 == -1 || city2 == -1)
		{
			std::cout << "\nSmth went wrong..."; //заменить на исключение
			return;
		}
		matrix[city1][city2] = stoi(line[DEPARTURE_PRICE]);
		matrix[city2][city1] = stoi(line[ARRIVAL_PRICE]);
		
	}
	
}

size_t Graph::max_num_len()
{
	size_t max_len = 0u;
	size_t len;
	for (size_t i = 0; i < size; ++i)
	{
		for (size_t j = 0; j < size; ++j)
		{
			if (matrix[i][j] == INF)
				len = 3;
			else
				len = to_string(matrix[i][j]).size();
			max_len = len > max_len ? len : max_len;
		}
	}
	return max_len;
}
void Graph::print_matrix()
{
	if (size == 0)
		throw std::logic_error("The matrix is empty!");
	cout << endl;
	size_t max_len = max_num_len();
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == j)
				cout << setw(max_len + 2u) << 0;
			else if (matrix[i][j] == 0 || matrix[i][j] == INF)
				cout << setw(max_len + 2u) << "N/A";
			else 
				cout << setw(max_len + 2u) << matrix[i][j];
			if (j == size- 1)
				std::cout << "\n"; 
			
		}	
	}
}

string Graph::minimal_way(const string &first_city, const string &second_city)
{
	if (first_city == second_city)
		return "Departure and arrival cities must be different!";

	int first_city_index = Cities.find(first_city);
	int second_city_index = Cities.find(second_city);

	if (first_city_index == -1 || second_city_index == -1)
		return "Irrelevant departure or arrival city name!";

	//calculate the matrix of shortest weights
	for (int k = 1; k < size; k++) 
		for (int i = 0; i < size; i++) 
			for (int j = 0; j < size; j++) 
				if (((matrix[i][k] + matrix[k][j]) < matrix[i][j]) && (i != j))
					matrix[i][j] = matrix[i][k] + matrix[k][j];

	if (matrix[first_city_index][second_city_index] == 0)
	{
		string answer;
		answer += "There is no route between " + first_city + " and " + second_city + "!";
		return answer;
	}
	string answer = "Minimal price: ";
	answer += to_string(matrix[first_city_index][second_city_index]);
	return answer;

}



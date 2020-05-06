#include "pch.h"
#include "CppUnitTest.h"
#include <exception>
#include <sstream>
#include <fstream>
#include "..//FloydWarshall//FloydWarshall.h"
#include "..//FloydWarshall//FloydWarshall.cpp"
#include "..//FloydWarshall//List.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FloydWarshallTests
{
	TEST_CLASS(FloydWarshallTests)
	{
	public:
		
		TEST_METHOD(EmptyList_exeption_Test)
		{
			
			try
			{
				List<string> lines;
				List<string*> FormatedInfo = ConvertInfo(lines);
			}
			catch (std::length_error error)
			{
				Assert::AreEqual(error.what(), "Input was empty!");
			}
		}

		TEST_METHOD(AnswerTest_known_cities)
		{
			ifstream file("info.txt");
			List<string> lines;
			if (file.is_open())  
			{
				while (file) {
					string line;
					getline(file, line);
					lines.push_back(line);

				}
				lines.pop_back();
			}
			file.close();
			List<string*> FormatedInfo = ConvertInfo(lines);
			List<string> Cities = GetCities(FormatedInfo);
			Graph graph(FormatedInfo, Cities);
			string FirstCity= "Moskow", SecondCity= "Khabarovsk";
			string min_path = graph.minimal_way(FirstCity, SecondCity);
			string expected = "Minimal price: 40";
			Assert::AreEqual(min_path, expected);
		}

		TEST_METHOD(AnswerTest_unknown_cities)
		{
			ifstream file("info.txt");
			List<string> lines;
			if (file.is_open())
			{
				while (file) {
					string line;
					getline(file, line);
					lines.push_back(line);

				}
				lines.pop_back();
			}
			file.close();
			List<string*> FormatedInfo = ConvertInfo(lines);
			List<string> Cities = GetCities(FormatedInfo);
			Graph graph(FormatedInfo, Cities);
			string FirstCity = "jeygfreytgfef", SecondCity = "Hudheurgdhw";
			string min_path = graph.minimal_way(FirstCity, SecondCity);
			string expected = "Irrelevant departure or arrival city name!";
			Assert::AreEqual(min_path, expected);
		}
	};
}

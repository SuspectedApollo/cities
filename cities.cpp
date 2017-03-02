#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class City {
	string name;
	string state;
	string country;
	double longitude;
	double latitude;
	int population;

public:
	City() {
		name = "";
		state = "";
		country = "";
		longitude = 0;
		latitude = 0;
		population = 0;
	}
	City(string cName, string cState, string cCountry, double cLongitude, double cLatitude, int cPopulation) {
		name = cName;
		state = cState;
		country = cCountry;
		longitude = cLongitude;
		latitude = cLatitude;
		population = cPopulation;
	}

	string getName() {
		return name;
	}

	string toString() {
		return name + '\n' + state + '\n' + country + '\n' + std::to_string(latitude) + '\n' + std::to_string(longitude) + '\n' + std::to_string(population) + '\n';
	}

	int print() {
		cout << name << '\n' << state << '\n' << country << "\nLatitude:" << latitude << "\nLongitude:" << longitude << "\nPopulation:" << population << endl;

		return EXIT_SUCCESS;
	}

};

int main(int argC, char *argV) {
	std::ifstream stream("cities.dat", std::ifstream::in);
	if (!stream.is_open()) {
		cout << "File failed to open" << endl;
		return EXIT_FAILURE;
	}
	int count = 0;
	string city, state, country;
	double lat, longi;
	int pop;
	City cities[1000];
	while (!stream.eof()) {
		switch(count % 7){
		case 0:stream >> city;
		case 1:stream >> state;
		case 2:stream >> country;
		case 3:stream >> lat;
		case 4:stream >> longi;
		case 5:stream >> pop;
		case 6:cities[count / 6] = City(city, state, country, lat, longi, pop);
		}
		count = count + 1;
	}
	bool exit = false;
	string command = "";
	int current = 0;
	count = count / 6;
	while (!exit) {
		cout << "Current city\n";
		cities[current].print();
		cout << "Enter a command. Enter \"HELP\" for a list of commands" << endl;
		cin >> command;
		if (command.compare("HELP") == 0 || command.compare("Help") == 0) {
			cout << "EXIT -- Exits the program\nADD – Adds a city to the list of cities\nLIST -- List all the cities\nNEXT – move to the next city in the list and display it\nPREVIOUS – move to the previous city in the list and display it\nDELETE – delete the current city from the list and print the new current city\nFIRST – move to the first city in the list and display it.\nLAST – move to the last city in the list and display it.\nSEARCH -- search for a city by name. If any part of the search string given appears in the\ncities name the city information should be displayed.The search leaves the current position in\nthe list unchanged." << endl;
		}
		else if (command.compare("EXIT") == 0 || command.compare("Exit") == 0) {
			exit = true;
			stream.close();
			ofstream oStream("cities.dat");
			for (int i = 0; i <= count; i = i + 1) {
				oStream << cities[i].toString();
			}

		}
		else if (command.compare("ADD") == 0 || command.compare("Add") == 0) {
			cout << "Enter the name of the city:";
			cin >> city;
			cout << "Enter the state of the city:";
			cin >> state;
			cout << "Enter the country of the city:";
			cin >> country;
			cout << "Enter the latitude of the city";
			cin >> lat;
			cout << "Enter the longitude of the city";
			cin >> longi;
			cout << "Enter the population of the city";
			cin >> pop;
			count = count + 1;
			cities[count] = City(city, state, country, lat, longi, pop);
		}
		else if (command.compare("NEXT") == 0 || command.compare("Next") == 0) {
			if (cities[current + 1].getName() != "") {
				current = current + 1;
			}
		}
		else if (command.compare("Previous") == 0 || command.compare("PREVIOUS") == 0) {
			if (current > 0) {
				current = current - 1;
			}
		}
		else if (command.compare("DELETE") == 0 || command.compare("Delete") == 0) {
			for (int i = current; i < 999; i++) {
				cities[i] = cities[i + 1];
			}
		}
		else if (command.compare("FIRST") == 0 || command.compare("First") == 0) {
			current = 0;
		}
		else if (command.compare("LAST") == 0 || command.compare("Last") == 0) {
			current = count;
		}
		else if (command.compare("LIST") == 0 || command.compare("List") == 0) {
			for (int i = 0; i <= count; i = i + 1) {
					cout << '\n';
					cities[i].print();
			}
		}
		else if (command.compare("SEARCH") == 0 || command.compare("Search") == 0) {
			string search;
			cout << "Enter a name to search for:";
			cin >> search;
			for (int i = 0; i <= count; i = i + 1) {
				if (cities[i].getName().find(search) != string::npos) {
					cout << '\n';
					cities[i].print();
				}
			}
		}
	}
	return EXIT_SUCCESS;
}



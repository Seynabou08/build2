//#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Map.h"
#include "City.h"

using namespace std;


//constructor method
Map::Map(int cityNum) {
	cities = vector<City*>();
	for (int i = 0; i < cityNum; i++) {
		City* city = new City(i);
		cities.push_back(city);
	}
	bool blueCure = false;
	bool yellowCure = false;
	bool whiteCure = false;
	bool redCure = false;
	int researchStationNum=6;
}

Map::~Map() {
	cities.clear();
	delete[] adjacencyMatrix;
}

City Map::getCity(int i) {
	return *cities[i];
}

City* Map::accessCity(int i) {
	City* city = cities[i];
	return city;
}


void Map::addEdge(int i, int j) {
	if (i >= 0 && i < 48 && j > 0 && j < 48) {
		adjacencyMatrix[i][j] = true;
		adjacencyMatrix[j][i] = true;
	}
}

vector<City*> Map::getConnectedCities(int i) { //returns vector of connected cities
	vector<City*> connectedCities;
	for (int j = 0; j < 48; j++) {
		if (adjacencyMatrix[i][j]) {
			connectedCities.push_back(accessCity(j));
		}
	}
	return connectedCities;
}


//Displaying map as an adjacency list
void  Map::showMap() {
	for (int i = 0; i < cities.size(); i++) {
		City* city = cities[i];
		string name = city->getName();
		cout << "\n The cities linked to city " << name << " are : \n ";
		vector<City*> connectedCities = getConnectedCities(i);
		for (int i=0; i<connectedCities.size(); i++)
		{
			cout << connectedCities[i]->index << ": " << connectedCities[i]->getName() << endl;
		}
		cout << endl;
	}
}

void Map::showCity(int i) {
	City* city = cities[i];
	string name = city->getName();
	cout << "\n The cities linked to city " << name << " are : \n ";
	vector<City*> connectedCities = getConnectedCities(i);
	for (int i=0; i<connectedCities.size(); i++)
	{
		cout << connectedCities[i]->index << ": " << connectedCities[i]->getName() << endl;
	}
	cout << endl;

}

//Initialising the official Pandemic map. Each city is assigned an integer and it helps represent the position of the pawn
void Map::startGame() {
	string cityName[] = { "San Francisco", "Los Angeles", "Chicago", "Mexico City", "Lima","Santiago", "Toronto", "Atlanta",
		"Miami", "Bogota", "New York", "Washington", "Sao Paulo", "Buenos Aires", "London", "Paris", "Madrid",
		"Lagos", "Kinshasa", "Essen", "Milan", "Algiers", "Khartoum", "Johannesburg", "St Petersburg", "Istanbul",
		"Cairo", "Moscow", "Baghdad", "Riyadh", "Tehran", "Karachi", "Delhi", "Mumbai", "Kolkata", "Chennai", "beijing",
		"Seoul", "Shanghai", "Hong Kong", "Bangkok", "Tokyo", "Osaka", "Taipei", "Manila", "Ho Chi Minh City",
		"Jakarta", "Sydney" };

	

	//initialize adjacency matrix
	adjacencyMatrix = new bool*[48];
	for (int i = 0; i < 48; i++) {
		adjacencyMatrix[i] = new bool[48];
		for (int j = 0; j < 48; j++)
			adjacencyMatrix[i][j] = false;
	}

	for (int j = 0; j < 48; j++) {
		cities[j]->name = cityName[j];
	}


	int blue[] = { 1, 3, 7, 8, 11, 12, 15, 16, 17, 20, 21, 25 };
	 
	//assign colour blue
	for (int j = 0; j < 12; j++) {
		cities[blue[j]]->colour = 'b';
	}

	int yellow[] = { 2, 4, 5, 6, 9, 10, 13, 14, 18, 19, 23, 24 };
	//assign colour yellow
	for (int j = 0; j < 12; j++) {
		cities[yellow[j]]->colour = 'y';
	}
	
	int white[] = { 22, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36 };
	//assign colour white
	for (int j = 0; j < 12; j++) {
		cities[white[j]]->colour = 'w';
	}
	
	int red[] = { 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48 };
	//assign colour red
	for (int j = 0; j < 12; j++) {
		cities[red[j]]->colour = 'r';
	}

	this->addEdge(0, 1);
	this->addEdge(0, 2);
	this->addEdge(1, 4);
	this->addEdge(2, 3);
	this->addEdge(2, 6);
	this->addEdge(2, 7);
	this->addEdge(3, 8);
	this->addEdge(3, 9);
	this->addEdge(3, 4);
	this->addEdge(4, 9);
	this->addEdge(4, 5);
	this->addEdge(6, 10);
	this->addEdge(6, 11);
	this->addEdge(7, 11);
	this->addEdge(7, 8);
	this->addEdge(8, 11);
	this->addEdge(8, 9);
	this->addEdge(9, 12);
	this->addEdge(9, 13);
	this->addEdge(10, 14);
	this->addEdge(10, 16);
	this->addEdge(10, 11);
	this->addEdge(12, 16);
	this->addEdge(12, 17);
	this->addEdge(12, 13);
	this->addEdge(14, 19);
	this->addEdge(14, 15);
	this->addEdge(15, 19);
	this->addEdge(15, 20);
	this->addEdge(15, 21);
	this->addEdge(15, 16);
	this->addEdge(16, 21);
	this->addEdge(17, 22);
	this->addEdge(17, 18);
	this->addEdge(18, 22);
	this->addEdge(18, 23);
	this->addEdge(19, 24);
	this->addEdge(19, 20);
	this->addEdge(20, 25);
	this->addEdge(21, 25);
	this->addEdge(21, 26);
	this->addEdge(22, 26);
	this->addEdge(22, 23);
	this->addEdge(24, 25);
	this->addEdge(24, 27);
	this->addEdge(25, 27);
	this->addEdge(25, 28);
	this->addEdge(26, 28);
	this->addEdge(26, 29);
	this->addEdge(27, 30);
	this->addEdge(28, 30);
	this->addEdge(28, 31);
	this->addEdge(28, 29);
	this->addEdge(29, 31);
	this->addEdge(30, 32);
	this->addEdge(30, 31);
	this->addEdge(31, 32);
	this->addEdge(31, 33);
	this->addEdge(32, 34);
	this->addEdge(32, 33);
	this->addEdge(33, 35);
	this->addEdge(34, 39);
	this->addEdge(34, 40);
	this->addEdge(34, 35);
	this->addEdge(35, 46);
	this->addEdge(35, 40);
	this->addEdge(36, 37);
	this->addEdge(36, 38);
	this->addEdge(37, 41);
	this->addEdge(37, 38);
	this->addEdge(38, 41);
	this->addEdge(38, 43);
	this->addEdge(38, 39);
	this->addEdge(39, 43);
	this->addEdge(39, 44);
	this->addEdge(39, 45);
	this->addEdge(39, 40);
	this->addEdge(40, 45);
	this->addEdge(40, 46);
	this->addEdge(41, 42);
	this->addEdge(41, 0);
	this->addEdge(42, 43);
	this->addEdge(43, 44);
	this->addEdge(44, 0);
	this->addEdge(44, 45);
	this->addEdge(44, 47);
	this->addEdge(45, 46);
	this->addEdge(46, 47);
	this->addEdge(47, 1);

	this->showMap();
}

//Saving the content of the map in a file
void Map::saveMap() {
	cout << "TRYING TO SAVING MAP" << endl;
	ofstream myfile;
	myfile.open("save.txt");
	
	if (myfile.is_open()) {
		for (int i = 0; i < 48; i++) {
			myfile << cities[i]->index << ' ' << cities[i]->name << ' ' <<
				cities[i]->infected << ' ' << cities[i]->infectionLevel << ' ' << cities[i]->researchCenter << '\n';
		}
		cout << "SAVE SUCCESSFUL" << endl;
	}
	else {
		cout << "COULD NOT CREATE SAVE FILE" << endl;
	}

	myfile.close();

}

//loading one of the saved files
void Map::loadMap(ifstream myfile) {
	string line;
	string lineToBeInputed;


	ifstream myFile;
	myFile.open("text.txt");


	if (myfile.is_open())
	{
		int i = 0;
		while (getline(myfile, line))
		{
			//when it reads the first element it reads and sets the index of the city to the value read. We convert that string to an integer using stoi
			getline(myfile, lineToBeInputed, ' '); 
			cities[i]->index =stoi(lineToBeInputed);


			//when it reads the second element it reads and sets the name of the city to the value read.
			getline(myfile, lineToBeInputed, ' ');
			cities[i]->name = lineToBeInputed;


			//when it reads the 3rd element it changes the boolean of the city to the value read.
			getline(myfile, lineToBeInputed, ' ');
			if (lineToBeInputed == "false") cities[i]->infected = false;
			else cities[i]->infected = true;

			//when it reads the 4th element it sets the infection level of the city to the values read. We convert that string to an integer using stoi
			getline(myfile, lineToBeInputed, ' ');
			
			cities[i]->infectionLevel = stoi(lineToBeInputed);


			//when it reads the 5th element it changes the boolean of the city to the values read.
			getline(myfile, lineToBeInputed, ' ');
			if (lineToBeInputed == "false") cities[i]->researchCenter = false;
			else cities[i]->researchCenter = true;; //need to convert string to city
			i++;
		}
		myfile.close();
	}

	myfile.close();

}


//#include "Player.h"
#include "City.h" 
#include <vector>

using namespace std;

#ifndef MAP_H
#define MAP_H
class Map
{
private:
	int size;               //The number of cities in the map
	bool** adjacencyMatrix; //represents the edges connecting cities
public:
	vector<City*> cities;   //need to be public for Infectiondeck()

	// These are initialised as false but then set to true with a cure for a disease is found
	bool blueCure;
	bool yellowCure;
	bool whiteCure;
	bool redCure;
	int researchStationNum;

	//Constructors
	Map(int i);
	 //Destructor
	~Map();

	//Accessor and Mutator methods
	City getCity(int i);

	City* accessCity(int i);

	vector<City*> getConnectedCities(int i); //gives index of neighbours

	void addEdge(int i, int j);   //Connect 2 cities

	//Prints out the map
	void showMap();

	//Prints out the city and its neigbours
	void showCity(int i);

	//Sets up the city names, links them appropriatly and adds color based on regions
	void startGame();

	//Saving and loading
	void saveMap();
	void loadMap(ifstream myfile);
};
#endif
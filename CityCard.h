#include "City.h"
#include "Card.h"
#include <string>
#include <vector>

using namespace std;

#ifndef CITYCARD_H
#define CITYCARD_H

class CityCard: public Card{
public:
	//Constructors
	CityCard();
	CityCard(City* city);
	//Destructor
	~CityCard();
	
	//Accessor Methods
	int getID();
	string getCityName();

private:
	int id;
	City* city; //We associate each card to a city. They share a name and index 

};

#endif
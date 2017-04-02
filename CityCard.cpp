#include "CityCard.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;


CityCard::~CityCard()
{
}


CityCard::CityCard() :Card(){
	this->id = 0;
}


CityCard::CityCard(City* city):Card(city->getName(), city->getColor(), city->accessCity()){
	this->id = city->index;
	this->city = city;
}

int CityCard::getID() {
	return this->id;
}

string CityCard::getCityName() {
	return this->city->name;
}


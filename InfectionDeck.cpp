#include "InfectionDeck.h"
#include <algorithm> //for shuffling
#include <iostream>
using namespace std;

int InfectionDeck::infectionCubes; //need another declaration for static to work
int InfectionDeck::infectionMarker;
int InfectionDeck::numberOutbreaks;
int InfectionDeck::markerValues[7] = { 2, 2, 2, 3, 3, 4, 4 };


InfectionDeck::InfectionDeck(vector<City*> cities)
{
	for each(City* city in cities) {
		InfectionCard card = InfectionCard(city);
		deck.push_back(card);
	}
}

InfectionDeck::~InfectionDeck()
{
	deck.clear();
	discardPile.clear();
}

void InfectionDeck::init(int numCities) {
	InfectionDeck::infectionCubes = numCities;
	InfectionDeck::infectionMarker = 0; //put marker on starting position
	InfectionDeck::numberOutbreaks = 0;
}

InfectionCard* InfectionDeck::draw()
{
	if (this->deck.empty()) {
		cout << "GAME OVER: You have ran out of infection card to draw from" << endl;
		system("pause"); //windows only
		exit(1);
	}
	InfectionCard card = this->deck.front(); //grab first card
	this->discardPile.push_back(card); //add drawn card to discard pile
	//delete[] card;
	this->deck.front() = this->deck.back(); //'swap' first with last
	this->deck.pop_back(); //delete last

	return &this->discardPile.back();
}

void InfectionDeck::initialInfection() //infect 3 cities with 3, 3 cities with 2, 3 cities with 1
{
	for (int i = 0; i < 3; i++) {
		InfectionCard* card = this->draw();
		cout << card->getCityName() << " has been set to infection level 3" << endl;
		card->setLevel(3);
	}
	for (int i = 0; i < 3; i++) {
		InfectionCard* card = this->draw();
		cout << card->getCityName() << " has been set to infection level 2" << endl;
		card->setLevel(2);
	}
	for (int i = 0; i < 3; i++) {
		InfectionCard* card = this->draw();
		cout << card->getCityName() << " has been set to infection level 1" << endl;
		card->setLevel(1);
	}
}

void InfectionDeck::playInfection() //play 1-4 infection cards
{
	for (int i = 0; i < markerValues[infectionMarker]; i++) {
		this->draw()->playCard();
	}
}

void InfectionDeck::intensify()
{
	cout << "Resetting discard pile" << endl;
	random_shuffle(discardPile.begin(), discardPile.end()); //shuffle discard
	this->deck.insert(deck.begin(), discardPile.begin(), discardPile.end()); //put at top of deck
	this->discardPile.clear(); //clear discard pile
}

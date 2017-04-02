#pragma once
#include "InfectionCard.h"

#include <vector>
using namespace std;

class InfectionDeck
{
public:
	vector<InfectionCard> deck;
	vector<InfectionCard> discardPile;
	static int infectionCubes; // 1 infection cube for each city, if no cubes left then GAME OVER
	static int infectionMarker; //determines how many infection cards to draw each turn
	static int markerValues[7];
	static int numberOutbreaks; //8 outbreaks = GAME OVER

	//Constructor
	InfectionDeck(vector<City*>);
	//Destructor
	~InfectionDeck();

	void init(int numCities); //call at beginning of game

	void initialInfection(); // done once at beginning of game
	void playInfection(); // play an infection turn (play number of cards based on infectionMarker)

	void intensify(); //shuffle cards from discard pile and place on top of deck (when epidemic happens)

private:
	InfectionCard* draw(); //draws 1 card and discards it
};


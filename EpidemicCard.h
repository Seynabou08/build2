#pragma once
#include "Card.h"
#include <string>
#include <vector>
#include "InfectionDeck.h"
using namespace std;

class EpidemicCard : public Card {
public:

	//Constructors
	EpidemicCard();
	EpidemicCard(string n, char c, int a);
	//Destructor
	~EpidemicCard();

	void playCard(InfectionDeck& deck); //pass the infection deck
};


#include "EpidemicCard.h"


EpidemicCard::EpidemicCard() :Card(){
}

EpidemicCard::EpidemicCard(string n, char c, int a) : Card(n,c,a){
}

EpidemicCard::~EpidemicCard()
{
}

void EpidemicCard::playCard(InfectionDeck& deck)
{
	//Move the infection rate marker forward 1 space on the Infection Rate Track.
	InfectionDeck::infectionMarker++;

	//draw the bottom card from the infection deck and make outbreak
	deck.deck.back().makeOutbreak();
	//move card to discard pile
	deck.discardPile.push_back(deck.deck.back());
	deck.deck.pop_back();

	deck.intensify();
}
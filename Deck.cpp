#include "Deck.h"
#include <algorithm> 

using namespace std;


Deck::Deck()
{
}

Deck::Deck(int i)
{
}

void Deck::addCard(Card* card)
{
	deck.push_back(card);
}

void Deck::shuffleCards()
{
	std::random_shuffle(deck.begin(), deck.end());
}

Card * Deck::drawCard()
{
	Card* card = deck.front(); //grab first card
	discard.push_back(card); //add drawn card to discard pile
									   //delete[] card;
	deck.front() = this->deck.back(); //'swap' first with last
	deck.pop_back(); //delete last

	return discard.back();
}



#pragma once
#include <vector>
#include "Card.h"

using namespace std;

class Deck
{
public:
	Deck();
	Deck(int i);
	void addCard(Card* card);
	void shuffleCards();
	Card* drawCard();

private:
	int size;
	vector<Card*> discard;
	vector<Card*> deck;
};
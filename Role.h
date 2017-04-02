#ifndef ROLE_H
#define ROLE_H

//#include <string>
#include <vector>
#include "Card.h"
#include "Map.h"
using namespace std;

class Role : public Card
{
    public:
		vector<Role*> roleCards;

		//Constructors and Destructor
        Role(string n, int i);
        Role();
        ~Role();

        void printRole();

		//Accessor and Mutator methods
        string getName();
        int getId();

        /* void passiveAbility(char disease, int city);
        void activeAbility(vector<Card> &deck, int city);
		*/

		//The seven different roles 
       /* void contingencyPlannerAct(vector<Card> &deck);
        void dispatcherAct(vector<Card> &hand, int city, Map m);
        void medicAb(char disease);
        void operationsExpertAb(char disease);
        void quarantineExpertAb();
        void researcherAb(Card c);
        void scientistAb(char disease);
		*/

    private:
        Card cCard; //contigency card
        
};
#endif

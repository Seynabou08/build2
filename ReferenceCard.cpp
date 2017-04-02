#include "ReferenceCard.h"

ReferenceCard::ReferenceCard()
{
  this->description="This card is used as a reminder of a player actions";
}

ReferenceCard::~ReferenceCard(){}

void ReferenceCard::displayCard()
{
    cout<<"////ACTIONS////"<<endl;
    cout<<"Build Research Station"<<endl;
    cout<<"Treat Disease"<<endl;
    cout<<"Share Knowledge"<<endl;
    cout<<"Discover a Cure"<<endl;
    cout<<"////MOVEMENT ACTIONS////"<<endl;
    cout<<"Drive/Ferry"<<endl;
    cout<<"Direct Flight"<<endl;
    cout<<"Charter Flight"<<endl;
    cout<<"Shuttle Flight"<<endl;
}
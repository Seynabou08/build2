#include <string>
#include <iostream>
using namespace std;

#ifndef REFERENCECARD_H
#define REFERENCECARD_H

class ReferenceCard{
    public:

		//Constructors
        ReferenceCard();
        ~ReferenceCard();
        void displayCard();

    private:
		//card's description
        string description;

};
#endif
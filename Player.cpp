#include "Player.h"

Player::Player(char p, vector<Role> &roleDeck, vector<Card*> &cardDeck, int pCount, int i)
{
	this->location = 7; //Atlanta is location 7
	this->cards = vector<Card*>(20);
	switch (pCount) //draws cards based on player count
	{
	case 1:
		drawCards(cardDeck, 4);
		break;
	case 2:
		drawCards(cardDeck, 4);
		break;
	case 3:
		drawCards(cardDeck, 3);
		break;
	case 4:
		drawCards(cardDeck, 2);
		break;
	}
	this->role = roleDeck[roleDeck.size() - 1];
	roleDeck.pop_back();

	//Choosing a color
	switch (p)
	{
	case 'b':
		this->pawn = BLUE;
		break;

	case 'g':
		this->pawn = GREEN;
		break;

	case 'r':
		this->pawn = RED;
		break;

	case 'y':
		this->pawn = YELLOW;
		break;

	case 'x':
		this->pawn = BLACK;
		break;

	}
	this->rc = ReferenceCard();
	this->id = i;
}

Player::Player()
{
	this->location = 7;
	this->cards = vector<Card*>();
	this->role = Role();
	this->pawn = BLACK;
	this->rc = ReferenceCard();
	this->id = 0;
}
Player::~Player()
{
	this->cards.clear();
}

vector<Card*> Player::getHand()
{
	return this->cards;
}

void Player::setHand(vector<Card*> c)
{
	this->cards = c;
}


void Player::setRole(Role rCard)
{
	this->role = rCard;
}

string Player::getRole()
{
	return this->role.getName();
}

char Player::getPawn()
{
	switch (this->pawn)
	{
	case BLUE:
		return 'b';

	case RED:
		return 'r';

	case YELLOW:
		return 'y';

	case GREEN:
		return 'g';

	case BLACK:
		return 'x';

	default:
		return 'x';
	}
}

int Player::getId()
{
	return this->id;
}

int Player::getLocation()
{
	return this->location;
}


///////////PRINT FUNCTIONS/////////////////////

void Player::printPossessions()
{
	cout << "Player id: " << this->id << endl;
	cout << "Player location: " << this->location << endl;
	switch (this->pawn)
	{
	case BLUE:
		cout << "Player pawn: blue" << endl;
		break;

	case RED:
		cout << "Player pawn: red" << endl;
		break;

	case YELLOW:
		cout << "Player pawn: yellow" << endl;
		break;

	case GREEN:
		cout << "Player pawn: green" << endl;
		break;

	default:
		cout << "Player pawn: black" << endl;;
	}

	cout << "Player cards: " << endl;
	this->displayHand();
	cout << "Player Role: " << this->role.getName() << endl;
	cout << "Player reference card: " << endl;
	this->printReference();
}

void Player::displayHand()
{
	for (int i = 0; i<cards.size(); i++)
	{
		cout << "Card at index " << i << ": " << cards[i]->getName() << endl;
	}
}

void Player::printReference()
{
	this->rc.displayCard();
}

void Player::displayActionsLeft()
{
	cout << "Actions remaining: " << this->actionsLeft << endl;
}
//////////AUTOMATIC ACTIONS//////////////////
void Player::startTurn()
{
	actionsLeft = 4;
}

void Player::subtractAction()
{
	actionsLeft--;
}

void Player::concludeTurn(vector<Card*> deck)
{
	this->drawCards(deck, 2);
}

void Player::drawCards(vector<Card*> deck, int num)
{
	int userCards = this->cards.size(); //number of cards in user hand
	int lastCard = deck.size(); //index of last card
	if (lastCard == 0) //if deck runs out
	{
		//game over
	}

	else //draw
	{
		for (int a = 0; a < num; a++)
		{
			this->cards.push_back(deck.back());
			deck.pop_back();
		}
	}
}


//  returns true if the user still has actions left this turn.

bool Player::checkAction()
{
	if (actionsLeft == 0)
		return false;
	else
		return true;
}

void Player::discard(int a)
{
	//vector<Card*> cards = this->getHand(); //does it make a copy
	//cards[a] = cards.back();
	//cards.pop_back();

	this->cards[a] = this->cards.back();
	this->cards.pop_back();
}

////////PLAYER ACTIONS/////////////////////////////////
void Player::move(int d)
{
	//This method was supposed to make sire the player can only drive to neighbouring cities, we will try to fix the error.
	//the player can drive anywhere but wont be shown any option but the neighbouring cities.

	/*vector<City*> cities= m.getConnectedCities(this->location);
	vector<int> cityIndex;
	bool correctInput=false;
	int choice;
	cout<<"select the index of the city you would like to drive (or fly) to: "<<endl;
	for (int i=0; i<cities.size(); i++) //get possible cities player can drive to
	{
	cout<< cities[i]->index << " : " << cities[i]->getName()<<endl;
	cityIndex.push_back(cities[i]->index);
	}
	cities.clear();

	while(!correctInput) //get player input with verification
	{
	cin>>choice;
	for (int i=0; i<cityIndex.size(); i++)
	{
	if(choice==cityIndex[i])
	correctInput = true;
	}
	if(!correctInput)
	cout<<"sorry, you have entered an invalid index"<<endl;
	}
	this->location = choice;

	this->subtractAction();

	*/
	if (Player::checkAction())
	{
		location = d;
		this->subtractAction();
	}
}

void Player::flight(int a)
{
	int choice;

	choice = a;

	this->location = choice;

	this->subtractAction();
}

void Player::buildStation(Map m)
{
	//uses current player location, builds a station
	if (m.researchStationNum>0)
	{
		int loc = this->location;
		City c;
		City* cp = m.accessCity(loc); // gets a pointer to city where player is
		c = *cp;                      //creates a copy that can be modified
		c.setResearchCenter(true);    // copy modified
		*cp = c;                      //city replaced with copy
		delete[] cp;

		m.researchStationNum--;
		this->subtractAction();
	}
	else
	{
		//no more research stations can be built
	}
}

void Player::treatDisease(Map m)
{
	int loc = this->location;
	City c;
	char cityColor;
	City* cp = m.accessCity(loc);
	c = *cp;
	cityColor = c.getColor();
	if (c.infected == true) //if the city has infection cubes
	{
		if ((cityColor == 'b' && m.blueCure) || (cityColor == 'y' && m.yellowCure) || (cityColor == 'w' && m.whiteCure) || (cityColor == 'r' && m.redCure))
		{   //if cure for city is discovered
			c.setInfectionLevel(0);
			c.setInfection(false);
		}
		else
		{
			c.decrementInfection();
			if (c.getInfection() == 0)
				c.setInfection(false);
		}
		*cp = c;
		this->subtractAction();
	}
	else
	{
		//city has no infection to remove
	}
	delete[] cp;
}

void Player::shareKnowledge(Player tg)
{
	if (this->checkAction())
	{
		char option;
		int index;
		vector<Card*> newHand;
		if (this->location == tg.getLocation())
		{
			cout << "Press 't' to take a card, and 'g' to give one" << endl;
			cin >> option;
			if (option == 't')
			{
				cout << "Player" << tg.getId() << "s hand: " << endl;
				tg.displayHand();
				cout << "Enter the index you want to take the card from" << endl;
				cin >> index;
				(this->cards).push_back(tg.getHand()[index]);   //adds card to hand of this player
				newHand = tg.getHand();                           //creates new hand for tg
				newHand.erase(newHand.begin() + index);         //removes card from new hand
				tg.setHand(newHand);                            //replaces old hand of tg
				this->subtractAction();
			}
			else if (option == 'g')
			{
				cout << "Player" << this->id << " hand: " << endl;
				this->displayHand();
				cout << "Enter the index you want to take the card from" << endl;
				cin >> index;
				newHand = tg.getHand();                             //similar logic
				newHand.push_back((this->getHand())[index]);
				tg.setHand(newHand);
				(this->cards).erase((this->cards).begin() + index);
				this->subtractAction();
			}
			else
			{
				cout << "Invalid Option. Try again." << endl;
			}
			cout << "Player" << this->id << " select the card you want " << endl;
		}

		else
		{
			cout << "sorry, this player is not on this space" << endl;
		}
	}
}

void Player::discoverCure(char diseaseColor)
{
	int count = 0;
	for (int i = 0; i<(this->cards).size(); i++) //counts number of cards with appropriate disease color
	{
		if ((this->cards)[i]->getColor() == diseaseColor)
			count++;
	}
	if (count>4)
	{
		//disease cured
		this->subtractAction();
	}
	else
	{
		cout << "not enough cards to cure that disease" << endl;
	}
}

void Player::activateAbility(vector<Card> &deck)
{
	//activates a player ability based on their role
}

///////////PASSIVE ROLE ABILITY/////////////////
void Player::checkPassiveRole()
{
	//activates a passive ability based on the Players role. 
}

//this will be commented out until  we fix the issue with saving and loading


void Player::savePlayer()
{
	cout << "TRYING TO SAVE MAP" << endl;
	ofstream myfile;
	int num = this->id;
	std::string numId = to_string(num);
	myfile.open("player" + numId + "save.txt");

	if (myfile.is_open()) {
		for (int i = 0; i < 48; i++) {
			myfile << this->id << ' ' << this->location << ' ' << this->role.getName() << ' ' << this->getPawn() << endl;

			for (int i = 0; i<cards.size(); i++)
			{
				myfile << "Card at index " << i << ": " << cards[i]->getName() << endl;
			}

		}
		cout << "SAVE SUCCESSFUL" << endl;
	}
	else {
		cout << "COULD NOT CREATE SAVE FILE" << endl;
	}

	myfile.close();




	/*
	string fullPath;
	stringstream playerId; //set dynamic file name unique to the player
	playerId << this->id;
	fullPath.append("PlayerSave");
	fullPath.append(playerId.str());
	fullPath.append(".txt");

	ofstream myFile(fullPath.c_str(), ios::binary);
	boost::archive::text_oarchive oa(myFile);
	oa << this;

	myFile.close();	*/
}




//loading one of the saved files
void Player::loadPlayer(ifstream myfile) {


	int num = this->id;
	string numId = to_string(num);
	myfile.open("player" + numId + "save.txt");

	string line;
	string lineToBeInputed;


	ifstream myFile;
	myFile.open("save.txt");


	if (myfile.is_open())
	{
		int i = 0;
		while (getline(myfile, line))
		{
			//Getting the id
			getline(myfile, lineToBeInputed, ' ');
			this->id = stoi(lineToBeInputed);

			//Getting the location
			getline(myfile, lineToBeInputed, ' ');
			this->location = stoi(lineToBeInputed);;

			//Getting the role
			getline(myfile, lineToBeInputed, ' ');
			this->role.getName() = lineToBeInputed;

			//Getting the Pawn
			getline(myfile, lineToBeInputed, ' ');
			//char line = lineToBeInputed;

			const char *charac = lineToBeInputed.c_str();
			const char c = *charac;
			switch (c)
			{
			case 'b':
				this->pawn = BLUE;
				break;

			case 'g':
				this->pawn = GREEN;
				break;

			case 'r':
				this->pawn = RED;
				break;

			case 'y':
				this->pawn = YELLOW;
				break;

			case 'x':
				this->pawn = BLACK;
				break;
			}



			//Getting the hand

			myfile.close();
		}

		myfile.close();

	}



	/* void Player::loadPlayer(string fileName)
	{

	Player pl;
	char c;
	ifstream home(fileName);
	boost::archive::text_iarchive ia(home);
	ia >> pl;
	home.close();

	this->id = pl.getId();
	this->cards = pl.getHand();
	this->role = pl.getRole();
	c= pl.getPawn();
	switch(p)
	{
	case 'b':
	this->pawn = BLUE;
	break;

	case 'g':
	this->pawn = GREEN;
	break;

	case 'r':
	this->pawn = RED;
	break;

	case 'y':
	this->pawn = YELLOW;
	break;

	case 'x':
	this->pawn = BLACK;
	break;

	}*/
}
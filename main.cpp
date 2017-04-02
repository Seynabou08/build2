#include "Map.h"
#include "InfectionDeck.h"
#include <iostream>
#include <algorithm>
#include "Player.h"
using namespace std;

int main(int argc, char* argv[])
{
	// Initialiing the map 
	Map newMap = Map(48);
	newMap.startGame();

	// Acessing the save from which we load the game
	ifstream file("save.txt");

	//newMap.loadMap(ifstream("save.txt")); //LOADING DOESNT WORK


	//saving the file in visual studio folder
	newMap.saveMap(); 

	//displaying the map
	newMap.showMap();



	//Place the research station in Atlanta.

	City atlanta = newMap.getCity(7);
	atlanta.setResearchCenter(true);
	

	//Placing the 4 cure markers, side	up near the discovered cure indicators.
	cout << "CURES: " << newMap.blueCure << ", " << newMap.yellowCure << ", " << newMap.whiteCure << ", " << newMap.redCure << endl;



	
	cout << "How many players do you want to play?" << endl;
	int a = 0;
	int playerNum;
	while (a >= 4 || a == 0)
	{
		cin >> a;
	}

	switch (a)
	{
	case 2:
		cout << "you have selected 2" << endl;
		playerNum = 2;
		break;
	case 3:
		cout << "you have selected 3" << endl;
		playerNum = 3;
		break;
	case 4:
		cout << "you have selected 4" << endl;
		playerNum = 4;
		break;
	}	

	vector<Player> players;
	int cardNum;
		
	if (playerNum == 2) {
		cardNum = 4;
		Player player1 = Player();
		Player player2 = Player();
		players.push_back(player1);
		players.push_back(player2);
	}
	else if (playerNum == 3) {
		cardNum = 3;
		Player player1 = Player();
		Player player2 = Player();
		Player player3 = Player();

		players.push_back(player1);
		players.push_back(player2);
		players.push_back(player3);
	}
	else if (playerNum == 4) {
		cardNum = 2;
		Player player1 = Player();
		Player player2 = Player();
		Player player3 = Player();
		Player player4 = Player();
		players.push_back(player1);
		players.push_back(player2);
		players.push_back(player3);
		players.push_back(player4);
	}

	// Setting up the player deck
	vector<Card*> playerDeck;
		
	for (int i = 0; i < newMap.cities.size(); i++) {
		CityCard* ccard = new CityCard(newMap.cities[i]);
		Card* card = new Card();
		card = ccard;
		playerDeck.push_back(card);
	}

	// GENERATING ROLE DECK
	vector<Role*> roleDeck;

	string roleNames[] = { "Contingency Planner","Dispatcher", "Medic",
		"Operation Expert", "Quarantine Specialist", "Researcher", "Scientist" };
	
	Role* roleCard = new Role();
	for (int i = 0; i < 7; i++)
	{
		roleCard->setName(roleNames[i]);
		roleCard->setId(i + 1);
		roleDeck.push_back(roleCard);
	}


	//Shuffling the Player cards randomly
	random_shuffle(playerDeck.begin(), playerDeck.end());
	random_shuffle(roleDeck.begin(), roleDeck.end());

	
	//Infection deck initialization
	cout << "INITIALIZING DECK" << endl;
	InfectionDeck ideck = InfectionDeck(newMap.cities);
	ideck.init(48);
	ideck.initialInfection();

	for (int i = 0; i < playerNum; i++) {
		vector<Card*> picks;

		for (int j = 0; j < cardNum; j++) {
			picks.push_back(playerDeck.back());
			playerDeck.pop_back();
		}
		Player* player = &players.at(i);

		player->drawCards(picks, cardNum);

		player->setRole(*roleDeck.back());
		roleDeck.pop_back();
	}

	//player1.drawCards(playerDeck, 4);
	//player1.getRole();
	//player1.printPossessions();

	//player2.drawCards(playerDeck, 4);
	//player2.getRole();
	//player2.printPossessions();


	//Displaying player locations
	for(int i=0; i<playerNum; i++) cout << "Player " << i << " at" << newMap.cities[players.at(i).getLocation()]->getName() << endl;
	
	
	bool gameover = false;

	// This loop ensures that each player gets a turn one after te other followed by inection turns
	while (!gameover) {   //If gameover is true we will exit the loop and that ends the game

		for (int i = 0; i < playerNum; i++) {
			players.at(i).startTurn();
			cout << "------------------PLAYER 1 TURN------------------" << endl;
			while (players.at(i).checkAction())
			{
				//Displaying the possible actions the player can make
				cout << "Player 1 at " << newMap.cities[players.at(i).getLocation()]->getName() << endl;
				cout << "Player 1: Choose your action..." << endl;
				players.at(i).displayActionsLeft();
				cout << "1. Drive/Ferry" << endl;
				cout << "2. Direct Flight" << endl;
				cout << "3. Charter Flight" << endl;
				cout << "4. Shuttle Flight" << endl;
				cout << "5. Build a Research Station" << endl;
				cout << "6. Treat Disease" << endl;
				cout << "7. Share Knowledge" << endl;
				cout << "8. Discover a Cure" << endl;
				char action;
				cin >> action;

				switch (action) {
				case '1':	//Drive/Ferry
				{
					newMap.showCity(players.at(i).getLocation());
					int city;
					cin >> city;
					players.at(i).move(city);

					break;
				}
				case '2':	//Direct Flight: Discard a City card to move to the city named on the card.
				{
					players.at(i).displayHand();

					int cardInt;

					cin >> cardInt;

					players.at(i).flight(players.at(i).getHand()[cardInt]->getId());

					players.at(i).discard(cardInt);
					break;
				}
				case '3':	//Charter Flight: Discard the City card that matches the city you are in to move to any city.
				{
					players.at(i).displayHand();

					int cardInt;

					cin >> cardInt;

					if (players.at(i).getHand()[cardInt]->getId() == players.at(i).getLocation())
					{
						players.at(i).flight(players.at(i).getHand()[cardInt]->getId());

						players.at(i).discard(cardInt);
					}
					break;
				}
				case '4': //Shuttle Flight	Move from a city with a research station to any other city that has a research station.
				{
					City* location = newMap.accessCity(players.at(i).getLocation());

					if (location->researchCenter == true)
					{

						for (int i = 0; i < 47; i++)
						{
							City* newLoc = newMap.accessCity(i);
							if (newLoc->researchCenter == true)
							{
								cout << newLoc->accessCity() << newLoc->getName();
							}
						}
						int newLocation;
						cout << "Enter the ID of the city you want to move to:" << endl;
						cin >> newLocation;

						players.at(i).flight(players.at(i).getHand()[newLocation]->getId());

					}
					break;
				}
				case '5': //Building a Research Station

				{
					players.at(i).displayHand();

					int cardInt;

					cin >> cardInt;

					City* location = newMap.accessCity(players.at(i).getLocation());

					players.at(i).treatDisease(newMap);

					players.at(i).discard(cardInt);

					break;

				}

				case '6':	//Treating a disease

				{
					City* location = newMap.accessCity(players.at(i).getLocation());

					players.at(i).treatDisease(newMap);

					break;
				}

				case '7': //Sharing knowledge

				{
					cout << "With which player do you want to share knowledge?";
					int a;
					cin >> a;
					Player* buddy = &players.at(a);
					players.at(i).shareKnowledge(*buddy);
					break;
				}

				case '8'://Discover a Cure
				{

					players.at(i).displayHand();

					int cardInt1, cardInt2, cardInt3, cardInt4, cardInt5;

					cout << "Enter the ID of the cards you want to discard:" << endl;

					cin >> cardInt1 >> cardInt2 >> cardInt3 >> cardInt4 >> cardInt5;

					players.at(i).treatDisease(newMap);

					players.at(i).discard(cardInt1);
					players.at(i).discard(cardInt2);
					players.at(i).discard(cardInt3);
					players.at(i).discard(cardInt4);
					players.at(i).discard(cardInt5);

					break;
				}
				}
			}




			////////////END TURN / DRAW 2 PLAYER CARDS////////////
			players.at(i).concludeTurn(playerDeck);



			/////////////INFECT CITIES///////////////
			cout << "------------------INFECTION TURN------------------" << endl;
			cout << "Cubes remaining: " << InfectionDeck::infectionCubes << ", Outbreaks: " << InfectionDeck::numberOutbreaks << ", Marker position: " << InfectionDeck::infectionMarker << "(" << InfectionDeck::markerValues[InfectionDeck::infectionMarker] << ")" << endl;
			ideck.playInfection();
			if (InfectionDeck::infectionCubes < 0) {
				//gameover = true;
				cout << "GAME OVER: You have run out of infection cubes" << endl;
				break;
			}
			if (InfectionDeck::numberOutbreaks >= 8) {
				//gameover = true;
				cout << "GAME OVER: Too many outbreaks have occurred" << endl;
				break;
			}
		}


	}


	system("pause"); //windows only
	return 0;
}

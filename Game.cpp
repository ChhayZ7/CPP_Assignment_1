#include "Game.h"
#include "Player.h"
#include "CannonCard.h"
#include "ChestCard.h"
#include "KeyCard.h"
#include "SwordCard.h"
#include "HookCard.h"
#include "OracleCard.h"
#include "MapCard.h"
#include "MermaidCard.h"
#include "KrakenCard.h"
#include <algorithm>
#include <random>
#include <string>
#include <iostream>

Game::Game(): _currentPlayer(0), _turn(1), _round(1) {
	//Dynamically allocate both players
	_players[0] = new Player();
	_players[1] = new Player();
}

Game::~Game() {
	//Delete cards in player banks and play areas
	for (Card* card : _players[0]->getBank()) delete card;
	for (Card* card : _players[0]->getPlayArea()) delete card;
	for (Card* card : _players[1]->getBank()) delete card;
	for (Card* card : _players[1]->getPlayArea()) delete card;

	//Clean up players
	delete _players[0];
	delete _players[1];

	//Clean up any cards still in the deck or discard pile
	//(cards in player banks/player areas are already moved here or deleted)
	for (Card* card : _deck) delete card;

	for (Card* card : _discard) delete card;
}

void Game::start() {
	printHeader();
	std::cout << "Starting Dead Man's Draw++!" << std::endl;

	//Build the full 54-card deck and shuffle it
	createDeck();
	shuffleDeck(_deck);

	//Play up to 20 turns total (10 per player), or until the deck runs out
	int totalTurns = 20;
	for (int i = 0; i < totalTurns && !_deck.empty(); i++) {
		std::cout << "--- Round " << _round << ", Turn " << _turn << " ---" << std::endl;
		runTurn();

		//Update the turn and round counter
		_turn++;

		if (_turn % 2 == 1) {
			_round++;
		}

		//Flip between player 0 and 1 each turn
		//(1 - 0 = 1, 1 - 1 = 0)
		_currentPlayer = 1 - _currentPlayer;
	}

	endGame();
}

void Game::runTurn() {
	Player* player = getCurrentPlayer();
	player->resetBust(); // reset the player's bust status at the start of their turn

	//Show whose turn it is and what they currently have in their bank
	std::cout << player->getName() << "'s turn." << std::endl;
	player->printBank();

	bool turnOver = false;

	//Keep drawing until the player busts, banks, or the deck runs out
	while (!turnOver && !_deck.empty()) {
		//Draw the top card from the deck
		Card* card = drawFromDeck();
		std::cout << player->getName() << " draws a " << card->str() << std::endl;

		//Add the card to the play area
		//Returns true if this causes a bust
		bool busted = player->playCard(card, *this);

		if (busted) {
			//Bust - move all cards from the play area to the discard pile and end the turn
			player->bustDiscard(*this);
			turnOver = true;
		} else if (player->hasBustedThisTurn()) {
			//Bust was already handled inside the card ability (e.g.Kraken)
			//bustDiscard() was already called, so just end the turn here
			turnOver = true;
		}
		else {
			//No bust - show the play area and ask if they want to keep drawing or bank
			player->printPlayArea();

			std::cout << "Draw again? (y/n): ";
			std::string input;
			std::cin >> input;

			if (input != "y") {
				// Player chose to stop drawing and bank their cards, so move all cards from the play area to the bank and end the turn
				player->bankCard(*this);
				turnOver = true;
			}
		}
	}

	//If the deck ran out while the player was still drawing, bank what they have
	if (_deck.empty() && !turnOver) {
		std::cout << "The deck is out of cards! " << player->getName() << " banks what they have." << std::endl;
		player->bankCard(*this);
	}

}

void Game::endGame() {
	std::cout << "--- Game Over ---" << std::endl;

	//Print each player's final bank and score
	_players[0]->printBank();
	_players[1]->printBank();

	int score0 = _players[0]->getScore();
	int score1 = _players[1]->getScore();

	//Declare the winner
	if (score0 > score1) {
		std::cout << _players[0]->getName() << " wins!" << std::endl;
	}
	else if (score1 > score0) {
		std::cout << _players[1]->getName() << " wins!" << std::endl;
	}
	else {
		std::cout << "It's a tie!" << std::endl;
	}
}

void Game::createDeck() {
	//Standard suits have values 2-7 (6 cards each)
	int standardValues[] = { 2, 3, 4, 5, 6, 7 };

	//Mermaid is the premium suit which has values 4-9
	int mermaidValues[] = { 4, 5, 6, 7, 8, 9 };

	//Add 6 cards of each suit to the deck: 9 suits x 6 cards = 54 total
	for (int v : standardValues) _deck.push_back(new CannonCard(v));
	for (int v : standardValues) _deck.push_back(new ChestCard(v));
	for (int v : standardValues) _deck.push_back(new KeyCard(v));
	for (int v : standardValues) _deck.push_back(new SwordCard(v));
	for (int v : standardValues) _deck.push_back(new HookCard(v));
	for (int v : standardValues) _deck.push_back(new OracleCard(v));
	for (int v : standardValues) _deck.push_back(new MapCard(v));
	for (int v : standardValues) _deck.push_back(new KrakenCard(v));
	for (int v : mermaidValues) _deck.push_back(new MermaidCard(v));

}

//Shuffes a card collection in place using a seeded random engine
//(This is the exact shuffle code provided in the assignment spec)
void Game::shuffleDeck(CardCollection& cards) {
	CardCollection shuffled{ cards.begin(), cards.end() };
	std::shuffle(shuffled.begin(), shuffled.end(), std::mt19937{ std::random_device{}() });
	std::copy(shuffled.begin(), shuffled.end(), cards.begin());
}

//Takes the card from the back of the vector (the top of the deck)
Card* Game::drawFromDeck() {
	if (_deck.empty()) return nullptr;

	Card* card = _deck.back();
	_deck.pop_back();
	return card;
}

//Takes the most recently discarded card from the discard pile
Card* Game::drawFromDiscard() {
	if (_discard.empty()) return nullptr;

	Card* card = _discard.back();
	_discard.pop_back();
	return card;
}

void Game::addToDiscard(Card* card) {
	_discard.push_back(card);
}

void Game::printHeader() const
{
	//ASCII art title screen printed at the start of the game
	std::cout << R"(
 ____                    _   __  __             _       ____
|  _ \  ___  __ _  __| | |  \/  | __ _ _ __( )___  |  _ \ _ __ __ ___      _|  |  |
| | | |/ _ \/ _` |/ _` | | |\/| |/ _` | '_ \|// __| | | | | '__/ _` \ \ /\ / /  +  +
| |_| |  __/ (_| | (_| | | |  | | (_| | | | | \__ \ | |_| | | | (_| |\ V  V /   +  +
|____/ \___|\__,_|\__,_| |_|  |_|\__,_|_| |_| |___/ |____/|_|  \__,_| \_/\_/
)" << std::endl;
}

Player* Game::getCurrentPlayer() const {
	return _players[_currentPlayer];
}

//The other player is the one that is not the current player, so we return 1 - _currentPlayer
Player* Game::getOtherPlayer() const {
	return _players[1 - _currentPlayer];
}
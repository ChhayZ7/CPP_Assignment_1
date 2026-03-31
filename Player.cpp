#include "Player.h"
#include "Game.h"
#include <iostream>

Player::Player() {
	// Pick a random name from the fixed list provided in the spec
	std::string names[] = { "Sam", "Billy", "Jen", "Bob", "Sally",
	"Joe", "Sue", "Sasha", "Tina", "Marge" };

	_name = names[rand() % 10];
}

Player::~Player() {
	// 
}

bool Player::playCard(Card* card, Game& game) {
	// Check if there is already a card of the same suit in the play area.
	// If so, this is a bust and the card is discarded, return true to indicate a bust
	for (Card* c : _playArea) {
		if (c->type() == card->type()) {
			_playArea.push_back(card);
			return true; // busted
		}
	}

	// Otherwise, add the card to the play area and trigger its ability, return false to indicate not a bust
	_playArea.push_back(card);
	card->play(game, *this);
	return false; // not busted
}

void Player::bankCard(Game& game) {
	// Give each card a chance to trigger its "on bank" effect before moving.
	// Only ChestCard actually does anything here (Chest+Key bonus).
	for (Card* card : _playArea) {
		card->willAddToBank(game, *this);
	}

	// Move all cards from the play area into the bank
	for (Card* card : _playArea) {
		_bank.push_back(card);
	}
	_playArea.clear();

	// Show the updated bank after banking
	printBank();
}

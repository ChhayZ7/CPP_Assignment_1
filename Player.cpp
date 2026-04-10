#include "Player.h"
#include "Game.h"
#include <iostream>
#include <map>
#include <algorithm>

Player::Player() : _bustedThisTurn(false) {
	//Pick a random name from the fixed list provided in the spec
	std::string names[] = { "Sam", "Billy", "Jen", "Zack", "Chhay",
	"Vivian", "Ken", "Wayne", "Tina", "Marge" };

	_name = names[rand() % 10];
}

Player::~Player() {
	//Cards are owned and deleted by the Game and not the player.
	//If we deleted them here we would get a double-free crash. 
}

bool Player::playCard(Card* card, Game& game) {
	//Check if there is already a card of the same suit in the play area.
	//If so, this is a bust and the card is discarded, return true to indicate a bust
	for (auto* c : _playArea) {
		if (c->type() == card->type()) {
			_playArea.push_back(card);
			return true; //busted
		}
	}

	//Otherwise, add the card to the play area and trigger its ability, return false to indicate not a bust
	_playArea.push_back(card);
	card->play(game, *this);
	return false; // not busted
}

void Player::bankCard(Game& game) {
	//Give each card a chance to trigger its "on bank" effect before moving.
	//Only ChestCard actually does anything here (Chest+Key bonus).
	_bustedThisTurn = false; // reset for next turn
	for (auto* card : _playArea) {
		card->willAddToBank(game, *this);
	}

	//Move all cards from the play area into the bank
	for (auto* card : _playArea) {
		_bank.push_back(card);
	}
	_playArea.clear();

	//Show the updated bank after banking
	printBank();
}

void Player::bustDiscard(Game& game) {
	//Send every card in the play area to the shared discard pile
	_bustedThisTurn = true;
	std::cout << "BUST! " << _name << " loses all cards in play area." << std::endl;
	for (auto* card : _playArea) {
		game.addToDiscard(card);
	}
	_playArea.clear();
}

bool Player::isBust() const {
	//Compare every pair if cards and if any two share a suit, the player is bust.
	//We start j at i+1 so we do not compare a card with itself.
	for (int i = 0; i < (int)_playArea.size(); i++) {
		for (int j = i + 1; j < (int)_playArea.size(); j++) {
			if (_playArea[i]->type() == _playArea[j]->type()) {
				return true;
			}
		}
	}
	return false;
}

int Player::getScore() const {
	//Use a map to track the highest value seen for each suit.
	//Key = suit, Value = highest value of that suit seen so far.
	auto scored = std::map<CardType, int>{};

	for (auto* card : _bank) {
		CardType t = card->type();

		//If we have not seen this suit yet, or this card is worth more, update it
		if (scored.find(t) == scored.end() || card->getValue() > scored[t]) {
			scored[t] = card->getValue();
		}
	}

	//Add up the best card from each suit
	int total = 0;
	for (auto& pair : scored) {
		total += pair.second;
	}
	return total;
}

void Player::printPlayArea() const {
	std::cout << _name << "'s Play Area:" << std::endl;
	printCardCollection(_playArea);
}

void Player::printBank() const {
	std::cout << _name << "'s Bank:" << std::endl;
	printCardCollection(_bank);
	std::cout << "| Score: " << getScore() << std::endl;
}

void Player::printCardCollection(const CardCollection& collection) const {
	//Group all cards by their suit using a map
	auto grouped = std::map<CardType, std::vector<Card*>>{};
	for (auto* card : collection) {
		grouped[card->type()].push_back(card);
	}

	//Print each suit on its own line, sorted highest value first
	for (auto& pair : grouped) {
		auto& cards = pair.second;

		//Sort descending so the highest value card appears first
		std::sort(cards.begin(), cards.end(), [](Card* a, Card* b) {
			return a->getValue() > b->getValue();
			});

		std::cout << " ";
		for (auto* card : cards) {
			std::cout << card->str() << " ";
		}
		std::cout << std::endl;
	}
}
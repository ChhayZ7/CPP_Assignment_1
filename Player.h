#pragma once
#include <string>
#include "Card.h"

class Game;

class Player {
public:
	Player();
	~Player();

	bool playCard(Card* card, Game& game);
	void bankCard(Game& game);
	void bustDiscard(Game& game);
	bool isBust() const;
	int getScore() const;
	void printPlayerArea() const;
	void printBank() const;

	// Getters
	const std::string& getName() const { return _name; }
	CardCollection& getPlayArea() { return _playArea; }
	CardCollection& getBank() { return _bank; }

private:
	std::string _name;
	CardCollection _playArea;
	CardCollection _bank;
	void printCardCollection(const CardCollection& collection) const;

};

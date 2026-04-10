#ifndef PLAYER_H
#define PLAYER_H
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
	void printPlayArea() const;
	void printBank() const;

	//Getters
	const std::string& getName() const { return _name; }
	CardCollection& getPlayArea() { return _playArea; }
	CardCollection& getBank() { return _bank; }
	bool hasBustedThisTurn() const { return _bustedThisTurn; }
	void resetBust() { _bustedThisTurn = false; }

private:
	std::string _name;
	CardCollection _playArea;
	CardCollection _bank;
	bool _bustedThisTurn;
	void printCardCollection(const CardCollection& collection) const;

};

#endif
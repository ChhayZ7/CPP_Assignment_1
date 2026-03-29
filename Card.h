#pragma once
#include <string>
#include <vector>

// All the possible card suits in the game
enum CardType
{
	Cannon,
	Chest,
	Key,
	Sword,
	Hook,
	Oracle,
	Map, 
	Mermaid,
	Kraken
};

class Game;
class Player;


class Card {
public:
	Card(int value, CardType type) : _value(value), _cardType(type) {}
	virtual ~Card() {};

	const CardType& type() const { return _cardType; }
	int getValue() const { return _value; }

	// Rreturns the card as a string like "Cannon 3" or "Key 5"
	virtual std::string str() const = 0;

	// Executes this card's special ability when its drawn
	virtual void play(Game& game, Player& player) = 0;

	// Called just before this card is moved into the player's bank
	virtual void willAddToBank(Game& game, Player& player) {}

protected:
	int _value;
	CardType _cardType;
};

typedef std::vector<Card*> CardCollection;
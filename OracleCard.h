#ifndef ORACLE_CARD_H
#define ORACLE_CARD_H
#include "Card.h"
#include <string>

//OracleCard
//Ability: peek at the top card of the deck before deciding whether to draw
class OracleCard : public Card {
public:
	OracleCard(int value) : Card(value, CardType::Oracle) {}
	std::string str() const override;
	void play(Game& game, Player& player) override;
};

#endif
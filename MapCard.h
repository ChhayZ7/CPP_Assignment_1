#ifndef MAP_CARD_H
#define MAP_CARD_H
#include "Card.h"
#include <string>

//MapCard
//Ability: draw 3 cards from the discard pile, choose one to play into
//the play area, put the others back
class MapCard : public Card {
public:
	MapCard(int value) : Card(value, CardType::Map) {}
	std::string str() const override;
	void play(Game& game, Player& player) override;
};

#endif

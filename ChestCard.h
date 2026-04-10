#ifndef CHEST_CARD_H
#define CHEST_CARD_H
#include "Card.h"
#include <string>

//ChestCard
//Ability: no immediate effect.
//If banked alongside a Key card, it draws bonus cards from the discard pile equal to
//the number of cards being banked this turn as you moved into your bank
class ChestCard : public Card {
public:
	ChestCard(int value) : Card(value, CardType::Chest) {}
	std::string str() const override;
	void play(Game& game, Player& player) override;

	// Overrides willAddToBank to trigger the Chest+Key bonus at banking time
	void willAddToBank(Game& game, Player& player) override;
};

#endif


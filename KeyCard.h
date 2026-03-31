#pragma once
#include "Card.h"
#include <string>

// KeyCard
// Ability: no immediate effect, pairs with ChestCard at banking time
class KeyCard : public Card {
public:
	KeyCard(int value) : Card(value, CardType::Key) {}
	std::string str() const override;
	void play(Game& game, Player& player) override;
};

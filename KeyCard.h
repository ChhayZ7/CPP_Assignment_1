#pragma once
#include "Card.h"
#include <string>

// KeyCard
// Ability: discard the highest value card of any suit from the opponent's bank
class KeyCard : public Card {
public:
	KeyCard(int value) : Card(value, CardType::Key) {}
	std::string str() const override;
	void play(Game& game, Player& player) override;
};

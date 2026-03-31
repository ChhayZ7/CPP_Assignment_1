#pragma once
#include "Card.h"
#include <string>

// CannonCard
// Ability: discard the highest value card of any suit from the opponent's bank
class CannonCard : public Card {
public:
	CannonCard(int value) : Card(value, CardType::Cannon) {}
	std::string str() const override;
	void play(Game& game, Player& player) override;
};

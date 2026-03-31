#pragma once
#include "Card.h"
#include <string>

// SwordCard
// Ability: steal the highest value card of any suit from the opponet's bank
// into your own play area
class SwordCard : public Card {
public:
	SwordCard(int value) : Card(value, CardType::Sword) {}
	std::string str() const override;
	void play(Game& game, Player& player) override;
};
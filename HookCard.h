#pragma once
#include "Card.h"
#include <string>

// HookCard
// Ability: pull the highest value card of any suit from your own bank
// back into your area 
class HookCard : public Card {
public:
	HookCard(int value) : Card(value, CardType::Hook) {}
	std::string str() const override;
	void play(Game& game, Player& player) override;
};

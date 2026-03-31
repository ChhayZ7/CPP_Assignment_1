#pragma once
#include "Card.h"
#include <string>

// KrakenCard
// Ability: forces you to draw and play 3 cards from the deck consecutively
// (you cannot stop, if any causes a bust, the turn ends immediately)
class CannonCard : public Card {
public:
	CannonCard(int value) : Card(value, CardType::Cannon) {}
	std::string str() const override;
	void play(Game& game, Player& player) override;
};

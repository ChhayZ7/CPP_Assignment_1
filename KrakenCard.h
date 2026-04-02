#pragma once
#include "Card.h"
#include <string>

// KrakenCard
// Ability: forces you to draw and play 3 cards from the deck consecutively
// (you cannot stop, if any causes a bust, the turn ends immediately)
class KrakenCard : public Card {
public:
	KrakenCard(int value) : Card(value, CardType::Kraken) {}
	std::string str() const override;
	void play(Game& game, Player& player) override;
};

#ifndef MERMAID_CARD_H
#define MERMAID_CARD_H
#include "Card.h"
#include <string>

//MermaidCard
//Ability: none, but Mermaids have higher point values (4-9 instead of 2-7)
class MermaidCard : public Card {
public:
	MermaidCard(int value) : Card(value, CardType::Mermaid) {}
	std::string str() const override;
	void play(Game& game, Player& player) override;
};

#endif
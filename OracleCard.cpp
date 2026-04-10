#include <iostream>
#include "OracleCard.h"
#include "Card.h"
#include "Game.h"
#include "Player.h"

//OracleCard
//Ability: peek at the top card of the deck before deciding whether to draw
std::string OracleCard::str() const {
	return "Oracle(" + std::to_string(_value) + ")";
}

void OracleCard::play(Game& game, Player& player) {
	CardCollection& deck = game.getDeck();

	if (deck.empty()) {
		std::cout << " No cards left in deck." << std::endl;
		return;
	}

	//Just show the top card but don't remove it from the deck
	Card* top = deck.back();
	std::cout << " The Oracle sees a " << top->str() << std::endl;
}
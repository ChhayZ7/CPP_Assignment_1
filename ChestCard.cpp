#include <iostream>
#include "ChestCard.h"
#include "Card.h"
#include "Game.h"
#include "Player.h"

// ChestCard
// Ability: no immediate effect.
// If banked alongside a Key card, it draws bonus cards from the discard pile equal to
// the number of cards being banked this turn as you moved into your bank
std::string ChestCard::str() const {
	return "Chest(" + std::to_string(_value) + ")";
}

void ChestCard::play(Game& game, Player& player) {
	// Nothing happens when drawn, but the Chest+Key bonus is triggered in willAddToBank when banking
	std::cout << " No immediate effect. If banked with key, draw as many bonus cards from the Discard pile as you moved into your Bank." << std::endl;
}

void ChestCard::willAddToBank(Game& game, Player& player) {
	// This runs just before banking, check if a Key is also in the play area
	bool hasKey = false;
	for (Card* c: player.getPlayArea()) {
		if (c->type() == CardType::Key) {
			hasKey = true;
			break;
		}
	}

	// If there is no Key, the bonus does not activate
	if (!hasKey) return;

	// Bonus activates! Draw as many cards from the discard pile as are being banked this turn
	int bonusCount = (int)player.getPlayArea().size();

	std::cout << " Chest and Key activated. Added ";
	bool first = true;
	for (Card* c : player.getPlayArea()) {
		if (!first) std::cout << ", ";
		std::cout << c->str();
		first = false;
	}
	std::cout << ", to your bank." << std::endl;

	for (int i = 0; i < bonusCount; i++) {
		Card* bonus = game.drawFromDiscard();
		if (bonus == nullptr) {
			std::cout << " No more cards in discard. Bonus draw ends." << std::endl;
			break;
		}
		// Add the bonus card directly to the bank (not the play area)
		player.getBank().push_back(bonus);
		std::cout << " Bonus card drawn: " << bonus->str() << std::endl;
	}
}
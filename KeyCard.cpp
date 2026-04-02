#include <string>
#include "Card.h"
#include "KeyCard.h"
#include <iostream>
#include "Game.h"
#include "Player.h"

// KeyCard
// Ability: no immediate effect, pairs with ChestCard at banking time
std::string KeyCard::str() const {
	return "Key(" + std::to_string(_value) + ")";
}

void KeyCard::play(Game& game, Player& player) {
	// Nothig happens when drawn, but the Chest+Key bonus is triggered in ChestCard::willAddToBank when banking
	std::cout << " No immediate effect. If banked with a chest, draw as many bonus cards from the Discard pile as you moved into your Bank." << std::endl;

}
#include <iostream>
#include "CannonCard.h"
#include "Card.h"
#include "Game.h"
#include "Player.h"
#include "CardHelper.h"

//CannonCard
//Ability: discard the highest value card of any suit from the opponent's bank
std::string CannonCard::str() const {
	return "Cannon(" + std::to_string(_value) + ")";
}

void CannonCard::play(Game& game, Player& player) {
	Player* other = game.getOtherPlayer();
	CardCollection& otherBank = other->getBank();

	if (otherBank.empty()) {
		std::cout << " No cards in opponent's Bank. Play continues." << std::endl;
		return;
	}

	//Let the current player choose which suit to target
	std::cout << " Discard the top card of any suit from the other player's Bank:" << std::endl;
	CardType suit = selectSuit(otherBank, " Select a suit from " + other->getName() + "'s Bank:");

	//Remove and discard the highest card of that suit
	Card* removed = removeTopCard(otherBank, suit);
	if (removed) {
		game.addToDiscard(removed);
		std::cout << "  Discarded " << removed->str() << " from " << other->getName() << "'s Bank." << std::endl;
	}

}
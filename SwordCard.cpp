#include <iostream>
#include "SwordCard.h"
#include "Card.h"
#include "Game.h"
#include "Player.h"
#include "CardHelper.cpp"

// SwordCard
// Ability: steal the highest value card of any suit from the opponet's bank
// into your own play area
std::string SwordCard::str() const {
	return "Sword(" + std::to_string(_value) + ")";
}

void SwordCard::play(Game& game, Player& player) {
	Player* other = game.getOtherPlayer();
	CardCollection& otherBank = other->getBank();

	if (otherBank.empty()) {
		std::cout << " No cards in other player's Bank. Play continues." << std::endl;
		return;
	}

	std::cout << " Steal the top card of any suit from the other player's Bank into your Play Area:" << std::endl;
	CardType suit = selectSuit(otherBank, " Select a suit from " + other->getName() + "'s Bank:");

	Card* stolen = removeTopCard(otherBank, suit);
	if (stolen) {
		// Playing the stolen card into the play area, this could trigger a bust
		bool busted = player.playCard(stolen, game);
		if (busted) {
			player.bustDiscard(game);
		}
	}
}
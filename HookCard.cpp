#include <iostream>
#include "HookCard.h"
#include "Card.h"
#include "Game.h"
#include "Player.h"
#include "CardHelper.cpp"

// HookCard
// Ability: pull the highest value card of any suit from your own bank
// back into your area 
std::string HookCard::str() const {
	return "Hook(" + std::to_string(_value) + ")";
}

void HookCard::play(Game& game, Player& player) {
	CardCollection& bank = player.getBank();

	if(bank.empty()) {
		std::cout << " No cards in your Bank. Play continues." << std::endl;
		return;
	}

	std::cout << " Select a highest-value card from any of the suits in your Bank:" << std::endl;
	CardType suit = selectSuit(bank, " Select a suit from your Bank:");

	Card* pulled = removeTopCard(bank, suit);
	if (pulled) {
		// Add the pulled card back into the play area (may cause a bust)
		bool busted = player.playCard(pulled, game);
		if (busted) {
			player.bustDiscard(game);
		}
	}
}
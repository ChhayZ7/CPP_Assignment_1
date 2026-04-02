#include <iostream>
#include "KrakenCard.h"
#include "Card.h"
#include "Game.h"
#include "Player.h"
#include "CardHelper.cpp"

// KrakenCard
// Ability: forces you to draw and play 3 cards from the deck consecutively
// (you cannot stop, if any causes a bust, the turn ends immediately)
std::string KrakenCard::str() const {
	return "Kraken(" + std::to_string(_value) + ")";
}

void KrakenCard::play(Game& game, Player& player) {
	std::cout << " Draw 3 cards from the deck and play each:" << std::endl;

	for (int i = 0; i < 3; i++) {
		if (game.getDeck().empty()) {
			std::cout << " Deck is empty. Kraken draw ends." << std::endl;
			break;
		}

		// Forcibly draw and play each card (the player has no choice)
		Card* card = game.drawFromDeck();
		std::cout << " " << player.getName() << " draw a " << card->str() << std::endl;

		bool busted = player.playCard(card, game);
		if (busted) {
			// Bust mid-Kraken - discard everythomg amd end the turn immediately
			player.bustDiscard(game);
			return;
		}
	}
}
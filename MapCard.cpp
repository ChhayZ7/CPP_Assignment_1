#include <iostream>
#include "MapCard.h"
#include "Card.h"
#include "Game.h"
#include "Player.h"
#include "CardHelper.h"

// MapCard
// Ability: draw 3 cards from the discard pile, choose one to play into
// the play area, put the others back
std::string MapCard::str() const {
	return "Map(" + std::to_string(_value) + ")";
}

void MapCard::play(Game& game, Player& player) {
	CardCollection drawn;

	// Draw up to 3 cards from the discard (may be fewer if discard is small)
	for (int i = 0; i < 3; i++) {
		Card* c = game.drawFromDiscard();
		if (c == nullptr) break;
		drawn.push_back(c);
	}

	if (drawn.empty()) {
		std::cout << " No cards in the discard. Play continues." << std::endl;
		return;
	}

	// Show the drawn cards as numbered options
	std::cout << " Draw 3 cards from the discard and pick one to add to the play area:" << std::endl;
	for (int i = 0; i < (int)drawn.size(); i++) {
		std::cout << " (" << (i + 1) << ") " << drawn[i]->str() << std::endl;
	}

	// Get the player's choice
	int choice = 0;
	while (choice < 1 || choice >(int)drawn.size()) {
		std::cout << " Which card do you pick? ";
		std::cin >> choice;
		if (!(std::cin >> choice)) {
			// clear the error flag and discard the bad input
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << " Invalid input. Please enter a number." << std::endl;
			choice = 0; // reset so the loop continues
		}
		else if (choice < 1 || choice >(int)drawn.size()) {
			std::cout << " Invalid choice. Please enter a number between 1 and " << drawn.size() << "." << std::endl;
		}
	}

	// Return the unchosen cards to the discard pile
	for (int i = 0; i < (int)drawn.size(); i++) {
		if (i != choice - 1) {
			game.addToDiscard(drawn[i]);
		}
	}

	// Play the chosen cards into the play area (this may cause a bust)
	Card* chosen = drawn[choice - 1];
	bool busted = player.playCard(chosen, game);
	if (busted) {
		player.bustDiscard(game);
	}

}
#include <iostream>
#include "Card.h"
#include "Game.h"
#include "Player.h"
#include "CardHelper.h"


CardType selectSuit(const CardCollection& bank, const std::string& prompt) {
	//Collect one entry per unique suit
	std::vector<CardType> suits;
	for (auto* c : bank) {
		bool found = false;
		for (CardType t : suits) {
			if (t == c->type()) {
				found = true;
				break;
			}
		}
		if (!found) {
			suits.push_back(c->type());
		}
	}

	//Display the highest card of each suit as the selectable option
	std::cout << prompt << std::endl;
	for (int i = 0; i < (int)suits.size(); i++) {
		Card* top = nullptr;
		for (auto* c : bank) {
			if (c->type() == suits[i]) {
				if (top == nullptr || c->getValue() > top->getValue()) {
					top = c;
				}
			}
		}
		if (top != nullptr) {
			std::cout << " (" << (i + 1) << ") " << top->str() << std::endl;
		} else {
			std::cout << " (" << (i + 1) << ") [No card available]" << std::endl;
		}
	}

	//Keep asking until they enter a valid number
	int choice = 0;
	while (choice < 1 || choice >(int)suits.size()) {
		std::cout << "Which card do you pick? ";
		if (!(std::cin >> choice)) {
			//clear the error flag and discard the bad input when cin failed
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << " Invalid input. Please enter a number." << std::endl;
			choice = 0; //reset so the loop continues
		}
		else if (choice < 1 || choice >(int)suits.size()) {
			std::cout << " Invalid choice. Please enter a number between 1 and " << suits.size() << "." << std::endl;
		}
	}
	return suits[choice - 1];
}
Card* removeTopCard(CardCollection& collection, CardType suit) {
	Card* best = nullptr;
	int bestIndex = -1;

	//Loop through all cards to find the highest value one matching the suit
	for (int i = 0; i < (int)collection.size(); i++) {
		if (collection[i]->type() == suit) {
			if (best == nullptr || collection[i]->getValue() > best->getValue()) {
				best = collection[i];
				bestIndex = i;
			}
		}
	}

	//Remove the found card from the collection
	if (bestIndex >= 0) {
		collection.erase(collection.begin() + bestIndex);
	}
	return best;
}
#ifndef CARD_HELPER_H
#define CARD_HELPER_H
#include "Card.h"
#include <string>

//Display a numbered list of the highest value card per suit from a collection
//and returns the CardType of the suit the player chose.
CardType selectSuit(const CardCollection& bank, const std::string& prompt);

//Finds and removes the highest value card of a given suit from a collection.
//Returns the removed card, or nullptr if no card of that suit exists.
Card* removeTopCard(CardCollection& collection, CardType suit);

#endif


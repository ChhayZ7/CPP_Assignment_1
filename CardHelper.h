#pragma once
#include "Card.h"
#include <string>

CardType selectSuit(const CardCollection& bank, const std::string& prompt);
Card* removeTopCard(CardCollection& collection, CardType suit);


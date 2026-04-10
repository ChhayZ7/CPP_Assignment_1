#include <string>
#include "Card.h"
#include "MermaidCard.h"
#include <iostream>
#include "Game.h"
#include "Player.h"

//MermaidCard
//Ability: none, but Mermaids have higher point values (4-9 instead of 2-7)

std::string MermaidCard::str() const {
	return "Mermaid(" + std::to_string(_value) + ")";
}

void MermaidCard::play(Game& game, Player& Player) {
	std::cout << " No effect but Mermaids are worth more." << std::endl;
}
#pragma once
#include "Card.h"

class Player;

// Game is the main controller of the entire program.
// It owns the deck, discard pile, and both players.
// There should only ever be one Game instance at a time.
class Game {
public:
	Game(); // Creates the deck and both players
		~Game(); // Cleans up all allocated memory

		void start(); //Entry point for the game, shuffles deck and runs all turns
		void runTurn(); // Runs a single player's turn (draw, ability, bank or bust)
		void endGame(); // Prints final scores and declares a winner

		// Deck and discard pile operations used by Game and card abilities
		Card* drawFromDeck();
		Card* drawFromDiscard();
		void addToDiscard(Card* card);
		void shuffleDeck(CardCollection& cards);

		// Getters used by card abilities so they can interact with the game state
		Player* getCurrentPlayer() const;
		Player* getOtherPlayer() const;
		CardCollection& getDeck() { return _deck; }
		CardCollection& getDiscard() { return _discard; }
		int getTurn() const { return _turn; }
		int getRound() const { return _round; }

private:
	CardCollection _deck;
	CardCollection _discard;
	Player* _players[2];
	int _currentPlayer;
	int _turn;
	int _round;

	void createDeck();
	void printHeader() const;
};

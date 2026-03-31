#pragma once
#include "Card.h"

class Player;

class Game {
public:
	Game();
		~Game();

		void start();
		void runTurn();
		void endTurn();

		Card* drawFromDeck();
		Card* drawFromDiscard();
		void addToDiscard(Card* card);
		void shuffleDeck(CardCollection& cards);

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

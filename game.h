#include <iostream>
#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
#include "deck.h"
#include "player.h"
#include "gameboard.h"
#include <algorithm>
#include <random>
#include <chrono>


class Game {

    
     public:
    //Attributes
    

    // stores list of players
    std::vector<std::string> playerList;

    // these are compositions of the Game
     Deck *card_deck;
     GameBoard *theBoard;

    // aggregrations created outside scope
     Player * p1;
     Player * p2;
     Player * p3;
     Player * p4;

    // constructor
    Game(Player *p1, Player *p2, Player *p3, Player *p4);

    // destructor
    ~Game();

    // responsible for adding players to the list and setting observers
    void make_game();

    // shuffles the cards in the deck class
    void shuffle(std::vector<std::string> & cards, std::default_random_engine rng);

    // deals the cards to four players
    void deal();

    // decides order of the game 
    void decide_order();

    // decides winner of the game
    void decide_winner();

    

};

#endif

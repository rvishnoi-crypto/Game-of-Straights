#include "game.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>


// constructor
Game::Game(Player *p1, Player *p2, Player *p3, Player *p4)
    : 
    p1{p1},
    p2{p2},
    p3{p3},
    p4{p4},
    card_deck{new Deck{}}, //stores the address of the heap loc
    theBoard{new GameBoard{}}
    {}

// Destructor 
Game::~Game (){
    delete card_deck;
    delete theBoard;
}

// other functions added later 

//adds the players to the game and sets observers
void Game::make_game() {
    //attaching observer
    // board observers each player 
    theBoard->attach(p1);
    theBoard->attach(p2);
    theBoard->attach(p3);
    theBoard->attach(p4);

    // each player observes the board
    p1->attach(theBoard);
    p2->attach(theBoard);
    p3->attach(theBoard);
    p4->attach(theBoard);    
}

//shuffles the same deck of cards
void Game::shuffle(std::vector<std::string> & cards, std::default_random_engine rng){
    std::shuffle( cards.begin(), cards.end(), rng );
}

// deals the cards to the players
void Game::deal(){
    //dealing p1
   for (int i=0; i<13; i++){
        p1->playerHand.emplace_back(card_deck->cardDeck[i]);
        //std::cout <<"dealt" << std::endl;
    }
    
    //dealing p2
    for (int i=13; i<26; i++){
       p2->playerHand.emplace_back(card_deck->cardDeck[i]);
    }
        
    //dealing p3
   for (int i=26; i<39; i++){
       p3->playerHand.emplace_back(card_deck->cardDeck[i]);
    }
       
    //dealing p4
   for (int i=39; i<52; i++){
       p4->playerHand.emplace_back(card_deck->cardDeck[i]);
    }
}

void Game::decide_order(){
    
    // decide whos gonna start the game
    int idx;
    for (int i=0; i<52 ; i++){
        if (card_deck->cardDeck[i]=="7S"){
            idx=i;
            //std::cout << "FOUND!" << idx << std::endl;
            break;
        }
    }
    if (idx>=0 && idx<13){
        playerList.emplace_back("P1");
        playerList.emplace_back("P2");
        playerList.emplace_back("P3");
        playerList.emplace_back("P4");
        p1->legalList.emplace_back("7S");
    }
    else if (idx>=13 && idx<26){
        playerList.emplace_back("P2");
        playerList.emplace_back("P3");
        playerList.emplace_back("P4");
        playerList.emplace_back("P1");
        p2->legalList.emplace_back("7S");
    }
    else if (idx>=26 && idx<39){
        playerList.emplace_back("P3");
        playerList.emplace_back("P4");
        playerList.emplace_back("P1");
        playerList.emplace_back("P2");
        p3->legalList.emplace_back("7S");
    }
    else if (idx>=39 && idx<52){
        playerList.emplace_back("P4");
        playerList.emplace_back("P1");
        playerList.emplace_back("P2");
        playerList.emplace_back("P3");
        p4->legalList.emplace_back("7S");
    }
}

void Game::decide_winner(){

    //go through player list and and calculate discard score
    int p1_score;
    int p2_score;
    int p3_score;
    int p4_score;

    //calculate the score for each player
    for (auto &p: playerList){
        if (p=="P1"){
            p1_score= p1->score();
        }
        else if (p=="P2"){
            p2_score= p2->score();
        }
        else if (p=="P3"){
            p3_score= p3->score();
        }
        else {
            p4_score= p4->score();
        }
    }

    // the one with minimum score wins;
    int min=100;
    int scores[]= {p1_score,p2_score,p3_score,p4_score};
     for (int i=0; i<4;i++) {
         if (scores[i] < min){
             min= scores[i];
         }
     }



    //int min = std::min(p1_score,p2_score,p3_score,p4_score);
    if (p1_score==min){
        std::cout << "Player<1> wins the round !"<<std::endl;
    }
    else if (p2_score==min){
        std::cout << "Player<2> wins the round !"<<std::endl;
    }
    else if (p3_score==min){
        std::cout << "Player<3> wins the round !"<<std::endl;
    }
    else  {
        std::cout << "Player<4> wins the round !"<<std::endl;
    }
    
}

#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <vector>
#include "observer.h"
#include "subject.h"

class Game;



class Player: public Subject, public Observer {

protected:

    //constructor 
    Player(); // so the children can use

public:

    std::vector<std::string> clubList;
    std::vector<std::string> spadeList;
    std::vector<std::string> diamondList;
    std::vector<std::string> heartList;
    std::vector<std::string> discardList;
    std::vector<std::string> legalList;
    std::vector<std::string> playerHand;

    //either h or c; 
    std::string type; 

    
    bool played= false;
    bool discarded = false;

    virtual ~Player(); // virtual destructor  
    virtual void play(Game *g) =0;

    // displays the players cards, discard list and table cards 
    virtual void player_choice_card() const=0;

    // Calculates the score based on the discard list 
    int score();

    virtual void rearrange(std::string human_cmd, std::string choice)=0;

    virtual bool valid(std::string human_cmd, std::string choice)=0;


};

#endif

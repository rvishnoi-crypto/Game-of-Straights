#ifndef HUMAN_H
#define HUMAN_H
#include <iostream>
#include <string>
#include <vector>
#include "player.h"
#include "observer.h"
#include "subject.h"
#include "game.h"
class Game;

class Human: public Player {
    public:
    Human();    
    virtual void play(Game *g) ;
    virtual void player_choice_card() const;

    //add notify and observer overrides later.

    virtual void notify( Subject & whoNotified ); 
    virtual std::string getInfo() const;

    virtual bool valid(std::string human_cmd, std::string choice);
    virtual void rearrange(std::string human_cmd, std::string choice);

};

#endif


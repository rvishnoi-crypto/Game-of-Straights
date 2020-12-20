#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <iostream>
#include <string>
#include <vector>
#include "observer.h"
#include "subject.h"

class GameBoard : public Subject , public Observer {

   // private:
    // list of list where inner list is a suite pile
    //std::vector<std::vector<std::string>> piles;

    //notify and attack functions later;

    public:
    GameBoard();
    std::string card_added;
    
    //just for testing 
   // void print_board();

    //notify function; 
    virtual void notify( Subject & whoNotified ) override; 

    //overridde subject method
    virtual std::string getInfo () const override;

};

#endif

#include "gameboard.h"


// Constructor
GameBoard::GameBoard(){
    //0= H
    //1= S
    //2= C
    //3= D
    
    //empty initalisation
    std::vector<std::vector<std::string>> piles;

    for(int i=0; i<4; i++){
        std::vector<std::string> suite;
        piles.emplace_back(suite);
    }


}

// default destructor 


//fill it later 
void GameBoard::notify( Subject & whoNotified ){
    
    //updated game board
    
    std::string card_played= whoNotified.getInfo();

    card_added= card_played;
    

    //informing all players my state changed
    //so they can be updated
    this->notifyObservers();

}

std::string GameBoard::getInfo () const {
    return card_added;
}

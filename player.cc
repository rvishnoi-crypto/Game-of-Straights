#include "player.h"
#include <iostream>
#include <string>
#include <algorithm>



Player::Player(){} // doesnt really do anything 
Player::~Player(){}


int Player::score(){
    // go through the discarded list and calculate score

    int player_score;

    for (auto &c: discardList){
        if (c[0]=='A'){
            player_score+=1;
        }
        else if (c[0]=='T'){
            player_score+=10;
        }
        else if (c[0]=='J'){
            player_score+=11;
        }
        else if (c[0]=='Q'){
            player_score+=12;
        }
        else if (c[0]=='K'){
            player_score+=13;
        }
        else {
            player_score+= int(c[0])-48;
        }
    }
    return player_score; 
}

#include "human.h"
#include "player.h"
#include <algorithm>


Human::Human()
    : Player{} //creates parent to use 
{}

// before each turn prints out what options the players have 
void Human::player_choice_card() const {
    std::cout << "Cards on the table:" <<std::endl;


    // printing clubs 
    std::cout << "Clubs:" << "< ";
  
   for (int i=0; i< (int)clubList.size()-1 ; i++){
        std::cout<< clubList[i] << " ";
    }
    std::cout << " >" << std::endl;

    
    //printing diamond
    std::cout << "Diamonds:" << "< ";
    for (int i=0; i< (int)diamondList.size()-1 ; i++){
        std::cout<< diamondList[i] << " ";
    }
    std::cout << " >" << std::endl;

    //printing hearts
    std::cout << "Hearts:" << "< ";
    for (int i=0; i<= (int)heartList.size()-1 ; i++){
        std::cout<< heartList[i] << " ";
    }
    std::cout << " >" << std::endl;

    //printing spades
    std::cout << "Spades:" << "<";
    for (int i=0; i<=(int)spadeList.size()-1 ; i++){
        std::cout<< spadeList[i] << " ";
    }
    std::cout << " >" << std::endl;

    //printing hand
    std::cout << "Your hand:" << "< ";
    for (int i=0; i<=(int)playerHand.size()-1 ; i++){
        std::cout<< playerHand[i] << " ";
    }
    std::cout << " >" << std::endl;

    //printing legal plays
    std::cout << "Legal plays:" << "< ";
    for (int i=0; i<= (int)legalList.size()-1 ; i++){
        std::cout<< legalList[i] << " ";
    }
    std::cout << " >" << std::endl;

    std::cout << "Discarded Cards:" << "< ";
    for (int i=0; i<= (int)discardList.size()-1 ; i++){
        std::cout<< discardList[i] << " ";
    }
    std::cout << " >" << std::endl;


}



//overriden observer and subject functions later

void Human::notify( Subject & whoNotified ){ // so this is when the gameboard updates the player

    //all list are updated
    std::string card_played= whoNotified.getInfo();
    if (card_played[1]=='H'){
        heartList.emplace_back(card_played);
    }

    if (card_played[1]=='S'){
        spadeList.emplace_back(card_played);
    }

    if (card_played[1]=='C'){
        clubList.emplace_back(card_played);
    }

    if (card_played[1]=='D'){
        diamondList.emplace_back(card_played);
    }
    
    //std::cout << card_played << std::endl;
    
    //updates legal cards
    for (int i=0; i< (int)playerHand.size(); i++){
        // if card is not in legal list 
        if (std::count(legalList.begin(),legalList.end(), playerHand[i])==0){
            
            // same rank diff suite
            if (playerHand[i][0]==card_played[0]){
                legalList.emplace_back(playerHand[i]);
            }

     //This is casuing the problem 
            // same suite 
            if (playerHand[i][1]==card_played[1]){

                if ((card_played[0]=='J' && ( playerHand[i][0]=='T' || playerHand[i][0]=='Q')) 
                ||  (card_played[0]=='Q' && ( playerHand[i][0]=='J' || playerHand[i][0]=='K')) 
                ||  (card_played[0]=='T' && ( playerHand[i][0]=='9' || playerHand[i][0]=='J')) 
                ||  (card_played[0]=='K' &&  playerHand[i][0]=='Q')
                ||  (card_played[0]=='A' &&  playerHand[i][0]=='2') 
                ||  (card_played[0]=='2' && ( playerHand[i][0]=='A' || playerHand[i][0]=='3'))  
                ||  (
                    (card_played[0]!='K' || card_played[0]!='Q' || card_played[0]!='J' || card_played[0]!='A' || card_played[0]!='T' || card_played[0]!='2' ) && 
                    ( (int(playerHand[i][0])-48) == (int(card_played[0]-48)-1) || ((int(playerHand[i][0])-48)== int(card_played[0]-48)+1))
                    ) 
                ){
                    legalList.emplace_back(playerHand[i]);
                }
            } 
            //
        }
        
    }    
}   




std::string Human::getInfo() const{return legalList[0];}


bool Human::valid(std::string human_cmd, std::string choice){
        int k= std::count(playerHand.begin(), playerHand.end(), choice) ;
        int j= std::count(legalList.begin(), legalList.end(), choice) ;
       // std::cout << k << " " << j << std::endl;
        
        if ((human_cmd=="discard"|| human_cmd=="\ndiscard") && 
            legalList.empty()==true &&
            k
            ){
                return true;
        }
        else if ((human_cmd=="play" || human_cmd=="\nplay")  && 
            k==1 && j==1
            ){  //std::cout << "Hello" <<std::endl;
                return true;
        }
        else {
            return false;}   
}

void Human::rearrange(std::string human_cmd, std::string choice){
    if (human_cmd == "discard"){
        int idx;
        for (int i=0; i< (int)playerHand.size(); i++){
            if (playerHand[i]==choice){
                idx=i;
                break;
            }
        } 
        playerHand.erase(playerHand.begin()+idx); 
        playerHand.insert(playerHand.begin(),choice);
    }

    else {
        int idx;
        for (int i=0; i< (int)legalList.size(); i++){
            if (legalList[i]==choice){
                idx=i;
                break;
            }
        } 
        legalList.erase(legalList.begin()+idx); 
        legalList.insert(legalList.begin(),choice);

    }
}




void Human::play(Game *g) {
    // if he has no legal plays
    if (legalList.empty()==true){
        //discards the first card in the hand
        std::string c= playerHand[0];
        discardList.emplace_back(c);
        discarded= true;
        //if its the card discarded erase from hand 
        playerHand.erase(playerHand.begin());

    }
    else {
        // if he does have legal cards 
        
        // its not in his hand anymore too
        int idx;
        for (int i=0; i< (int)playerHand.size(); i++){
            if (playerHand[i]==legalList[0]){
                idx=i;
                //std::cout << idx << std::endl;
                break;
            }
        }


        //if its the card played erase from hand 
        playerHand.erase(playerHand.begin()+idx);

        
       
        //notifies the board that hes playing the card
        g->theBoard->notify(*this);
        
        //now the card is used so removes it from legal cards
        legalList.erase(legalList.begin());

       
        //update its legal card   
        played=true;
        
        
     

    }
}


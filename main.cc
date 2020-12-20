#include <iostream>
#include <string>
#include <vector>
#include "game.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include "gameboard.h"
#include "deck.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <stdexcept>

using namespace std;


int main(int argc, char * argv[]) {
     
std::cout << "Welcome the Game of Straights" <<std::endl;
std::cout << "\n";


     //UNINITIALISED
    Player *p1;
    Player *p2;
    Player *p3;
    Player *p4;

    // First we ask what the 4 players want to be ! c or h (INVITING)
    for (int i=0; i<4; i++){
        string cmd;
        std::cout<< "Is player" << " <" << i+1 << ">" << " a human (h) or computer (c)?" << std::endl;
        std::cin >> cmd ; 
                    if ( cmd == "h" && i==0) {
                         p1= new Human{};
                         p1->type="h";
                    } 
                    else if ( cmd == "c" && i==0) {
                         p1= new Computer{};
                         p1->type="c";
                    }   
                    else if ( cmd == "h" && i==1) {
                         p2= new Human{};
                         p2->type="h";
                    } 
                    else if ( cmd == "c" && i==1) {
                         p2= new Computer{};
                         p2->type="c";
                    }
                    else if ( cmd == "h" && i==2) {
                         p3= new Human{};
                         p3->type="h";
                    } 
                    else if ( cmd == "c" && i==2) {
                         p3= new Computer{};
                         p3->type="c";
                    }
                    else if ( cmd == "h" && i==3) {
                         p4= new Human{};
                         p4->type="h";
                    } 
                    else if ( cmd == "c" && i==3) {
                         p4= new Computer{};
                         p4->type="c";
                    }           
                             
    }

    //(CREATING GAME)
    Game *game = new Game{p1,p2,p3,p4};


     //(SETTING UP GAME)
     game->make_game();

    //(SHUFFLING CARD)//////////////////////////////////////////////////////
    //this part is required for shuffling
     unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	
	if ( argc > 1 ) {
		try {
			seed = std::stoi( std::string{ argv[1] } );
		} catch( std::invalid_argument & e ) {
			std::cerr << e.what() << std::endl;
			return 1;
		} catch( std::out_of_range & e ) {
			std::cerr << e.what() << std::endl;
			return -1;
		} // catch
	} // if

	std::default_random_engine rng{seed};
     

     game->shuffle(game->card_deck->cardDeck,rng);

     // to test the deck is shuffled (TESTING PURPOSES)
     //game->card_deck->print_deck();
    ////////////////////////////////////////////////

     // (DEALING OF CARDS)
     game->deal();


    // to test if the cards have been dealt properly (TESTING PURPOSES)
     //game->p1->player_choice_card();
     //game->p2->player_choice_card();
     //game->p3->player_choice_card();
     //game->p4->player_choice_card();


     // (DECIDE ORDER OF THE GAME)
     game->decide_order();
     
     //game->p1->player_choice_card();
     //std::cout << "\n";
     //game->p2->player_choice_card();
     //std::cout << "\n";
     //game->p3->player_choice_card();
     //std::cout << "\n";
     //game->p4->player_choice_card();
     //std::cout << "\n";
     
     // Starting Round
     std::cout <<"\n";
     std::cout << "Round Begins !\n"; 
     std::string human_cmd;
     std::string choice;
      for (int p=0; p<13; p++){
          for (int k=0; k<4; k++){  
                         
               if (game->playerList[k]=="P1"){
                 std::cout << "It's player<1>'s turn to play." << std::endl; 
                 std::cout << "\n"; 
                    if (p1->type=="c"){
                         // to see what he has
                         p1->player_choice_card();
                         std::cout << "\n";
                         // he plays
                         p1->play(game); 
                         //game->theBoard->print_board();
                           
                    }
                    if (p1->type=="h"){
                         p1->player_choice_card();
                         while ( std::getline(std::cin, human_cmd, ' ') && std::getline(std::cin,choice, '\n')){
                              //validates discard or play option
                              if ((human_cmd=="deck"|| human_cmd=="\ndeck"|| human_cmd==" deck") || (human_cmd=="quit" || human_cmd=="\nquit") || p1->valid(human_cmd,choice)==true){break;}
                              else {std::cerr << "Not a valid choice. CHOOSE AGAIN !"<<std::endl;}
                         }
                         if (human_cmd=="deck" || human_cmd=="\ndeck" || human_cmd==" deck"){
                              std::cout << "\n";
                              game->card_deck->print_deck();
                              std::cout << "\n";}
                         else if (human_cmd=="quit" || human_cmd=="\nquit" || human_cmd==" quit"){
                                delete p1; delete p2; delete p3; delete p4; delete game; exit (0);}
                         else { p1->rearrange(human_cmd,choice);
                              p1->play(game);}                        
                    }
                    if (p1->played==true){
                         std::cout << "Player<" << "1"<<"> "<< "played " << game->theBoard->card_added<<"."<<std::endl;
                         std::cout << "\n";
                         }
                    if (p1->discarded==true){
                        std::cout << "Player<" << "1"<<"> "<< "discarded " << p1->discardList.back()<<"."<<std::endl; 
                        std::cout << "\n";
                    }
                    
                    p1->player_choice_card();
                    std::cout << "\n"; 
                   
               }
               else if (game->playerList[k]=="P2"){
                    std::cout << "It's player<2>'s turn to play." << std::endl;  
                    std::cout << "\n"; 
                    if (p2->type=="c"){
                         p2->player_choice_card();
                         std::cout << "\n";
                         p2->play(game);
                    }
                    if (p2->type=="h"){
                         p2->player_choice_card();
                         while ( std::getline(std::cin, human_cmd, ' ') && std::getline(std::cin,choice, '\n')){
                              //validates discard or play option
                              if ((human_cmd=="deck"|| human_cmd=="\ndeck"|| human_cmd==" deck") || (human_cmd=="quit" || human_cmd=="\nquit") || p2->valid(human_cmd,choice)==true){break;}
                              else {std::cerr << "Not a valid choice. CHOOSE AGAIN !"<<std::endl;}
                         }
                         if (human_cmd=="deck" || human_cmd=="\ndeck" || human_cmd==" deck"){
                              std::cout << "\n";
                              game->card_deck->print_deck();
                              std::cout << "\n";}
                         else if (human_cmd=="quit" || human_cmd=="\nquit" || human_cmd==" quit"){
                               delete p1; delete p2; delete p3; delete p4; delete game; exit (0);}
                         else { p2->rearrange(human_cmd,choice);
                              p2->play(game);}    
                    } 
                    if (p2->played==true){
                         std::cout << "Player<" << "2"<<"> "<< "played " << game->theBoard->card_added<<"."<<std::endl;
                         std::cout << "\n";
                    }
                    if (p2->discarded==true){
                        std::cout << "Player<" << "2"<<"> "<< "discarded " << p2->discardList.back()<<"."<<std::endl; 
                        std::cout << "\n";
                    }
                    p2->player_choice_card();
                    std::cout << "\n"; 
               }

               else if (game->playerList[k]=="P3"){
                    std::cout << "It's player<3>'s turn to play." << std::endl; 
                    std::cout << "\n";  
                    if (p3->type=="c"){
                         p3->player_choice_card();
                         std::cout << "\n";
                         p3->play(game);
                    }
                    if (p3->type=="h"){
                         p3->player_choice_card();
                         while ( std::getline(std::cin, human_cmd, ' ') && std::getline(std::cin,choice, '\n')){
                              //validates discard or play option
                              if  ((human_cmd=="deck"|| human_cmd=="\ndeck"|| human_cmd==" deck") || (human_cmd=="quit" || human_cmd=="\nquit") || p3->valid(human_cmd,choice)==true){break;}
                              else {std::cerr << "Not a valid choice. CHOOSE AGAIN !"<<std::endl;}
                         }
                         if (human_cmd=="deck" || human_cmd=="\ndeck" || human_cmd==" deck") { std::cout << "\n";
                              game->card_deck->print_deck();
                              std::cout << "\n";}
                         else if (human_cmd=="quit" || human_cmd=="\nquit" || human_cmd== " quit"){
                               delete p1; delete p2; delete p3; delete p4; delete game; exit (0);}
                         else { p3->rearrange(human_cmd,choice);
                              p3->play(game);}    
                    } 
                    if (p3->played==true){
                         std::cout << "Player<" << "3"<<"> "<< "played " << game->theBoard->card_added<<"."<<std::endl;
                         std::cout << "\n";
                    }
                    if (p3->discarded==true){
                        std::cout << "Player<" << "3"<<"> "<< "discarded " << p3->discardList.back()<<"."<<std::endl; 
                        std::cout << "\n";
                    }
                    p3->player_choice_card();
                    std::cout << "\n"; 
               }
               else if (game->playerList[k]=="P4"){
                    std::cout << "It's player<4>'s turn to play." << std::endl;  
                    std::cout << "\n"; 
                    if (p4->type=="c"){
                         p4->player_choice_card();
                         std::cout << "\n";
                         p4->play(game);
                    }
                    if (p4->type=="h"){
                         p4->player_choice_card();
                         while ( std::getline(std::cin, human_cmd, ' ') && std::getline(std::cin,choice,'\n')){
                              //validates discard or play option
                              if ((human_cmd=="deck"|| human_cmd=="\ndeck"|| human_cmd==" deck") || (human_cmd=="quit" || human_cmd=="\nquit") || p4->valid(human_cmd,choice)==true){break;}
                              else {std::cerr << "Not a valid choice. CHOOSE AGAIN !"<<std::endl;}
                         }
                         if (human_cmd=="deck" || human_cmd=="\ndeck" || human_cmd==" deck"){
                              std::cout << "\n";
                              game->card_deck->print_deck();
                              std::cout << "\n";}
                         else if (human_cmd=="quit" || human_cmd=="\nquit" || human_cmd==" quit"){
                               delete p1; delete p2; delete p3; delete p4; delete game; exit (0);}
                         else { p4->rearrange(human_cmd,choice);
                              p4->play(game);}    
                    } 
                    if (p4->played==true){
                         std::cout << "Player<" <<"4"<<"> "<< "played " << game->theBoard->card_added<<"."<<std::endl;
                         std::cout << "\n";
                    }
                    if (p4->discarded==true){
                        std::cout << "Player<" << "4"<<"> "<< "discarded " << p4->discardList.back()<<"."<<std::endl; 
                        std::cout << "\n";
                    }
                    p4->player_choice_card();
                    std::cout << "\n"; 
               } 
          }
     }
     

  // DECIDES WINNER AND DISPLAYS IT 
     game->decide_winner();

     // displaying score
     std::cout << "\n";
     std::cout << "Scores" << std::endl; 
     std::cout << "Player<1> scored "<< p1->score() << std::endl;
     std::cout << "Player<2> scored "<< p2->score() << std::endl;
     std::cout << "Player<3> scored "<< p3->score() << std::endl;
     std::cout << "Player<4> scored "<< p4->score() << std::endl;
 
  // Special Thanks
  
     std::cout << "\n";
     std::cout << "Thanks for Playing :)" <<std::endl;
     std::cout << "\n";




    //(DELETE GAME AND PLAYERS);
    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete game;
    
}

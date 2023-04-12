#include <iostream>
#include <cstdlib>
#include "game.hpp"
using namespace ariel;

void Game::splitCards(std::vector<Card>& cardsArray){
    std::vector<Card> firstPlayerCards;
    std::vector<Card> secondPlayerCards;
    for(int count=52; count > 0; count--){
        int currentPlace = rand() % count;
        if(count % 2 == 0){
            secondPlayerCards.push_back(cardsArray.at((size_t) currentPlace));
        } else{
            firstPlayerCards.push_back(cardsArray.at((size_t) currentPlace));
        }
        cardsArray.erase(cardsArray.begin() + currentPlace);
    }
    this->firstPlayer.playerCards = firstPlayerCards;
    this->secondPlayer.playerCards = secondPlayerCards;
}

void Game::buildCards(){
    std::vector<Card> cardsArray;
    for(int rank = 1; rank <= 13; rank++){
        Card spadesCard(rank, "Spades");
        Card clubsCard(rank, "Clubs");
        Card heartsCard(rank, "Hearts");
        Card diamondsCard(rank, "Diamonds");
        cardsArray.push_back(spadesCard);
        cardsArray.push_back(clubsCard);
        cardsArray.push_back(heartsCard);
        cardsArray.push_back(diamondsCard);
    }
    splitCards(cardsArray);
}


void Game::playTurn(){

    if(this->firstPlayer.isPlaying){
        throw std::invalid_argument("The first player is already in game");
    } else{
        this->firstPlayer.isPlaying = true;
    }

    if(this->secondPlayer.isPlaying){
        throw std::invalid_argument("The second player is already in game");
    } else{
        this->secondPlayer.isPlaying = true;
    }

    if(this->firstPlayer.stacksize() == 0){
        throw std::runtime_error("Game already finished");
    }

    Card firstCard = this->firstPlayer.firstCard();
    Card secondCard = this->secondPlayer.firstCard();
    int playerWon = firstCard.compareCards(secondCard);

    int rounds = 1;
    bool isFinished = false;

    std::string gameLog = firstPlayer.name + " delt card " + firstCard.toString() + ", ";
    gameLog += secondPlayer.name + " delt card " + secondCard.toString() + ".";

    while(!isFinished && playerWon == 0){
        gameLog += " Draw. ";
        this->countDraw += 1;
        if(this->firstPlayer.stacksize() > 0){
            firstCard = this->firstPlayer.firstCard();
            secondCard = this->secondPlayer.firstCard();
            if(this->firstPlayer.stacksize() > 0){
                firstCard = this->firstPlayer.firstCard();
                secondCard = this->secondPlayer.firstCard();
            }
        } else{
            isFinished = true;
            gameLog += "\n";
            break;
        }
        if(!isFinished){
            gameLog += firstPlayer.name + " delt card " + firstCard.toString() + ", ";
            gameLog += secondPlayer.name + " delt card " + secondCard.toString() + ".";
            playerWon = firstCard.compareCards(secondCard);
            rounds += 1;
        }
    }
    int cardsTook = 4 * rounds - 2;
    
    if (playerWon == 1){
        gameLog += " " + firstPlayer.name + " win" + "\n";
        firstPlayer.cardsTook += cardsTook;
        this->countFirstPlayer += 1;
    } else if(playerWon == -1){
        gameLog += " " + secondPlayer.name + " win" + "\n";
        secondPlayer.cardsTook += cardsTook;
        this->countSecondPlayer += 1;
    } else{
        firstPlayer.cardsTook += (cardsTook/2);
        secondPlayer.cardsTook += (cardsTook/2);
        this->countDraw += 1;
    }

    this->log.push_back(gameLog);
};

void Game::playAll(){
    while(this->firstPlayer.stacksize() > 0){
        playTurn();
    }
};

void Game::printLog(){
    size_t index = 0;
    while(this->log.size() > index){
        std::cout << log.at(index) << std::endl;
        index += 1;
    }
};

void Game::printLastTurn(){
    std::cout << log.back() << std::endl;
};

void Game::printStats(){
    std::cout << "first player: " + firstPlayer.name + " win rate: " + std::to_string((((double) countFirstPlayer / (this->log.size() + 1)) * 100)) + ", Cards Took: " + std::to_string(firstPlayer.cardesTaken()) << std::endl;
    std::cout << "second player: " + secondPlayer.name + " win rate: " + std::to_string(((double) countSecondPlayer / (this->log.size() + 1)) * 100) + ", Cards Took: " + std::to_string(secondPlayer.cardesTaken()) << std::endl;
    std::cout << "draw rate: " + std::to_string((((double) countDraw / (this->log.size() + 1)) * 100)) + ", draw times: " + std::to_string(countDraw) << std::endl;
};

void Game::printWiner(){
    if (this->firstPlayer.stacksize() != 0){
        std::cout << "Game have not ended" << std::endl;
    }
    if(this->firstPlayer.cardesTaken() == this->secondPlayer.cardesTaken()){
        std::cout << "No one won the game, tie." << std::endl;
    } else if(this->firstPlayer.cardesTaken() > this->secondPlayer.cardesTaken()){
        std::cout << this->firstPlayer.name + " won the game." << std::endl;
    } else{
        std::cout << this->secondPlayer.name + " won the game." << std::endl;
    }
};
#include <iostream>
#include "player.hpp"

Card &Player::firstCard(){
    Card &cardToReturn = playerCards.back();
    playerCards.pop_back();
    this->isPlaying = false;
    return cardToReturn;
}

int Player::stacksize()
{
    return this->playerCards.size();
}

int Player::cardesTaken()
{
    return this->cardsTook;
}

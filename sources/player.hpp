#pragma once

#include <iostream>
#include <vector>
#include "card.hpp"

class Player{
    public:
        std::string name;
        int cardsTook;
        bool isPlaying;
        std::vector<Card> playerCards;
    
        Player(std::string name): name(std::move(name)), cardsTook(0), isPlaying(false){};
        Card &firstCard();
        int stacksize();
        int cardesTaken();
};
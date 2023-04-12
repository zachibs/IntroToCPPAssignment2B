#pragma once
#include <iostream>


class Card{

    public:
        int rank;
        std::string suit;

        std::string toString();
        int compareCards(Card secondCard);
        Card(int rank, std::string suit): rank(rank), suit(std::move(suit)){}
};
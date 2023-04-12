#pragma once
#include <iostream>
#include <vector>
#include "player.hpp"

namespace ariel{

    class Game{

    public:

        Player &firstPlayer;
        Player &secondPlayer;
        int countDraw;
        int countFirstPlayer;
        int countSecondPlayer;
        std::vector<std::string> log;

        Game(Player &player1, Player &player2): firstPlayer(player1), secondPlayer(player2), countDraw(0), countFirstPlayer(0), countSecondPlayer(0){buildCards();};
        void splitCards(std::vector<Card>& cardsArray);
        void buildCards();

        void playTurn();
        void playAll();
        void printLog();
        void printLastTurn();
        void printStats();
        void printWiner();
    };
};
#include "card.hpp"

std::string Card::toString(){
    std::string String = "";
    if (this->rank == 1){
        String = "Ace";
    } else if(this->rank == 11){
        String = "Jack";
    } else if(this->rank == 12){
        String = "Queen";
    } else if(this->rank == 13){
        String = "King";
    } else{
        String = std::to_string(this->rank);
    }
    return String + " of " + this->suit;
}

int Card::compareCards(Card secondCard){
    if(this->rank == secondCard.rank){
        return 0;
    } else if(secondCard.rank == 1 || this->rank == 1){
        if (this->rank == 2){
            return 1;
        } else if(secondCard.rank == 2){
            return -1;
        } else if(this->rank == 1){
            return 1;
        }
        return -1;
    } else if(secondCard.rank > this->rank){
        return -1;
    }
    return 1;
}
#ifndef HAND_H
#define HAND_H

#include <vector>
#include "Card.h"

//Tinh diem cua bai tren tay
class Hand {
public:
    vector<Card> cards;
    
    void addCard(Card c);
    void clear();
    int getScore() const;
    bool isXiBang() const;
    bool isXiDach() const;
    bool isNguLinh() const;
    bool isBust() const;
};

#endif
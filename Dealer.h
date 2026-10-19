#ifndef DEALER_H
#define DEALER_H

#include "Hand.h"

// Nhà cái (Dealer)
class Dealer {
private:
    Hand hand;
    double balance;
public:
    Dealer(double b);
    
    Hand& getHand();
    void resetHand();
    double getBalance() const;
    void updateBalance(double amount);
    
    bool makeDecision();
};

#endif
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Hand.h"

using namespace std;

// Nguoi choi
class Player {
protected:
    string name;
    double balance;
    Hand hand;
public:
    Player(string n, double initialBalance);
    virtual ~Player();
    
    string getName() const;
    double getBalance() const;
    void updateBalance(double amount);
    
    Hand& getHand();
    void resetHand();
    
    virtual bool makeDecision() = 0;
};

// Loại 1: Người chơi Nhát gan / An toàn (FunkyPlayer)
class FunkyPlayer : public Player {
public:
    FunkyPlayer(string n, double b);
    bool makeDecision() override;
};

// Loại 2: Người chơi Tối ưu (OptimalPlayer)
class OptimalPlayer : public Player {
public:
    OptimalPlayer(string n, double b);
    bool makeDecision() override;
};

// Loại 3: Người chơi Máu liều (RecklessPlayer)
class RecklessPlayer : public Player {
public:
    bool checkBetter28;
    RecklessPlayer(string n, double b);
    bool makeDecision() override;
};

#endif
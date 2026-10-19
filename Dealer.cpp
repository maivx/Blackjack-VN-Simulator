#include "Dealer.h"

Dealer::Dealer(double b) : balance(b) {}

Hand& Dealer::getHand() { return hand; }
void Dealer::resetHand() { hand.clear(); }
double Dealer::getBalance() const { return balance; }
void Dealer::updateBalance(double amount) { balance += amount; }

bool Dealer::makeDecision() {
    int score = hand.getScore();
    int count = hand.cards.size();
    if (count >= 5) return false;
    if (score >= 15) return false; // Nhà cái cần từ 15 điểm trở lên để đứng bài
    return true;
}
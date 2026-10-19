#include "Player.h"

Player::Player(string n, double initialBalance) : name(n), balance(initialBalance) {}
Player::~Player() {}

string Player::getName() const { return name; }
double Player::getBalance() const { return balance; }
void Player::updateBalance(double amount) { balance += amount; }

Hand& Player::getHand() { return hand; }
void Player::resetHand() { hand.clear(); }

// Loại 1: Người chơi Nhát gan / An toàn (FunkyPlayer)
FunkyPlayer::FunkyPlayer(string n, double b) : Player(n, b) {}
bool FunkyPlayer::makeDecision() {
    int score = hand.getScore();
    int count = hand.cards.size();
    if (count >= 5) return false;
    if (score >= 16) return false; // Dừng ngay khi đạt mức 16 điểm
    return true; 
}

// Loại 2: Người chơi Tối ưu (OptimalPlayer)
OptimalPlayer::OptimalPlayer(string n, double b) : Player(n, b) {}
bool OptimalPlayer::makeDecision() {
    int score = hand.getScore();
    int count = hand.cards.size();
    if (count >= 5) return false;
    if (score >= 17) return false; // Dừng khi từ 17 điểm trở lên
    return true;
}

// Loại 3: Người chơi Máu liều (RecklessPlayer)
RecklessPlayer::RecklessPlayer(string n, double b) : Player(n, b), checkBetter28(false) {}
bool RecklessPlayer::makeDecision() {
    int score = hand.getScore();
    int count = hand.cards.size();
    if (count >= 5) return false;
    
    // Trường hợp đặc biệt: Đang có đúng 18 điểm và cầm 4 lá, tiếp tục rút lá thứ 5
    if (score == 18 && count == 4) {
        return true;
    }
    
    if (score >= 18) return false;
    return true;
}
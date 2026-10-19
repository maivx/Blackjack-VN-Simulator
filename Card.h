#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

using namespace std;

// Cấu trúc lá bài
struct Card {
    int value; // 1 đến 13 (1: A, 11: J, 12: Q, 13: K)
    string suit; // "Bích", "Chuồn", "Rô", "Cơ"
    
    int getGameValue() const;
};

// Bộ bài
class Deck {
private:
    vector<Card> cards;
public:
    Deck();
    void reset();
    void shuffle();
    Card draw();
};

#endif
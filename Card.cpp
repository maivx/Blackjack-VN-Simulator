#include "Card.h"
#include <algorithm>
#include <cstdlib>
#include <random> 

int Card::getGameValue() const {
    if (value == 1) return 11; // Mặc định Át là 11
    if (value >= 11 && value <= 13) return 10;
    return value;
}

Deck::Deck() {
    reset();
}

void Deck::reset() {
    cards.clear();
    string suits[4] = {"Bích", "Chuồn", "Rô", "Cơ"};
    for (const string& s : suits) {
        for (int v = 1; v <= 13; ++v) {
            cards.push_back({v, s});
        }
    }
    shuffle();
}

void Deck::shuffle() {
    auto rd = std::random_device {};
    auto rng = std::default_random_engine { rd() };
    std::shuffle(cards.begin(), cards.end(), rng);
}

Card Deck::draw() {
    if (cards.empty()) {
        reset();
    }
    Card c = cards.back();
    cards.pop_back();
    return c;
}
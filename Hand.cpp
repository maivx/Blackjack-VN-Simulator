#include "Hand.h"

void Hand::addCard(Card c) {
    cards.push_back(c);
}

void Hand::clear() {
    cards.clear();
}

int Hand::getScore() const {
    int sum = 0;
    int aceCount = 0;
    
    for (const auto& c : cards) {
        if (c.value == 1) {
            aceCount++;
            sum += 11; // Tạm tính Át là 11
        } else if (c.value >= 11 && c.value <= 13) {
            sum += 10;
        } else {
            sum += c.value;
        }
    }
    
    int count = cards.size();
    
    // Xử lý giá trị lá Át theo luật đề bài
    if (count > 3) {
        sum -= aceCount * 10; 
    }
    
    // Cơ chế tự động giảm điểm để cứu khỏi Quắc (Bust)
    while (sum > 21 && aceCount > 0) {
        sum -= 10; 
        aceCount--;
    }
    
    // Quy tắc đặc biệt: đề phòng khi cầm 3 lá mà tổng điểm bị đẩy lên 22 ( vì lá át có thể tính là 10 hoặc 11)
    if (sum == 22 && count == 3) {
        sum = 21; 
    }
    
    return sum;
}

// Chỉ cần 2 lá Át bất kỳ là Xì Bàng
bool Hand::isXiBang() const {
    return (cards.size() == 2 && cards[0].value == 1 && cards[1].value == 1);
}

bool Hand::isXiDach() const {
    if (cards.size() == 2) {
        bool hasAce = (cards[0].value == 1 || cards[1].value == 1);
        bool hasTenOrFace = (cards[0].getGameValue() == 10 || cards[1].getGameValue() == 10);
        return hasAce && hasTenOrFace && !isXiBang();
    }
    return false;
}

bool Hand::isNguLinh() const {
    return cards.size() == 5 && getScore() <= 21;
}

bool Hand::isBust() const {
    return getScore() > 21;
}
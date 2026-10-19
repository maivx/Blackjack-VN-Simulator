#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include "Card.h"
#include "Hand.h"
#include "Player.h"
#include "Dealer.h"

using namespace std;

int main() {
    srand(time(0));
    
    int TOTAL_GAMES = 0;
    cout << "========================================================\n";
    cout << "        CHUONG TRINH MO PHONG BLACKJACK OOP C++\n";
    cout << "========================================================\n";
    cout << "Nhap so luong van choi muon mo phong: ";
    cin >> TOTAL_GAMES;
    
    if (TOTAL_GAMES <= 0) {
        cout << "So luong van choi khong hop le! Dat mac dinh la 100000 van.\n";
        TOTAL_GAMES = 100000;
    }

    double initialMoney = 10000.0;
    
    FunkyPlayer p1("Funky (16d)", initialMoney);
    OptimalPlayer p2("Optimal (17d)", initialMoney);
    RecklessPlayer p3("Reckless (18d+)", initialMoney);
    Dealer dealer(50000.0);
    Deck deck;
    
    long long dealerDecisionCount[21] = {0};
    long long dealerWinAtScore[21] = {0};

    // --- BỔ SUNG: Biến đếm số lần Quắc (Bust) của từng người chơi ---
    long long p1BustCount = 0;
    long long p2BustCount = 0;
    long long p3BustCount = 0;
    
    vector<double> historyDealer;
    vector<double> historyP1;
    vector<double> historyP2;
    vector<double> historyP3;
    
    double betAmount = 100.0;
    
    cout << "\nDang chay mo phong " << TOTAL_GAMES << " van choi, vui lòng đợi trong giay lát...\n";

    for (int game = 1; game <= TOTAL_GAMES; ++game) {
        deck.reset();
        p1.resetHand();
        p2.resetHand();
        p3.resetHand();
        dealer.resetHand();
        
        vector<Player*> players = {&p1, &p2, &p3};
        for (auto p : players) {
            p->getHand().addCard(deck.draw());
            p->getHand().addCard(deck.draw());
        }
        dealer.getHand().addCard(deck.draw());
        dealer.getHand().addCard(deck.draw());
        
        for (auto p : players) {
            while (p->makeDecision()) {
                p->getHand().addCard(deck.draw());
                if (auto* reckless = dynamic_cast<RecklessPlayer*>(p)) {
                    if (reckless->getHand().getScore() >= 28) {
                        reckless->checkBetter28 = true;
                    }
                }
            }
        }

        // --- BỔ SUNG: Kiểm tra và ghi nhận số lần Quắc ngay sau khi rút bài xong ---
        if (p1.getHand().isBust()) p1BustCount++;
        if (p2.getHand().isBust()) p2BustCount++;
        if (p3.getHand().isBust()) p3BustCount++;
        
        while (dealer.makeDecision()) {
            dealer.getHand().addCard(deck.draw());
        }
        
        int dealerScore = dealer.getHand().getScore();
        bool dealerBust = dealer.getHand().isBust();
        
        if (!dealerBust && dealerScore >= 16 && dealerScore <= 20) {
            dealerDecisionCount[dealerScore]++;
        }
        
        for (auto p : players) {
            int pScore = p->getHand().getScore();
            bool pBust = p->getHand().isBust();
            bool pXiBang = p->getHand().isXiBang();
            bool pXiDach = p->getHand().isXiDach();
            bool pNguLinh = p->getHand().isNguLinh();
            
            bool dealerXiBang = dealer.getHand().isXiBang();
            bool dealerXiDach = dealer.getHand().isXiDach();
            bool dealerNguLinh = dealer.getHand().isNguLinh();
            
            double payout = 0;
            bool playerWon = false;
            
            if (pXiBang) {
                if (dealerXiBang) payout = 0;
                else { playerWon = true; payout = betAmount; }
            } else if (dealerXiBang) {
                playerWon = false; payout = -betAmount;
            } else if (pXiDach) {
                if (dealerXiDach || dealerXiBang) payout = 0;
                else { playerWon = true; payout = betAmount; }
            } else if (dealerXiDach) {
                playerWon = false; payout = -betAmount;
            } else if (pNguLinh) {
                if (dealerXiBang || dealerXiDach || dealerNguLinh) {
                    playerWon = false; payout = -betAmount;
                } else { playerWon = true; payout = betAmount; }
            } else if (dealerNguLinh) {
                playerWon = false; payout = -betAmount;
            } else {
                if (pBust) {
                    playerWon = false; payout = -betAmount;
                } else if (dealerBust) {
                    playerWon = true; payout = betAmount;
                } else {
                    if (pScore > dealerScore) {
                        playerWon = true; payout = betAmount;
                    } else if (pScore < dealerScore) {
                        playerWon = false; payout = -betAmount;
                    } else {
                        payout = 0;
                    }
                }
            }
            
            if (playerWon) {
                p->updateBalance(payout);
                dealer.updateBalance(-payout);
            } else if (payout < 0) {
                p->updateBalance(payout);
                dealer.updateBalance(-payout);
                if (!dealerBust && dealerScore >= 16 && dealerScore <= 20) {
                    dealerWinAtScore[dealerScore]++;
                }
            }
        }
        
        int step = max(1, TOTAL_GAMES / 1000);
        if (game % step == 0 || game == TOTAL_GAMES) {
            historyDealer.push_back(dealer.getBalance());
            historyP1.push_back(p1.getBalance());
            historyP2.push_back(p2.getBalance());
            historyP3.push_back(p3.getBalance());
        }
    }
    
    // In bảng kết toán tài sản
    cout << "\n========================================================\n";
    cout << "         BANG KET TOAN TAI SAN SAU " << TOTAL_GAMES << " VAN CHOI\n";
    cout << "========================================================\n";
    cout << left << setw(25) << "Thanh phan" 
         << setw(15) << "Von ban dau" 
         << setw(15) << "Von cuoi cung" 
         << setw(15) << "Loi nhuan" << endl;
    cout << "--------------------------------------------------------\n";
    
    auto printRow = [&](string name, double start, double current) {
        double profit = current - start;
        cout << left << setw(25) << name 
             << setw(15) << start 
             << setw(15) << current 
             << setw(15) << (profit >= 0 ? "+" + to_string(profit) : to_string(profit)) << endl;
    };
    
    printRow(p1.getName(), initialMoney, p1.getBalance());
    printRow(p2.getName(), initialMoney, p2.getBalance());
    printRow(p3.getName(), initialMoney, p3.getBalance());
    printRow("Nha Cai (Dealer)", 50000.0, dealer.getBalance());
    cout << "========================================================\n\n";

    // --- BỔ SUNG: In bảng thống kê Tỷ lệ Quắc (Bust Rate) cho báo cáo ---
    cout << "========================================================\n";
    cout << "             THONG KE TY LE QUAC (BUST RATE)            \n";
    cout << "========================================================\n";
    cout << left << setw(25) << "Chien luoc" 
         << setw(15) << "So lan Quac" 
         << setw(15) << "Ty le Quac (%)" << endl;
    cout << "--------------------------------------------------------\n";
    
    auto printBustRate = [&](string name, long long busts) {
        double rate = ((double)busts / TOTAL_GAMES) * 100.0;
        cout << left << setw(25) << name 
             << setw(15) << busts 
             << setw(15) << fixed << setprecision(2) << rate << "%" << endl;
    };

    printBustRate(p1.getName(), p1BustCount);
    printBustRate(p2.getName(), p2BustCount);
    printBustRate(p3.getName(), p3BustCount);
    cout << "========================================================\n\n";
    
    // In tỷ lệ thắng của nhà cái từ 16 đến 20 điểm
    cout << "========================================================\n";
    cout << "   TY LE THANG CUA NHA CAI KHI DUNG O MUC DIEM TU 16 - 20\n";
    cout << "========================================================\n";
    cout << left << setw(10) << "Diem" 
         << setw(20) << "So lan dung" 
         << setw(20) << "So lan thang" 
         << setw(15) << "Ty le thang (%)" << endl;
    cout << "--------------------------------------------------------\n";
    for (int d = 16; d <= 20; ++d) {
        double winRate = (dealerDecisionCount[d] > 0) ? ((double)dealerWinAtScore[d] / dealerDecisionCount[d]) * 100.0 : 0.0;
        cout << left << setw(10) << d 
             << setw(20) << dealerDecisionCount[d] 
             << setw(20) << dealerWinAtScore[d] 
             << setw(15) << fixed << setprecision(2) << winRate << "%" << endl;
    }
    cout << "========================================================\n\n";
    
    // Tạo file bieu_do.py (Đã sửa lỗi len() ở dòng steps)
    ofstream pyFile("bieu_do.py");
    pyFile << "import matplotlib.pyplot as plt\n\n";
    pyFile << "total_games = " << TOTAL_GAMES << "\n";
    pyFile << "steps = " << historyDealer.size() << "\n"; // Đã sửa lỗi type int has no len()
    pyFile << "games = [int(i * (total_games / (steps - 1) if steps > 1 else 1)) for i in range(steps)]\n";
    
    pyFile << "dealer_bal = " << "[\n";
    for (double val : historyDealer) pyFile << "    " << val << ",\n";
    pyFile << "]\n\n";
    
    pyFile << "p1_bal = " << "[\n";
    for (double val : historyP1) pyFile << "    " << val << ",\n";
    pyFile << "]\n\n";
    
    pyFile << "p2_bal = " << "[\n";
    for (double val : historyP2) pyFile << "    " << val << ",\n";
    pyFile << "]\n\n";
    
    pyFile << "p3_bal = " << "[\n";
    for (double val : historyP3) pyFile << "    " << val << ",\n";
    pyFile << "]\n\n";
    
    pyFile << "plt.figure(figsize=(12, 6))\n";
    pyFile << "plt.plot(games, dealer_bal, label='Nha Cai (Dealer)', color='black', linewidth=2)\n";
    pyFile << "plt.plot(games, p1_bal, label='FunkyPlayer (16d)', color='blue', linestyle='--')\n";
    pyFile << "plt.plot(games, p2_bal, label='OptimalPlayer (17d)', color='green')\n";
    pyFile << "plt.plot(games, p3_bal, label='RecklessPlayer (18d+)', color='red', linestyle=':')\n";
    pyFile << "plt.title('Bieu do bien dong tai san qua ' + str(total_games) + ' van choi Blackjack')\n";
    pyFile << "plt.xlabel('So van choi')\n";
    pyFile << "plt.ylabel('So tien (VND / Diem)')\n";
    pyFile << "plt.legend()\n";
    pyFile << "plt.grid(True)\n";
    pyFile << "plt.show()\n";
    pyFile.close();
    
    cout << "KET THUC CHUONG TRINH\n";
    return 0;
}
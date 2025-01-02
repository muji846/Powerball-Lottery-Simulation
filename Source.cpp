#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

class Lottery {
private:
    vector<int> playerNumbers;
    vector<int> computerNumbers;
    int jackpot;
    int totalMatches;
    int totalWinnings;
    int gamesPlayed;

    // Generate unique random numbers for the computer
    void generateComputerNumbers() {
        computerNumbers.clear();
        while (computerNumbers.size() < 5) {
            int num = rand() % 69 + 1;
            if (find(computerNumbers.begin(), computerNumbers.end(), num) == computerNumbers.end()) {
                computerNumbers.push_back(num);
            }
        }
    }

    // Prompt player to input unique numbers
    void getPlayerNumbers() {
        playerNumbers.clear();
        cout << "Enter 5 unique numbers between 1 and 69: ";
        while (playerNumbers.size() < 5) {
            int num;
            cin >> num;
            if (num < 1 || num > 69) {
                cout << "Number out of range. Try again: ";
            }
            else if (find(playerNumbers.begin(), playerNumbers.end(), num) != playerNumbers.end()) {
                cout << "Duplicate number. Try again: ";
            }
            else {
                playerNumbers.push_back(num);
            }
        }
    }

    // Check for matches and assign winnings
    int checkMatches() {
        int matches = 0;
        for (int num : playerNumbers) {
            if (find(computerNumbers.begin(), computerNumbers.end(), num) != computerNumbers.end()) {
                matches++;
            }
        }
        return matches;
    }

public:
    Lottery() : jackpot(10000000), totalMatches(0), totalWinnings(0), gamesPlayed(0) {
        srand(time(0));
    }

    void playGame() {
        generateComputerNumbers();
        getPlayerNumbers();

        int matches = checkMatches();
        gamesPlayed++;
        totalMatches += matches;

        if (matches == 5) {
            cout << "Jackpot! You won $" << jackpot << "!" << endl;
            totalWinnings += jackpot;
            jackpot = 10000000; // Reset jackpot
        }
        else {
            int winnings = matches * 100;
            cout << "You matched " << matches << " number(s) and won $" << winnings << "." << endl;
            totalWinnings += winnings;
            jackpot += 2000000; // Increase jackpot
        }

        printCurrentResults();
    }

    void printCurrentResults() {
        cout << "Player Numbers: ";
        for (int num : playerNumbers) {
            cout << num << " ";
        }
        cout << endl;

        cout << "Computer Numbers: ";
        for (int num : computerNumbers) {
            cout << num << " ";
        }
        cout << endl;
    }

    void printFinalResults() {
        cout << "\nFinal Results:" << endl;
        cout << "Total games played: " << gamesPlayed << endl;
        cout << "Total numbers matched: " << totalMatches << endl;
        cout << "Total winnings: $" << totalWinnings << endl;
        cout << "Final jackpot value: $" << jackpot << endl;
    }
};

int main() {
    Lottery lottery;
    char choice;

    do {
        lottery.playGame();
        cout << "Do you want to play again? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    lottery.printFinalResults();

    return 0;
}

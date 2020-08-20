#include "Greedy.h"
#include "Head.h"
#include "Card.h"

int Greedy::computeNextMove(std::unique_ptr<Card>& card, std::vector<std::unique_ptr<Head>>& heads) const {
    int cardValue = card->getValue();
    int best = 100;
    int bestMove = heads[0]->getIdentifier();

    // Check if there exists any valid move 
    for (size_t i = 0; i < heads.size(); ++i) {
        int value = heads[i]->getTop()->getValue();

        // There exists a valid move
        if (value >= cardValue || value == 1) {
            // Choose move that minimizes difference between card and head value
            if (value - cardValue < best) {
                best = value - cardValue;
                bestMove = heads[i]->getIdentifier();
            }
        }
    }

    return bestMove;
}

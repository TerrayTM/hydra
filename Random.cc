#include "Random.h"
#include "Head.h"
#include "Card.h"

int Random::computeNextMove(std::unique_ptr<Card>& card, std::vector<std::unique_ptr<Head>>& heads) const {
    int cardValue = card->getValue();
    std::vector<int> validMoves{};

    // Check if there exists any valid move 
    for (size_t i = 0; i < heads.size(); ++i) {
        int value = heads[i]->getTop()->getValue();

        // There exists a valid move, add it to the move set
        if (value >= cardValue || value == 1) {
            validMoves.emplace_back(heads[i]->getIdentifier());
        }
    }

    if (validMoves.size() > 0) {
        // If there are valid moves then we randomly select one
        return validMoves[rand() % validMoves.size()];
    }

    // Else we cut a head
    return heads[0]->getIdentifier();
}

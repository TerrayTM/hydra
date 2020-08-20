#include "Vanilla.h"
#include "Player.h"
#include "Card.h"
#include "Head.h"

// Constructor
Vanilla::Vanilla() : Game{} {}

// Override get move state
MoveState Vanilla::getMoveState(int move) const {
    // Player may access reserve if there is more than 1 head
    if (move == 0 && heads.size() == 1) {
        return MoveState::invalid;
    } else if (move == 0) {
        return MoveState::valid;
    }

    // Store card and head value
    int cardValue = players[currentPlayer]->peekCard()->getValue();
    int headValue = heads[move - heads.size()]->getTop()->getValue();

    // Valid move if card value is strictly less than head value
    if (cardValue < headValue) {
        return MoveState::valid;
    }

    // If values are the same then move is valid but ends player's turn immediately
    if (cardValue == headValue) {
        return MoveState::stop;
    }

    // If the head card is an ace then we let any card to be placed on top
    if (headValue == 1) {
        return MoveState::valid;
    }

    // If the move is the first head and the card is not a joker
    if (move == heads[0]->getIdentifier() && players[currentPlayer]->peekCard()->getSuit() != CardSuit::joker) {
        // Check if there exists any valid move 
        for (size_t i = 1; i < heads.size(); ++i) {
            int value = heads[i]->getTop()->getValue();

            // There exists a valid move, then current move is not a cut directive
            if (value >= cardValue || value == 1) {
                return MoveState::invalid;
            }
        }

        // There does not exist valid moves, so current move is a cut
        return MoveState::cut;
    }

    return MoveState::invalid;
}

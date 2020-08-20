#include "Sandbox.h"
#include "Player.h"
#include "Card.h"
#include "Head.h"
#include "Regular.h"
#include "Joker.h"

// Constructor
Sandbox::Sandbox() : Game{} {}

// Override get move state
// Sand box mode has same rules as vanilla
MoveState Sandbox::getMoveState(int move) const {
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

// Override create head
void Sandbox::createHead(std::istream& in, std::ostream& out) {
    heads.emplace_back(std::make_unique<Head>(generateCard(in, out), 1));
    players[currentPlayer]->popCard();
    currentPlayer = (currentPlayer + 1) % players.size();
}

// Generate card based on user input
std::unique_ptr<Card> Sandbox::generateCard(std::istream& in, std::ostream& out) const {
    int number = -1;

    do {
        out << "Card value?" << std::endl;
        
        // Get card value
        std::string input;
        in >> input;

        // Get the value inputted
        if (input == "Joker") {
            return std::make_unique<Joker>();
        } else if (input == "A") {
            number = 1;
        } else if (input == "J") {
            number = 11;
        } else if (input == "Q") {
            number = 12;
        } else if (input == "K") {
            number = 13;
        } else {
            try {
                // Attempt to get integer of input
                number = std::stoi(input);
            } catch (...) {
                // Input is not a valid number
                number = -1;
            }

            // Invalid card value
            if (number < 2 || number > 10) {
                number = -1;
            }
        }
    } while (number == -1 && !in.eof());

    bool isValid;
    CardSuit suit = CardSuit::hearts;

    do {
        isValid = true;

        // Get card suit
        out << "Suit?" << std::endl;

        std::string input;
        in >> input; 

        // Convert input to suit
        if (input == "H") {
            suit = CardSuit::hearts;
        } else if (input == "D") {
            suit = CardSuit::diamonds;
        } else if (input == "S") {
            suit = CardSuit::spades;
        } else if (input == "C") {
            suit = CardSuit::clubs;
        } else {
            isValid = false;
        }
    } while (!isValid && !in.eof());

    return std::make_unique<Regular>(suit, number);
}

// Override plant new heads to specify any seed card
void Sandbox::plantNewHeads(std::pair<std::unique_ptr<Card>, std::unique_ptr<Card>>&& seeds, int starting, std::istream& in, std::ostream& out) {
    heads.emplace_back(std::make_unique<Head>(generateCard(in, out), starting + 1));
    heads.emplace_back(std::make_unique<Head>(generateCard(in, out), starting + 2));
}

// Override request move event handler
void Sandbox::requestMoveEvent(std::istream& in, std::ostream& out) {
    players[currentPlayer]->popCard();
    players[currentPlayer]->pushCard(generateCard(in, out));
}

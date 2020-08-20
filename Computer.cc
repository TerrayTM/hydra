#include "Computer.h"
#include "Card.h"
#include "Joker.h"

// Constructor
Computer::Computer(int id, std::unique_ptr<Strategy>&& strategy) : Player{id}, strategy{std::move(strategy)} {}

// Override base get next move
int Computer::getNextMove(std::istream& in, std::ostream& out, std::vector<std::unique_ptr<Head>>& heads) {
    // For sake of simplicity treat joker card as AJ
    if (peekCard()->getSuit() == CardSuit::joker) {
        popCard();
        pushCard(std::make_unique<Joker>(1));
    }

    // Compute a move
    int move = strategy->computeNextMove(peekCard(), heads);

    // Output the move
    out << move << std::endl;

    return move;
}

// Override base generate string
std::string Computer::generateString() const {
    return "CPU Player " + std::to_string(id) + ": " + std::to_string(deck.size() + discard.size()) + " (" + std::to_string(deck.size()) + " draw, " + std::to_string(discard.size()) + " discard)";
}

// Override base generate active string
std::string Computer::generateActiveString(int remaining) const {
    return generateString() + " + 1 in hand, " + std::to_string(remaining) + " remaining, " + (reserve != nullptr ? "1" : "0") + " in reserve";
}

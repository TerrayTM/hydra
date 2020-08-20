#include "Human.h"

// Constructor
Human::Human(int id) : Player{id} {}

// Override base get next move
int Human::getNextMove(std::istream& in, std::ostream& out, std::vector<std::unique_ptr<Head>>& heads) {
    // Get input
    int move;

    if (!(in >> move)) {
        // Input invalid
        return -1;
    }
    
    // Return the move
    return move;
}
    
// Override base generate string
std::string Human::generateString() const {
    return "Player " + std::to_string(id) + ": " + std::to_string(deck.size() + discard.size()) + " (" + std::to_string(deck.size()) + " draw, " + std::to_string(discard.size()) + " discard)";
}

// Override base generate active string
std::string Human::generateActiveString(int remaining) const {
    return generateString() + " + 1 in hand, " + std::to_string(remaining) + " remaining, " + (reserve != nullptr ? "1" : "0") + " in reserve";
}

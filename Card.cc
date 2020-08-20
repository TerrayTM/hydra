#include "Card.h"

// Constructor
Card::Card(CardSuit suit, int value) : suit{suit}, value{value} {}

// Card value getter
int Card::getValue() const {
    return value;
}

// Card suit getter
CardSuit Card::getSuit() const {
    return suit;
}

// Get the string representation of the card
std::string Card::toString() const {
    return generateString();
}

// Perform side effects of the card if there is any
// Returns true for successful activation or false for failure
bool Card::activate(std::istream& in, std::ostream& out) {
    return sideEffects(in, out);
}

// Reset the card if it has any special effects
// Called when the card is not in use anymore
void Card::deactivate() {
    resetEffects();
}

// Called when the card is used to create a head
// Triggers event handler, if any
void Card::createHeadEvent() {
    createHeadEventHandler();
}

// Performs any side effects of the card when it is about to be placed on a head
// By default side effects does nothing and returns true
bool Card::sideEffects(std::istream& in, std::ostream& out) {
    return true;
}

// Reset any side effects of the card
// By default this does nothing
void Card::resetEffects() {}

// Event handler when the card forms a new head
// By default this does nothing
void Card::createHeadEventHandler() {}

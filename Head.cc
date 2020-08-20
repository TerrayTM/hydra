#include "Head.h"
#include "Card.h"

// Constructor
Head::Head(std::unique_ptr<Card>&& card, int id) : cards{}, id{id} {
    card->createHeadEvent();
    cards.emplace_back(std::move(card));
}

// Gets the top card on the head
const std::unique_ptr<Card>& Head::getTop() const {
    return cards[cards.size() - 1];
}

// Place a card on the top of the pile
void Head::placeCard(std::unique_ptr<Card>&& card) {
    // First deactivate any top card
    getTop()->deactivate();

    // Place the new top card
    cards.emplace_back(std::move(card));
}

// Returns all the cards on the head
// After call to this function the head should be destroyed
std::vector<std::unique_ptr<Card>> Head::releaseCards() {
    return std::move(cards);
}

// Gets the string representation of the head
std::string Head::toString() const {
    return std::to_string(id) + ": " + getTop()->toString() + " (" + std::to_string(cards.size()) + ")";
}

// Identifier getter
int Head::getIdentifier() const {
    return id;
}

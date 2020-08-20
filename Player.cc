#include "Player.h"
#include "Card.h"
#include "Head.h"

// Constructor
Player::Player(int id) : deck{}, discard{}, reserve{nullptr}, id{id} {}

// Removes the top card of the draw pile and returns it
// Will reshuffle discard into draw if nesscary
std::unique_ptr<Card> Player::popCard() {
    if (deck.size() == 0) {
        reshuffleDiscardPile();
    }

    // Move top card into temporary variable
    std::unique_ptr<Card> card = std::move(deck[0]);
    
    // Remove top card
    deck.erase(deck.begin());

    // Return card
    return card;
}

// Receive cards from an external source and add it to draw pile
void Player::receiveCards(std::vector<std::unique_ptr<Card>>&& cards) {
    std::move(cards.begin(), cards.end(), std::back_inserter(deck));
}

// Get the player's move
int Player::getMove(std::istream& in, std::ostream& out, std::vector<std::unique_ptr<Head>>& heads) {
    return getNextMove(in, out, heads);
}
 
// Returns the total number of cards the player has
int Player::cardCount() const {
    return deck.size() + discard.size() + (reserve != nullptr ? 1 : 0);
}

// Gets the top card of the player's draw pile
// Will reshuffle discard into draw if nesscary
std::unique_ptr<Card>& Player::peekCard() {
    if (deck.size() == 0) {
        reshuffleDiscardPile();
    }

    return deck[0];
}

// Return true if reserve is not empty else false
bool Player::hasReserve() const {
    return reserve != nullptr;
}

// Add reserve card if any to discard pile
void Player::resetReserve() {
    if (hasReserve()) {
        discard.emplace_back(std::move(reserve));
        reserve = nullptr;
    }
}

// Performs cut hydra head procedure
// Returns top two cards from player's draw pile to form the new heads
// Will reshuffle discard into draw pile if nesscary
std::pair<std::unique_ptr<Card>, std::unique_ptr<Card>> Player::cutHead(std::unique_ptr<Head>& head) {
    // Place the played card into discard pile
    discard.emplace_back(popCard());

    // If there is a reserve, place it to discard pile
    if (hasReserve()) {
        discard.emplace_back(std::move(reserve));
        reserve = nullptr;
    }

    // Move all the cards from the head to the player's discard pile
    std::vector<std::unique_ptr<Card>> cards = head->releaseCards();
    std::move(cards.begin(), cards.end(), std::back_inserter(discard));

    // Return top two card from draw pile
    return std::make_pair(popCard(), popCard());
}

// Add the card on top of the draw pile to reserve if it is empty
// If reserve is not empty, swap card with top of the draw pile
void Player::updateReserve() {
    if (hasReserve()) {
        std::swap(reserve, deck[0]);
    } else {
        reserve = popCard();
    }
}

// Get string representation of the player
std::string Player::toString() {
    if (deck.size() == 0) {
        reshuffleDiscardPile();
    }
    
    return generateString();
}

// Get string representation of the player when it is their turn
// Remaining indicates how many cards they must still play in their turn
std::string Player::toActiveString(int remaining) {
    if (deck.size() == 0) {
        reshuffleDiscardPile();
    }

    return generateActiveString(remaining);
}

// Push a card to the top of the draw pile
void Player::pushCard(std::unique_ptr<Card>&& card) {
    deck.insert(deck.begin(), std::move(card));
}

// Shuffles the discard pile and put it into the draw pile
void Player::reshuffleDiscardPile() {
    // Seed random with current time
    srand(time(nullptr));

    // Perform shuffle
    for (int i = discard.size() - 1; i >= 0; --i) { 
        int j = rand() % (i + 1);
        std::swap(discard[i], discard[j]);
    }

    // Move the discard pile to draw pile and then clear the discard pile
    std::move(discard.begin(), discard.end(), std::back_inserter(deck));
    discard.clear();
}

// Destructor
Player::~Player() {}

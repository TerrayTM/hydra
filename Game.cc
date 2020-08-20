#include "Game.h"
#include "Card.h"
#include "Head.h"
#include "Player.h"
#include "Computer.h"
#include "Human.h"
#include "Joker.h"
#include "Regular.h"
#include "Random.h"
#include "Greedy.h"

// Constructor
Game::Game() : players{}, heads{}, currentPlayer{0}, cardsRemaining{0} {}

// Initialize the game
void Game::initialize(int humanPlayers, int computerPlayers, std::istream& in, std::ostream& out) {
    // Create the players
    createPlayers(humanPlayers, computerPlayers, in, out);

    // Create the cards
    std::vector<std::unique_ptr<Card>> cards = createCards();

    // Shuffle the cards
    shuffleCards(cards);

    // Distribute the cards
    distributeCards(std::move(cards));

    // Create the first head
    createHead(in, out);
}

// Play the game
void Game::play(std::istream& in, std::ostream& out) {
    // While our game is not over
    while (!isGameOver()) {
        // Print current game state
        out << std::endl << generateString(false) << std::endl;

        // Print player's turn
        out << "Player " << currentPlayer + 1 << ", it is your turn." << std::endl;

        // Wait for user input to proceed
        std::string wait;

        // If input is EOF then we end game
        if (!std::getline(in, wait)) {
            return;
        }

        if (!std::getline(in, wait)) {
            return;
        }

        // Loop for however many cards the player must play on their turn
        for (cardsRemaining = cardsRequired(); cardsRemaining > 0; --cardsRemaining) {
            // EOF reached then stop
            if (in.eof()) {
                return;
            }

            // Print game state with current player's info
            out << std::endl << generateString(true) << std::endl;

            // Call event handler for request move
            requestMoveEvent(in, out);

            // Print player holding what card
            out << "Player " << currentPlayer + 1 << ", you are holding a " << players[currentPlayer]->peekCard()->toString() << ". Your move?" << std::endl;
        
            int move = players[currentPlayer]->getMove(in, out, heads);

            // Ensure move is valid (not out of bounds)
            if (move != 0) {
                if (move < 0 || move < heads[0]->getIdentifier() || move > heads[heads.size() - 1]->getIdentifier()) {
                    // Bad input, retry
                    ++cardsRemaining;
                    continue;
                }
            }

            // Try to activate the card before placing on head
            if (move != 0 && !players[currentPlayer]->peekCard()->activate(in, out)) {
                // Activation failed, retry move
                ++cardsRemaining;
                continue;
            }

            // Get whether the move propsed by player is valid, invalid, or ends their turn immediately
            MoveState moveState = getMoveState(move);

            // If move is invalid according to game rule then repeat asking
            if (moveState == MoveState::invalid) {
                players[currentPlayer]->peekCard()->deactivate();
                ++cardsRemaining;
                continue;
            }

            // Perform cut head if directive is to cut
            if (moveState == MoveState::cut) {
                // Get the identifier
                int starting = heads[heads.size() - 1]->getIdentifier();

                // Cut and plant the seeds to grow into new heads
                plantNewHeads(players[currentPlayer]->cutHead(heads[0]), starting, in, out);

                // Remove oldest head from vector
                heads.erase(heads.begin());

                // Ends current player's turn after cutting head
                moveState = MoveState::stop;
            } else {
                // If the player chooses to put card in reserve
                if (move == 0) {
                    // If player has a reserve, they cannot decrease how many cards placed by swapping over and over again
                    if (players[currentPlayer]->hasReserve()) {
                        ++cardsRemaining;
                    }

                    // Put or swap card in reserve
                    players[currentPlayer]->updateReserve();
                } else {
                    // Place the card on head
                    heads[move - heads[0]->getIdentifier()]->placeCard(players[currentPlayer]->popCard());
                }
            }

            // Check if the player has won
            if (isWinner(players[currentPlayer])) {
                out << "Player " << currentPlayer + 1 << " wins!" << std::endl; 
                return;
            }

            // Ends player's turn immediately if move state is to stop
            if (moveState == MoveState::stop) {
                break;
            }
        }

        // Add reserve card to discard pile
        players[currentPlayer]->resetReserve();

        // Go to the next player
        currentPlayer = (currentPlayer + 1) % players.size();
    }

    out << "Turn limit has been reached. Game is over and no one wins." << std::endl;
}

// Destructor
Game::~Game() {}

// Create the players
void Game::createPlayers(int humanPlayers, int computerPlayers, std::istream& in, std::ostream& out) {
    // Player indexer
    int i;

    // Create the human players first
    for (i = 1; i <= humanPlayers; ++i) {
        players.emplace_back(std::make_unique<Human>(i));
    }

    // Create the computer players after
    for (; i <= computerPlayers + humanPlayers; ++i) {
        // Ask for CPU strategy
        out << "What strategy should CPU player " << i << " use? Enter \"greedy\" or \"random\"." << std::endl;
        
        std::string input;
        in >> input;

        if (input == "greedy") {
            players.emplace_back(std::make_unique<Computer>(i, std::make_unique<Greedy>()));
        } else {
            players.emplace_back(std::make_unique<Computer>(i, std::make_unique<Random>()));
        }
    }
}

// Create the cards
std::vector<std::unique_ptr<Card>> Game::createCards() {
    std::vector<std::unique_ptr<Card>> cards{};

    // Create all the cards
    for (size_t i = 0; i < players.size(); ++i) {
        // Add clubs cards
        for (int value = 1; value <= 13; ++value) {
            cards.emplace_back(std::make_unique<Regular>(CardSuit::clubs, value));
        }

        // Add diamonds cards
        for (int value = 1; value <= 13; ++value) {
            cards.emplace_back(std::make_unique<Regular>(CardSuit::diamonds, value));
        }

        // Add hearts cards
        for (int value = 1; value <= 13; ++value) {
            cards.emplace_back(std::make_unique<Regular>(CardSuit::hearts, value));
        }

        // Add spades cards
        for (int value = 1; value <= 13; ++value) {
            cards.emplace_back(std::make_unique<Regular>(CardSuit::spades, value));
        }

        // Add the 2 joker cards per every player there is
        cards.emplace_back(std::make_unique<Joker>());
        cards.emplace_back(std::make_unique<Joker>());
    }

    // Return the cards
    return cards;
}

// Shuffle the cards
void Game::shuffleCards(std::vector<std::unique_ptr<Card>>& cards) {
    // Seed random with current time
    srand(time(nullptr));

    // Perform shuffle
    for (int i = cards.size() - 1; i >= 0; --i) { 
        int j = rand() % (i + 1);
        std::swap(cards[i], cards[j]);
    }
}

// Distribute the cards
void Game::distributeCards(std::vector<std::unique_ptr<Card>>&& cards) {
    // Calculate how many cards each player gets
    int splitSize = cards.size() / players.size();
    
    // Give each player cards
    for (size_t i = 0; i < players.size(); ++i) {
        std::vector<std::unique_ptr<Card>> chunk{};

        // Move cards into chunk
        std::move(cards.begin() + i * splitSize, cards.begin() + (i + 1) * splitSize, std::back_inserter(chunk));

        // Give player card
        players[i]->receiveCards(std::move(chunk));
    }
}

// Determine if the game is over
bool Game::isGameOver() const {
    // By default game runs until winner is found
    return false;
}

// Determine if the player is a winner
bool Game::isWinner(std::unique_ptr<Player>& player) {
    // By default the player is a winner if they have 0 cards
    return player->cardCount() == 0;
}

// Get a string representation of the current game state
// If use active is set to true then we display the current user
std::string Game::generateString(bool useActive) const {
    std::string output = "Heads:\n";

    // Get all head strings
    for (size_t i = 0; i < heads.size(); ++i) {
        output += heads[i]->toString();
        output += "\n";
    }

    output += "\nPlayers:\n";

    // Get all player strings
    for (size_t i = 0; i < players.size(); ++i) {
        // Get active player string if we enable active
        if (useActive && i == currentPlayer) {
            output += players[i]->toActiveString(cardsRemaining - 1);
        } else {
            output += players[i]->toString();
        }

        output += "\n";
    }

    return output;
}

// Get the number of cards a player must play on their turn
// By default this is the number of heads present
// Can be customized in concrete classes
int Game::cardsRequired() const {
    return heads.size();
}

// Create the first head
void Game::createHead(std::istream& in, std::ostream& out) {
    // Create the first head
    heads.emplace_back(std::make_unique<Head>(players[currentPlayer]->popCard(), 1));

    // Go to the next player
    currentPlayer = (currentPlayer + 1) % players.size();
}

void Game::plantNewHeads(std::pair<std::unique_ptr<Card>, std::unique_ptr<Card>>&& seeds, int starting, std::istream& in, std::ostream& out) {
    heads.emplace_back(std::make_unique<Head>(std::move(seeds.first), starting + 1));
    heads.emplace_back(std::make_unique<Head>(std::move(seeds.second), starting + 2));
}

// Request move event handler
// By default this does nothing but is provided for child class to modify if needed
void Game::requestMoveEvent(std::istream& in, std::ostream& out) {}

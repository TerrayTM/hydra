#ifndef _GAME_H_
#define _GAME_H_

#include <vector>
#include <memory>
#include <iostream>
#include <ctime>

class Player;
class Head;
class Card;

// The move state when we call to get state based on player's move
// Invalid means the move proposed by player is invalid
// Valid means the move proposed by player is valid
// Stop means the move is valid but player's turn ends immediately
// Cut means we must cut down the oldest head
enum MoveState {
    invalid, 
    valid,
    stop,
    cut
};

// Represents the game abstract base class
class Game {
  private:
    // Create the players
    virtual void createPlayers(int humanPlayers, int computerPlayers, std::istream& in, std::ostream& out);

    // Create the cards
    virtual std::vector<std::unique_ptr<Card>> createCards();
    
    // Shuffle the cards
    virtual void shuffleCards(std::vector<std::unique_ptr<Card>>& cards);
    
    // Distribute the cards
    virtual void distributeCards(std::vector<std::unique_ptr<Card>>&& cards);

    // Determine if the game is over
    // Useful for ending the game after a certain number of turns
    virtual bool isGameOver() const;

    // Determine if the player is a winner
    virtual bool isWinner(std::unique_ptr<Player>& player);

    // Get the move state based on a move proposed by player
    virtual MoveState getMoveState(int move) const = 0;

    // Get a string representation of the current game state
    // If use active is set to true then we display the current user
    virtual std::string generateString(bool useActive) const;

    // Get the number of cards a player must play on their turn
    // By default this is the number of heads present
    // Can be customized in concrete classes
    virtual int cardsRequired() const;

    // Create the first head
    virtual void createHead(std::istream& in, std::ostream& out);

    // Plant the two new heads after cutting one down
    virtual void plantNewHeads(std::pair<std::unique_ptr<Card>, std::unique_ptr<Card>>&& seeds, int starting, std::istream& in, std::ostream& out);

    // Request move event handler
    // By default this does nothing but is provided for child class to modify if needed
    virtual void requestMoveEvent(std::istream& in, std::ostream& out);

  protected:
    // Track all the players
    std::vector<std::unique_ptr<Player>> players;

    // Track all the heads
    // Heads are arranged in increasing consecutive identifiers
    std::vector<std::unique_ptr<Head>> heads;

    // Track index of the current player
    size_t currentPlayer;

    // Cards remaining on this turn
    int cardsRemaining;

  public:
    // Constructor
    Game();

    // Initialize the game
    void initialize(int humanPlayers, int computerPlayers, std::istream& in, std::ostream& out);

    // Play the game
    void play(std::istream& in, std::ostream& out);

    // Destructor
    virtual ~Game();
};

#endif

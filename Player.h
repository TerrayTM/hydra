#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <ctime>

class Card;
class Head;

// Represents a player abstract class
class Player {
  private:
    // Gets the player's next move
    virtual int getNextMove(std::istream& in, std::ostream& out, std::vector<std::unique_ptr<Head>>& heads) = 0;
    
    // Generates a string representing this player when it is not their turn
    virtual std::string generateString() const = 0;

    // Generates a string representing this player when it is their turn
    virtual std::string generateActiveString(int remaining) const = 0;

    // Shuffles the discard pile and put it into the draw pile
    virtual void reshuffleDiscardPile();

  protected:
    // The player's draw pile
    // The top card is at index 0
    std::vector<std::unique_ptr<Card>> deck;

    // The player's discard pile
    // The top card is at the last index (bottom card of the pile is at index 0)
    std::vector<std::unique_ptr<Card>> discard;

    // The player's reserve
    std::unique_ptr<Card> reserve;

    // The identifier of the player
    int id;

  public:
    // Constructor
    Player(int id);

    // Removes the top card of the draw pile and returns it
    // Will reshuffle discard into draw if nesscary
    std::unique_ptr<Card> popCard();
    
    // Receive cards from an external source and add it to draw pile
    void receiveCards(std::vector<std::unique_ptr<Card>>&& cards);

    // Get the player's move
    int getMove(std::istream& in, std::ostream& out, std::vector<std::unique_ptr<Head>>& heads);

    // Returns the total number of cards the player has
    int cardCount() const;

    // Gets the top card of the player's draw pile
    // Will reshuffle discard into draw if nesscary
    std::unique_ptr<Card>& peekCard();

    // Return true if reserve is not empty else false
    bool hasReserve() const;

    // Add reserve card if any to discard pile
    void resetReserve();

    // Performs cut hydra head procedure
    // Returns top two cards from player's draw pile to form the new heads
    // Will reshuffle discard into draw pile if nesscary
    std::pair<std::unique_ptr<Card>, std::unique_ptr<Card>> cutHead(std::unique_ptr<Head>& head);

    // Add the card on top of the draw pile to reserve if it is empty
    // If reserve is not empty, swap card with top of the draw pile
    void updateReserve();

    // Get string representation of the player
    std::string toString();

    // Get string representation of the player when it is their turn
    // Remaining indicates how many cards they must still play in their turn
    std::string toActiveString(int remaining);

    // Push a card to the top of the draw pile
    void pushCard(std::unique_ptr<Card>&& card);

    // Destructor
    virtual ~Player();
};

#endif

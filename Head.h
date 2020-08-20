#ifndef _HEAD_H_
#define _HEAD_H_

#include <memory>
#include <vector>
#include <string>

class Card;

// Represents a hydra head
class Head {
  private:
    // Stores the cards on this head pile
    // The top of the head is at the last index
    std::vector<std::unique_ptr<Card>> cards;

    // Stores the identifier of this head
    int id;

  public:
    // Constructor
    Head(std::unique_ptr<Card>&& card, int id);

    // Gets the top card on the head
    const std::unique_ptr<Card>& getTop() const;

    // Place a card on the top of the pile
    void placeCard(std::unique_ptr<Card>&& card);

    // Returns all the cards on the head
    // After call to this function the head should be destroyed
    std::vector<std::unique_ptr<Card>> releaseCards();

    // Gets the string representation of the head
    std::string toString() const;

    // Identifier getter
    int getIdentifier() const;
};

#endif

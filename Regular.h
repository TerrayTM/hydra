#ifndef _REGULAR_H_
#define _REGULAR_H_

#include <string>
#include "Card.h"

// Represents a regular card with suits: diamonds, spades, hearts, or clubs
class Regular : public Card {
  private:
    // Override base generate string
    std::string generateString() const override;
  
  public:
    // Constructor
    Regular(CardSuit suit, int value);
};

#endif

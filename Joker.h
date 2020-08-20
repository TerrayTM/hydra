#ifndef _JOKER_H_
#define _JOKER_H_

#include <string>
#include <iostream>
#include "Card.h"

// Represents a joker card
class Joker : public Card {
  private:
    // Track card state
    bool isActivated;
    
    // Override generate string
    std::string generateString() const override;

    // Override base side effects
    bool sideEffects(std::istream& in, std::ostream& out) override;

    // Override base reset effects
    void resetEffects() override;

    // Override base create head event handler
    void createHeadEventHandler() override;
  
  public:
    // Constructor
    Joker();

    // Constructor for an activated joker
    Joker(int value);
};

#endif

#ifndef _CARD_H_
#define _CARD_H_

#include <iostream>
#include <string>

// The card suits
enum CardSuit {
    diamonds,
    spades,
    hearts,
    clubs,
    joker
};

// Represents the base abstract class for cards
class Card {
  private:
    // Generates a string representation of the card
    // To be implemented by concrete classes
    virtual std::string generateString() const = 0;

    // Performs any side effects of the card when it is about to be placed on a head
    // By default side effects does nothing and returns true
    virtual bool sideEffects(std::istream& in, std::ostream& out);

    // Reset any side effects of the card
    // By default this does nothing
    virtual void resetEffects();

    // Event handler when the card forms a new head
    // By default this does nothing
    virtual void createHeadEventHandler();

  protected:
    // The suit of the card
    CardSuit suit;

    // The value of the card
    int value;

  public:
    // Constructor
    Card(CardSuit suit, int value);

    // Card value getter
    int getValue() const;

    // Card suit getter
    CardSuit getSuit() const;

    // Get the string representation of the card
    std::string toString() const;

    // Perform side effects of the card if there is any
    // Returns true for successful activation or false for failure
    bool activate(std::istream& in, std::ostream& out);

    // Reset the card if it has any special effects
    // Called when the card is not in use anymore
    void deactivate();

    // Called when the card is used to create a head
    // Triggers event handler, if any
    void createHeadEvent();
};

#endif

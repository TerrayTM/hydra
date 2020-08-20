#include "Regular.h" 

// Constructor
Regular::Regular(CardSuit suit, int value) : Card{suit, value} {}

// Override base generate string
std::string Regular::generateString() const {
    char character;

    // Find the correct character for the suit
    switch (suit) {
        case CardSuit::clubs:
            character = 'C';
            break;
        
        case CardSuit::hearts:
            character = 'H';
            break;

        case CardSuit::spades:
            character = 'S';
            break;

        case CardSuit::diamonds:
            character = 'D';
            break;
        
        default:
            character = '?';
    }

    std::string number; 

    // Find the correct string for the value
    switch (value) {
        case 1:
            number = "A";
            break;
        
        case 11: 
            number = "J";
            break;
        
        case 12:
            number = "Q";
            break;
        
        case 13:
            number = "K"; 
            break;
        
        default:
            number = std::to_string(value); 
    }

    // Return the card's representation
    return number + character;
}

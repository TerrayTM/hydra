#include "Joker.h"

// Constructor
Joker::Joker() : Card{CardSuit::joker, 2}, isActivated{false} {}

// Constructor for an activated joker
Joker::Joker(int value) : Card{CardSuit::joker, value}, isActivated{true} {}

// Override generate string
std::string Joker::generateString() const {
    // If card is not activated then return simple string
    if (!isActivated) {
        return "Joker";
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

    return number + 'J';
}

// Override base side effects
bool Joker::sideEffects(std::istream& in, std::ostream& out) {
    // Prompt joker value
    out << "Joker value?" << std::endl;
    
    int number;

    if (isActivated) {
        out << value << std::endl;
        number = value;
    } else {
        // Get input
        std::string input; 
        in >> input;

        // Get the value inputted
        if (input == "A") {
            number = 1;
        } else if (input == "J") {
            number = 11;
        } else if (input == "Q") {
            number = 12;
        } else if (input == "K") {
            number = 13;
        } else {
            try {
                // Attempt to get integer of input
                number = std::stoi(input);
            } catch (...) {
                // Input is not a valid number
                return false;
            }

            // Invalid card value
            if (number < 2 || number > 10) {
                return false;
            }
        }
    }

    // Update card value and activation state
    value = number;
    isActivated = true;

    // Successfully acquired joker value
    return true;
}

// Override base reset effects
void Joker::resetEffects() {
    value = 2;
    isActivated = false;
};

void Joker::createHeadEventHandler() {
    value = 2;
    isActivated = true;
}

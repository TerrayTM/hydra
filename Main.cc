#include <iostream>
#include <memory>
#include <string>
#include "Game.h"
#include "Vanilla.h"
#include "Sandbox.h"
#include "Custom.h"

int main(int argc, char* argv[]) {
    std::unique_ptr<Game> game = nullptr;
    int playerCount;
    int cpuCount = 0;

    // Read how many players
    std::cout << "How many players?" << std::endl;

    // If no valid input we exit
    if (!(std::cin >> playerCount)) {
        return 0;
    }

    if (argc == 2) {
        std::string option = argv[1];

        if (option == "-testing") {
            // Selects sandbox game mode
            game = std::make_unique<Sandbox>();
        } else if (option == "-custom") {
            // Selects custom game mode
            game = std::make_unique<Custom>();
        } else if (option == "-cpu") {
            // Ask for how many CPU players
            std::cout << "How many CPU players?" << std::endl;

            // If no valid input we exit
            if (!(std::cin >> cpuCount)) {
                return 0;
            }
        }
    }

    if (cpuCount + playerCount == 0) {
        std::cout << "Game is over since there are no players." << std::endl;
        return 0;
    }

    // If user don't specify game mode then we play vanilla
    if (game == nullptr) {
        game = std::make_unique<Vanilla>();
    }

    // Initialize the game
    game->initialize(playerCount, cpuCount, std::cin, std::cout);

    // Play the game
    game->play(std::cin, std::cout);

    return 0;
}

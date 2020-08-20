#ifndef _SANDBOX_H_
#define _SANDBOX_H_

#include "Game.h"

// Represents a game of sandbox hydra with the ability to change cards to whatever you want
class Sandbox : public Game {
  private:
    // Override get move state
    // Sand box mode has same rules as vanilla
    MoveState getMoveState(int move) const override;

    // Override create head
    void createHead(std::istream& in, std::ostream& out) override;

    // Generate card based on user input
    std::unique_ptr<Card> generateCard(std::istream& in, std::ostream& out) const;

    // Override plant new heads to specify any seed card
    void plantNewHeads(std::pair<std::unique_ptr<Card>, std::unique_ptr<Card>>&& seeds, int starting, std::istream& in, std::ostream& out) override;
    
    // Override request move event handler
    void requestMoveEvent(std::istream& in, std::ostream& out) override;

  public:
    // Constructor
    Sandbox();
};

#endif

#ifndef _VANILLA_H_
#define _VANILLA_H_

#include "Game.h"

// Represents a game of vanilla hydra with the default rules and settings
class Vanilla : public Game {
  private:
    // Override get move state
    MoveState getMoveState(int move) const override;

  public:
    // Constructor
    Vanilla();
};

#endif

#ifndef _CUSTOM_H_
#define _CUSTOM_H_

#include "Game.h"

// Represents a custom game with house rules
class Custom : public Game {
  private:
    // Override get move state
    MoveState getMoveState(int move) const override;

  public:
    // Constructor
    Custom();
};

#endif

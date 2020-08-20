#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <vector>
#include <memory>
#include "Strategy.h"

class Head;
class Card;

// Represents a random strategy
// The strategy is to enumerate all valid moves then random select a move
class Random : public Strategy {
  public:
    // Override base compute move
    int computeNextMove(std::unique_ptr<Card>& card, std::vector<std::unique_ptr<Head>>& heads) const override;
};

#endif

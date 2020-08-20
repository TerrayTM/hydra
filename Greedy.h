#ifndef _GREEDY_H_
#define _GREEDY_H_

#include <vector>
#include <memory>
#include "Strategy.h"

class Head;
class Card;

// Represents a greedy strategy
// The strategy is to enumerate all valid moves and then select a move such that the difference between the current card value and the head is minimized
class Greedy : public Strategy {
  public:
    // Override base compute move
    int computeNextMove(std::unique_ptr<Card>& card, std::vector<std::unique_ptr<Head>>& heads) const override;
};

#endif

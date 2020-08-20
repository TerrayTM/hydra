#ifndef _STRATEGY_H_
#define _STRATEGY_H_

#include <vector>
#include <memory>

class Head;
class Card;

// Represents a strategy base class for the CPU players
class Strategy {
  public:
    // Computes the next move based on the current card and heads
    virtual int computeNextMove(std::unique_ptr<Card>& card, std::vector<std::unique_ptr<Head>>& heads) const = 0;

    // Destructor
    virtual ~Strategy();
};

#endif

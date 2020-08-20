#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include "Player.h"
#include "Strategy.h"

class Strategy;

// Represents a CPU player
class Computer : public Player {
  private:
    // The player's strategy
    std::unique_ptr<Strategy> strategy;
  
    // Override base get next move
    int getNextMove(std::istream& in, std::ostream& out, std::vector<std::unique_ptr<Head>>& heads) override;

    // Override base generate string
    std::string generateString() const override;

    // Override base generate active string
    std::string generateActiveString(int remaining) const override;

  public:
    // Constructor
    Computer(int id, std::unique_ptr<Strategy>&& strategy);
};

#endif

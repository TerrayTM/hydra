#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "Player.h"

// Represents a human player
class Human : public Player {
  private:
    // Override base get next move
    int getNextMove(std::istream& in, std::ostream& out, std::vector<std::unique_ptr<Head>>& heads) override;
    
    // Override base generate string
    std::string generateString() const override;

    // Override base generate active string
    std::string generateActiveString(int remaining) const override;

  public:
    // Constructor
    Human(int id);
};

#endif 

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Unit.h"

class Player : public Unit {
private:
   

public:
    Player(Machine* machine, GridElement*** cgrid, int cgridSize) : Unit(machine, cgrid, cgridSize) {
        texPath->setBlendColor(40, 40, 40, 111);
        speed = 0.06f;
    }
    
    ~Player() {
        
    }
    
    void render(Machine* machine) {
        Unit::render(machine);
        
    }
    
};

#endif

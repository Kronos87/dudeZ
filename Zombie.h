#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include "Unit.h"
#include "Util.h"

class Zombie : public Unit {
    
private:
    
public:

    Zombie(Machine* machine, GridElement*** cgrid, int cgridSize) : Unit(machine, cgrid, cgridSize) {
        texPath->setBlendColor(222, 40, 40, 111);
        speed = 0.04f;
        
        alarmBox->w = cgridSize * 5;
        alarmBox->h = cgridSize * 5;
    }
    
    ~Zombie() {
        
    }
    
    void update(Machine* machine) {
        Unit::update(machine);
        
        if(bestway.empty()) {
            findPath(Util::rndNo(0, Machine::WIDTH / gridSize), Util::rndNo(0, Machine::HEIGHT / gridSize));
        }
    }
    
    void render(Machine* machine) {
        Unit::render(machine);
    }
    
};

#endif

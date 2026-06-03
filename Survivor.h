#ifndef SURVIVOR_H_
#define SURVIVOR_H_

#include "unit.h"

class Survivor : public Unit {
private:
    
    
public:
    Survivor(Machine* machine, GridElement*** cgrid, int cgridSize) : Unit(machine, cgrid, cgridSize) {
        texPath->setBlendColor(40, 222, 40, 111);
        speed = 0.05f;
        counted = false;
    }
    
    ~Survivor() {
        
    }
    
    void render(Machine* machine) {
        Unit::render(machine);
        
    }
    
    bool counted;
    
};

#endif

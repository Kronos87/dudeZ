#ifndef __DudeZ__Mover__
#define __DudeZ__Mover__

#include "Geom.h"
#include "Util.h"
#include "Machine.h"

class Mover {
public:
    Vector2F* location;
    Vector2F* velocity;
    Vector2F* acc;
    float mass;
    float friction;
    
    float topspeed;
    
    RectF* rect;
    
    Mover(float x, float y, float m) {
        location = new Vector2F(x, y);
        velocity = new Vector2F(0, 0);
        acc = new Vector2F(0, 0);
        
        topspeed = 4;
        mass = m;
        friction = 0.01f;
        
        rect = new RectF(0, 0, 15, 15);
    }
    
    ~Mover() {
        delete rect;
        delete location;
        delete velocity;
        delete acc;
    }
    
    void applyForce(Vector2F* force) {
        Vector2F* f = force->copy();
        f->div(mass);
        acc->add(f);
        
        delete f;
    }
    
    void update(Machine* machine, float mx, float my) {
        //Position
        Vector2F* position = new Vector2F(mx, my);
        Vector2F* dir = position->sub(location);
        dir->normalize();
        
        //Friction
        Vector2F* fric = velocity->copy();
        fric->mul(-1);
        fric->normalize();
        fric->mul(friction);
        fric->div(mass);
        acc->add(fric);
        
        //Add a force
        acc->add(dir->mul(0.007 * machine->getDeltaTime()));
        
        velocity->add(acc);
        acc->mul(0);
        
        velocity->limit(topspeed);
        location->add(velocity);
        
        rect->x = location->x;
        rect->y = location->y;
        
        delete fric;
        delete position;
    }
    
    void render(Machine* machine) {
        machine->setColor(0, 0, 224, 225);
        rect->fill(machine->getRenderer());
    }
    
};

#endif

#ifndef UNIT_H_
#define UNIT_H_

#include "SDL.h"
#include "AStar.h"
#include "Machine.h"
#include "Texture.h"
#include "Geom.h"

#include <deque>
#include <vector>

class Unit : public RectF {
public:
    bool alarmed;
    
    RectF* alarmBox;
    
    Unit(Machine* machine, GridElement*** cgrid, int cgridSize) : RectF(0, 0, 0, 0), grid(cgrid), gridSize(cgridSize) {
        w = gridSize;
        h = gridSize;
        
        texPath = new Texture(Texture::createTexture(machine->getRenderer(), cgridSize, cgridSize));
        
        alarmBox = new RectF(0, 0, cgridSize * 3, cgridSize * 3);
        alarmed = false;
        
        RectF::update();
    }
    
    virtual ~Unit() {
        delete texPath;
        delete astar;
    }
    
    void findPath(int tx, int ty) {
        RectF::update();
        
        delete astar;
        
        astar = new AStar(gridSize, Machine::WIDTH, Machine::HEIGHT, grid);
        astar->set(x/gridSize, y/gridSize, tx, ty);
        
        int i=0;
        while(!astar->findPath()) {
            i++;
        }
        
        //Fill bestway deque
        bestway.clear();
        
        Waypoint* wp = astar->getBestPath();
        while(wp != nullptr) {
            bestway.push_front(wp);
            
            wp = wp->getPrevious();
        }
        
    }
    
    //TODO for memory saving put in Unit Processor
    virtual void update(Machine* machine) {
        bool arrivedX = false;
        bool arrivedY = false;
        
        if(bestway.empty()) {
            //arrived
            alarmed = false;
        } else {
            int ix = int( x + 0.5f );
            int iy = int( y + 0.5f );
            
            if(ix < bestway.front()->x * gridSize) {
                x += speed * machine->getDeltaTime();
                
                if(x > bestway.front()->x * gridSize)
                    x = bestway.front()->x * gridSize;
                
            } else if(ix > bestway.front()->x * gridSize) {
                x -= speed * machine->getDeltaTime();
                
                if(x < bestway.front()->x * gridSize)
                   x = bestway.front()->x * gridSize;
                
            } else {
                arrivedX = true;
            }
            
            if(iy < bestway.front()->y * gridSize) {
                y += speed * machine->getDeltaTime();
                
                if(y > bestway.front()->y * gridSize)
                   y = bestway.front()->y * gridSize;
                
                
            } else if(iy > bestway.front()->y * gridSize) {
                y -= speed * machine->getDeltaTime();
                
               if(y < bestway.front()->y * gridSize)
                   y = bestway.front()->y * gridSize;
                
            } else {
                arrivedY = true;
            }
            
            if(arrivedX && arrivedY) {
                bestway.pop_front();
            }
        }
        
        //arrange alarmBox
        alarmBox->x = x - alarmBox->w/2 + w/2;
        alarmBox->y = y - alarmBox->h/2 + h/2;
        
        RectF::update();
    }
    
    void renderPath(Machine* machine) {
        if(!astar)
            return;
        
        Waypoint* wp = astar->getBestPath();
        
        SDL_Rect rect;
        while(wp != nullptr) {
            rect.x = wp->x * gridSize;
            rect.y = wp->y * gridSize;
            rect.w = gridSize;
            rect.h = gridSize;
            
            texPath->render(machine->getRenderer(), &rect);
            
            wp = wp->getPrevious();
        }
    }
    
    virtual void render(Machine* machine) {
        texture->render(machine->getRenderer(), sdlRect);
        
        if(alarmed)
            machine->setColor(255, 0, 0, 255);
        else
            machine->setColor(0, 0, 0, 255);
        
        alarmBox->draw(machine->getRenderer());
    }
    
    void stop() {
        bestway.clear();
    }
    
    void setTexture(Texture* ctexture) {
        texture = ctexture;
    }
    
    bool reachedTarget() {
        return bestway.empty();
    }
    
protected:
    Texture* texture;
    Texture* texPath;
    
    float speed;
    
    GridElement*** grid;
    int gridSize;
    
    AStar* astar = nullptr;
    
    std::deque<Waypoint*> bestway;
    
};


///////// UnitProcessor

class UnitProcessor {
private:
    static std::vector<Unit*> units;
    
public:
    static void addUnit(Unit* unit) {
        
    }
    
    static void findPath(int tx, int ty) {
        
    }
    
    static void update(Machine* machine) {
        
    }
    
};

#endif

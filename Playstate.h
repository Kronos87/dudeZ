#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

#include "Machine.h"

class PlayState : public GameState {
    
private:
    static PlayState instance;
    
    public:
    
        void pause();
        void resume();
    
        void init(Machine* machine);
        void update(Machine* machine);
        void render(Machine* machine);
        void handleEvents(Machine* machine);
        void cleanUp();
    
        static PlayState* Instance() {
            return &instance;
        }
    
    protected:
        PlayState() {}
    
};

#endif

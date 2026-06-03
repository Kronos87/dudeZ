#include "Introstate.h"
#include "Playstate.h"
#include "Font.h"


IntroState IntroState::instance;

void IntroState::pause() {
    paused = true;
}

void IntroState::resume() {
    paused = false;
}

void IntroState::init(Machine* machine) {
    font = new Font("04B_03.ttf", 34, 222, 222, 222);
    
    
    bgcolor = new SDL_Color;
    bgcolor->r = 104;
    bgcolor->g = 177;
    bgcolor->b = 136;
    bgcolor->a = 255;
    
    bgrect = new SDL_Rect;
    bgrect->x = 0;
    bgrect->y = 0;
    bgrect->w = Machine::WIDTH;
    bgrect->h = Machine::HEIGHT;
    
    duration = 10;
    
    leftrect = new SDL_Rect;
    leftrect->x = 0;
    leftrect->y = 0;
    leftrect->w = Machine::WIDTH;
    leftrect->h = 0;

    
}

void IntroState::update(Machine* machine) {
        duration -= machine->getDeltaTime();
}

void IntroState::render(Machine* machine) {
    if(!paused) {
        
    /* update */
    
        printf("deltaTime: %f\n", machine->getDeltaTime());
        

    

    
    leftrect->h = (1 - (duration / 10.0f)) * Machine::HEIGHT;
    
    /* render */
    
    machine->setColor(bgcolor);
    SDL_RenderFillRect(machine->getRenderer(), bgrect);
    
    
    machine->setColor(220, 34, 11, 255);
    SDL_RenderFillRect(machine->getRenderer(), leftrect);
    
    font->renderFontOutlined(machine->getRenderer(), "DudeZ", Machine::CENTER_X - font->getWidth() / 2, Machine::CENTER_Y - font->getHeight() / 2, 3, 200);
    
    machine->setColor(0, 0, 0, 255);
    }
    
    if(duration <= 0) {
        machine->changeState(PlayState::Instance());
    }
    
}

void IntroState::handleEvents(Machine* machine) {

}

void IntroState::cleanUp() {
    delete font;
    
    delete leftrect;
    delete bgrect;
    delete bgcolor;
}
#include "Animation.h"
#include "SDL.h"

//Pixel-by-Pixel Animation
Animation::Animation(Texture* ctexture, int cwidth, int durationSpeed) : texture(ctexture) , width(cwidth), duration(durationSpeed) {
    rectPBP = new SDL_Rect;
    rectPBP->w = width;
    rectPBP->h = texture->getHeight();
    rectPBP->x = 0;
    rectPBP->y = 0;
    
    cDura = 0;
    finish = true;
}

//Normal Sprite Animation
Animation::Animation(Texture* ctexture, int frames, int tileWidth, int durationSpeed) : texture(ctexture), maxFrames(frames), duration(durationSpeed) {
    frameClips = new SDL_Rect[frames];
    
    for(int i=0; i < frames; i++) {
        frameClips[i].x = i * tileWidth;
        frameClips[i].y = 0;
        frameClips[i].w = tileWidth;
        frameClips[i].h = texture->getHeight();
    }
    
    currentFrame = 0;
    cDura = 0;
}

Animation::~Animation() {
    delete[] frameClips;
    delete texture;
    delete rectPBP;
}

void Animation::render(Machine* machine, int x, int y) {
    SDL_Rect tmpsrc;
    tmpsrc.x = x;
    tmpsrc.y = y;
    tmpsrc.w = frameClips[0].w;
    tmpsrc.h = frameClips[0].h;
    
    SDL_RenderCopy(machine->getRenderer(), texture->getSDL_Texture(), &frameClips[currentFrame], &tmpsrc);
}

void Animation::renderPBP(Machine* machine, int x, int y) {
    SDL_Rect tmpsrc;
    tmpsrc.x = x;
    tmpsrc.y = y;
    tmpsrc.w = width;
    tmpsrc.h = texture->getHeight();
    
    SDL_RenderCopy(machine->getRenderer(), texture->getSDL_Texture(), rectPBP, &tmpsrc);
}

void Animation::updatePBP(float delta) {
    if(finish)
        return;
    
    cDura += delta;
    
    if(cDura >= duration) {
        if(!loopBack && rectPBP->x >= texture->getWidth() - width) {
            //ende
            finish = true;
            loopBack = true;
            return;
        } else if(!loopBack && rectPBP->x <= texture->getWidth() - width) {
            rectPBP->x += 1;
            cDura = 0;
        }
        
        if(loopBack && rectPBP->x <= 0) {
            finish = true;
            loopBack = false;
        } else if(loopBack && rectPBP->x >= 0) {
            rectPBP->x -= 1;
            cDura = 0;
        }
    }
}

void Animation::update(float delta) {
    cDura += delta;
    
    if(cDura >= duration) {
        currentFrame++;
        cDura = 0;
        if(currentFrame == maxFrames)
            currentFrame = 0; // from beginning, nobackward loop here
    }
}

void Animation::restart() {
    cDura = 0;
    finish = false;
}


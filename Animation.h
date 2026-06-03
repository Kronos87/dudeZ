#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "SDL.h"
#include "Machine.h"
#include "Texture.h"

class Animation {
private:
    SDL_Rect *frameClips;
    Texture* texture;
    int currentFrame;
    int duration;
    float cDura;
    int maxFrames;
    int width;
    SDL_Rect* rectPBP;
    bool loopBack;
    bool finish;
    
    
public:
    Animation(Texture* tex, int width, int durationSpeed);
    Animation(Texture* tex, int frames, int tileWidth, int durationSpeed);
    ~Animation();
    
    void renderPBP(Machine* machine, int x, int y);
    void render(Machine* machine, int x, int y);
    
    void updatePBP(float delta);
    void update(float delta);
    
    void restart();
    
};

#endif
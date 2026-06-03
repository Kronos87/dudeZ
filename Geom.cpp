#include "Geom.h"
#include "SDL.h"

//// Vector2F ////

Vector2F::Vector2F() {
    x = 0;
    y = 0;
}

Vector2F::Vector2F(float cx, float cy) {
    x = cx;
    y = cy;
}


//// RectF ////

RectF::RectF(float nx, float ny, float nw, float nh) : x(nx), y(ny), w(nw), h(nh) {
    sdlRect = new SDL_Rect();
    update();
}

RectF::~RectF() {
    delete sdlRect;
}

void RectF::update() {
    sdlRect->x = x;
    sdlRect->y = y;
    sdlRect->w = w;
    sdlRect->h = h;
}

SDL_Rect* RectF::getSDL_Rect() {
    update();
    return sdlRect;
}

void RectF::set(int nx, int ny) {
    x = nx;
    y = ny;
    update();
}

void RectF::set(int nx, int ny, int nw, int nh) {
    x = nx;
    y = ny;
    w = nw;
    h = nh;
    update();
}

bool RectF::contains(float ox, float oy) {
    update();
    if(ox >= x && ox <= x + w && oy >= y && oy <= y + h)
        return true;
    else
        return false;
}

bool RectF::intersects(RectF *other) {
    update();
    return (x < other->x + other->w && x + w > other-> x && y < other-> y + other-> h && y + h > other->y);
}

void RectF::fill(SDL_Renderer* gRenderer) {
    update();
    SDL_RenderFillRect(gRenderer, sdlRect);
}

void RectF::draw(SDL_Renderer* gRenderer) {
    update();
    SDL_RenderDrawRect(gRenderer, sdlRect);
}


#ifndef GEOM_H_
#define GEOM_H_

#include "SDL.h"
#include <cmath>

class Vector2F {
public:
    float x, y;
    
    Vector2F();
    Vector2F(float cx, float cy);
    
    // static methods
    
    static Vector2F* add(Vector2F* a, Vector2F* b) {
        Vector2F* newVec = new Vector2F();
        
        newVec->x = a->x + b->x;
        newVec->y = a->y + b->y;
        
        return newVec;
    }
    
    static Vector2F* sub(Vector2F* a, Vector2F* b) {
        Vector2F* newVec = new Vector2F();
        
        newVec->x = a->x - b->x;
        newVec->y = a->y - b->y;
        
        return newVec;
    }
    
    static Vector2F* mul(Vector2F* a, float scalar) {
        Vector2F* newVec = new Vector2F();
        
        newVec->x = a->x * scalar;
        newVec->y = a->y * scalar;
        
        return newVec;
    }
    
    static Vector2F* div(Vector2F* a, float scalar) {
        Vector2F* newVec = new Vector2F();
        
        newVec->x = a->x / scalar;
        newVec->y = a->y / scalar;
        
        return newVec;
    }
    
    //
    
    /**
     * A copy of Vector on the heap (newd)
     */
    Vector2F* copy() {
        return new Vector2F(x, y);
    }
    
    Vector2F* add(Vector2F* other) {
        x += other->x;
        y += other->y;
        
        return this;
    }
    
    Vector2F* sub(Vector2F* other) {
        x -= other->x;
        y -= other->y;
        
        return this;
    }
    
    Vector2F* mul(float scalar) {
        x *= scalar;
        y *= scalar;
        
        return this;
    }
    
    Vector2F* div(float scalar) {
        x /= scalar;
        y /= scalar;
        
        return this;
    }
    
    Vector2F* normalize() {
        float l = mag();
        if(l != 0)
            div(l);
        
        return this;
    }
    
    float mag() {
        return sqrt(magSq());
    }
    
    float magSq() {
        return x*x + y*y;
    }
    
    void limit(float max) {
        float msq = magSq();
        if(msq > max * max) {
            div(sqrt(msq));
            mul(max);
        }
    }
    
    void setMag(float mag) {
        normalize();
        mul(mag);
    }
};

class RectF {
    
protected:
    SDL_Rect* sdlRect;
    void update();
    
public:
    float x;
    float y;
    float w;
    float h;
    
    RectF(float nx, float ny, float nw, float nh);
    virtual ~RectF();
    
    bool contains(float ox, float oy);
    
    bool intersects(RectF *other);
    
    void fill(SDL_Renderer* gRenderer);
    void draw(SDL_Renderer* gRenderer);
    
    void set(int x, int y);
    void set(int x, int y, int w, int h);
    
    SDL_Rect* getSDL_Rect();
};


#endif
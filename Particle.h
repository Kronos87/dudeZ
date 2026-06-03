#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Machine.h"
#include "Util.h"
#include "SDL.h"
#include "Texture.h"

#include "Geom.h"

#include <vector>


class Particle {
private:
    Vector2F* location;
    Vector2F* velocity;
    Vector2F* acceleration;
    Vector2F* accStd;
    
    SDL_Rect* rect;
    Texture* texture;

public:
    
    float life, lifeMax;
    float accX, accY;
    
    
    Particle(SDL_Renderer* crenderer, int cx, int cy, int cw, int ch, float clife, float caccX, float caccY, SDL_Color* color) : life(clife) {
        rect = new SDL_Rect;
        rect->x = cx;
        rect->y = cy;
        rect->w = cw;
        rect->h = ch;
        
        location = new Vector2F(cx, cy);
        velocity = new Vector2F(float(Util::rndNo(-40, 40)) / 10.0f, float(Util::rndNo(-40, 0)) / 10.0f);
        acceleration = new Vector2F(caccX, caccY);
        accStd = new Vector2F(caccX, caccY);
        
        texture = new Texture(Texture::createTexture(crenderer, cw, ch));
        texture->setBlendColor(color);
        
        lifeMax = clife;
    }
    
    void applyForce(Vector2F* force) {
        Vector2F* f = force->copy();
        //f->div(mass);
        acceleration->add(f);
        
        delete f;
    }
    
    void update(Machine* machine) {
        acceleration->add(accStd);
        acceleration->mul(machine->getDeltaTime());
        
        velocity->add(acceleration);
        location->add(velocity);
        rect->x = location->x;
        rect->y = location->y;
        
        acceleration->mul(0);
        
        life -= machine->getDeltaTime();
        
        texture->setAlpha(life/lifeMax * 255.0f);
    }
    
    void render(Machine* machine) {
        texture->render(machine->getRenderer(), rect);
    }
    
    bool isDead() {
        return (life < 0);
    }
    
    ~Particle() {
        delete velocity;
        delete acceleration;
        delete location;
        delete accStd;
        
        delete texture;
        delete rect;
    }
    
};


class ParticleEmitter {
private:
    SDL_Renderer* renderer;
    int size;
    int particleCount;
    float life;
    float gravityX, gravityY;
    float spread;
    
    bool looping;
    bool finished;
    
    SDL_Color* color;
    std::vector<Particle*> particles;
    
    
    void born() {
        particles.push_back(new Particle(renderer, x, y, size, size, life, accX, accY, color));
    }
    
public:
    int x, y;
    float accX, accY;
    
    ParticleEmitter(SDL_Renderer* crenderer, int cx, int cy, int csize, int cparticleCount, float clife, float caccX, float caccY, SDL_Color* ccolor, bool clooping) : renderer(crenderer), x(cx), y(cy), size(csize), particleCount(cparticleCount), life(clife), accX(caccX), accY(caccY), color(ccolor), looping(clooping) {
        for(int i=0; i < particleCount; i++) {
            born();
        }
    }
    
    ~ParticleEmitter() {
        for(int i=0; i < particles.size(); i++) {
            delete particles[i];
        }
        
        particles.clear();
    }
    
    void applyForce(Vector2F* force) {
        for(int i=0; i < particles.size(); i++) {
            particles[i]->applyForce(force);
        }
    }
    
    void update(Machine* machine) {
        for(int i=0; i < particles.size(); i++) {
            particles[i]->update(machine);
            
            if(particles[i]->isDead()) {
                delete particles[i];
                particles.erase(particles.begin() + i);
                
                //new born
                if(looping)
                    born();
            }
        }
    }
    
    void render(int cx, int cy, Machine* machine) {
        x = cx;
        y = cy;
        
        
        for(int i=0; i < particles.size(); i++) {
            particles[i]->render(machine);
        }
    }
    
};


#endif

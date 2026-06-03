#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "SDL.h"

#include <string>


class Texture {
private:
    SDL_Texture* texture;
    int width, height;
    
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  static const uint32_t rmask = 0xff000000;
  static const uint32_t gmask = 0x00ff0000;
  static const uint32_t bmask = 0x0000ff00;
  static const uint32_t amask = 0x000000ff;
#else
  static const uint32_t rmask = 0x000000ff;
  static const uint32_t gmask = 0x0000ff00;
  static const uint32_t bmask = 0x00ff0000;
  static const uint32_t amask = 0xff000000;
#endif
    
public:
    Texture(SDL_Texture* ctexture);
    Texture(SDL_Renderer* gRenderer, std::string path);
    ~Texture();
    
    void render(SDL_Renderer* gRenderer, SDL_Rect *rect);
    
    /**
     * Color 0-255
     */
    void setBlendColor(int r, int g, int b, int a);
    void setBlendColor(SDL_Color* color);
    
    void setAlpha(int a);
    
    int getWidth();
    int getHeight();
    
    SDL_Texture* getSDL_Texture();
    
    static SDL_Texture* createTexture(SDL_Renderer* renderer, int width, int height) {
        SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 8, 0, 0, 0, 0);
        SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_FreeSurface(surface);
        
        return text;
    }
    
    
};


#endif

//
//  Texture.cpp
//  DudeZ
//
//  Created by Benjamin Besli on 11.03.15.
//
//

#include "SDL.h"
#include "SDL_image.h"

#include "Texture.h"

Texture::Texture(SDL_Texture* ctexture) : texture(ctexture) {
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    width = w;
    height = h;
}

Texture::Texture(SDL_Renderer* gRenderer, std::string path) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    
    texture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    
    width = loadedSurface->w;
    height = loadedSurface->h;
    
    SDL_FreeSurface(loadedSurface);
}

Texture::~Texture() {
    SDL_DestroyTexture(texture);
}

void Texture::render(SDL_Renderer* gRenderer, SDL_Rect *rect) {
    SDL_RenderCopy(gRenderer, texture, NULL, rect);
}

void Texture::setAlpha(int a) {
    SDL_SetTextureAlphaMod(texture, a);
}

void Texture::setBlendColor(int r, int g, int b, int a) {
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture, a);
    SDL_SetTextureColorMod(texture, r, g, b);
}

void Texture::setBlendColor(SDL_Color* color) {
    setBlendColor(color->r, color->g, color->b, color->a);
}

int Texture::getWidth() {
    return width;
}

int Texture::getHeight() {
    return height;
}

SDL_Texture* Texture::getSDL_Texture() {
    return texture;
}
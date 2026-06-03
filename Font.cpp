#include "SDL.h"
#include "SDL_ttf.h"
#include "Font.h"
#include <string>


Font::Font(std::string fontPath, int fontSize, int r, int g, int b) {
	font = TTF_OpenFont(fontPath.c_str(), fontSize);
    
    TTF_SetFontHinting(font, TTF_HINTING_NORMAL);
    
    setFontColor(r, g, b);
    
    font_colorOutline.r = 80;
    font_colorOutline.g = 80;
    font_colorOutline.b = 80;
}

Font::Font(std::string fontPath, int fontSize, std::string text, SDL_Renderer* gRenderer, int r, int g, int b) : Font(fontPath, fontSize, r, g, b) {
	
	m_Surface = TTF_RenderText_Blended(font, text.c_str(), font_color);
	m_Texture = SDL_CreateTextureFromSurface(gRenderer, m_Surface);
	
	SDL_QueryTexture(m_Texture, NULL, NULL, &m_Dst.w, &m_Dst.h);

	width = m_Dst.w;
	height = m_Dst.h;
	
	SDL_FreeSurface(m_Surface);
}

Font::~Font() {
    if(m_Texture == nullptr)
        SDL_DestroyTexture(m_Texture);
    if(m_Surface == nullptr)
        SDL_FreeSurface(m_Surface);
    
    TTF_CloseFont(font);
}

void Font::renderFont(SDL_Renderer* gRenderer, int nx, int ny) {
	m_Dst.x = nx;
	m_Dst.y = ny;
	
	SDL_RenderCopy(gRenderer, m_Texture, NULL, &m_Dst);
}

void Font::renderFont(SDL_Renderer* gRenderer, std::string text, int nx, int ny) {
	m_Surface = TTF_RenderText_Blended(font, text.c_str(), font_color);
	SDL_Texture *texText = SDL_CreateTextureFromSurface(gRenderer, m_Surface);
	
	SDL_Rect dst;
	
	SDL_QueryTexture(texText, NULL, NULL, &dst.w, &dst.h);
	dst.x = nx;
	dst.y = ny;
	
	width = dst.w;
	height = dst.h;
	
	SDL_FreeSurface(m_Surface);
	
	SDL_RenderCopy(gRenderer, texText, NULL, &dst);
	
	SDL_DestroyTexture(texText);
}

void Font::renderFontOutlined(SDL_Renderer* gRenderer, std::string text, int nx, int ny, int outline, int alpha) {
	SDL_Surface* fontSurface;
	SDL_Rect dst;
	SDL_Texture *texText;
	
	TTF_SetFontOutline(font, outline);
	
	fontSurface = TTF_RenderText_Blended(font, text.c_str(), font_colorOutline);
	texText = SDL_CreateTextureFromSurface(gRenderer, fontSurface);
	
	SDL_SetTextureBlendMode(texText, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(texText, alpha);
	
	SDL_QueryTexture(texText, NULL, NULL, &dst.w, &dst.h);
	dst.x = nx - outline;
	dst.y = ny - outline;
	
	width = dst.w;
	height = dst.h;
	
	SDL_RenderCopy(gRenderer, texText, NULL, &dst);
	
	// second
	
	TTF_SetFontOutline(font, 0);
	
	fontSurface = TTF_RenderText_Blended(font, text.c_str(), font_color);
	texText = SDL_CreateTextureFromSurface(gRenderer, fontSurface);
	
	SDL_SetTextureBlendMode(texText, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(texText, 255);
	
	SDL_QueryTexture(texText, NULL, NULL, &dst.w, &dst.h);
	dst.x = nx;
	dst.y = ny;
	
	width = dst.w;
	height = dst.h;
	
	SDL_RenderCopy(gRenderer, texText, NULL, &dst);
	
	SDL_FreeSurface(fontSurface);
	SDL_DestroyTexture(texText);
}

void Font::setFontColor(int r, int g, int b) {
    font_color.r = r;
    font_color.g = g;
    font_color.b = b;
}

int Font::getWidth() {
	return width;
}

int Font::getHeight() {
	return height;
}
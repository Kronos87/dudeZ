#ifndef FONT_H_
#define FONT_H_

#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

class Font {
	
	private:
		TTF_Font* font = nullptr;
		SDL_Color font_color;
		SDL_Color font_colorOutline;
		
		/* for second Constructor */
        SDL_Surface* m_Surface = nullptr;
		SDL_Texture* m_Texture = nullptr;
		SDL_Rect m_Dst;
		int width, height;
		
	public:
		Font(std::string fontPath, int fontSize, int r, int g, int b);
		Font(std::string fontPath, int fontSize, std::string text, SDL_Renderer* gRenderer, int r, int g, int b);
		~Font();
		
		
		void renderFontOutlined(SDL_Renderer* gRenderer, std::string text, int nx, int ny, int outline, int alpha);
		void renderFont(SDL_Renderer* gRenderer, std::string text, int nx, int ny);
		void renderFont(SDL_Renderer* gRenderer, int nx, int ny);
		void setFontColor(int r, int g, int b);
		
		int getWidth();
		int getHeight();
};

#endif
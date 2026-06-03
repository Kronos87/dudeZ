#ifndef INTROSTATE_H_
#define INTROSTATE_H_

#include "Machine.h"
#include "Font.h"

class IntroState : public GameState {

	private:
		static IntroState instance;
    
        SDL_Rect* bgrect;
        SDL_Rect* leftrect;
        SDL_Color* bgcolor;
    
        Font* font;
    
        float duration;
	
	public:
	
		void pause();
		void resume();
	
		void init(Machine* machine);
        void update(Machine* machine);
		void render(Machine* machine);
		void handleEvents(Machine* machine);
		void cleanUp();
		
		static IntroState* Instance() {
			return &instance;
		}
	
	protected:
		IntroState() {}

};

#endif
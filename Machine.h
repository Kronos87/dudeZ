#ifndef MACHINE_H_
#define MACHINE_H_

#include "SDL.h"

#include <vector>
#include <string>

class GameState;

class Machine {
	private:
		std::vector<GameState*> states;
		SDL_Window* gWindow = nullptr;
		SDL_Renderer* gRenderer = nullptr;
		SDL_Event* gEvent = nullptr;
		
        bool running;
    
		
	public:
		static int WIDTH;
		static int HEIGHT;
        static int ACTUAL_WIDTH;
        static int ACTUAL_HEIGHT;
        static int CENTER_X;
        static int CENTER_Y;
        static float RATIO;
    
        float deltaTime = 0;
        int thisTime = 0;
        int lastTime = 0;
		
		Machine(std::string title, int width, int height);
		~Machine();
		
		void start();
		
		void changeState(GameState* state);
		void pushState(GameState* state);
		void popState();
		
		void quit();
		
		void setColor(SDL_Color* color);
        void setColor(int r, int g, int b, int a);
		
		float getDeltaTime();
		
		SDL_Window* getWindow();
		SDL_Renderer* getRenderer();
		SDL_Event* getEvent();
    
        void setRunning(bool crunning);
    
        std::vector<GameState*> *getStates() {
            return &states;
        }
};

class GameState {
    
	public:
        bool paused;
		
        virtual void pause() = 0;
		virtual void resume() = 0;
	
		virtual void init(Machine* machine) = 0;
        virtual void update(Machine* machine) = 0;
		virtual void render(Machine* machine) = 0;
		virtual void handleEvents(Machine* machine) = 0;
		virtual void cleanUp() = 0;
		
		void changeState(Machine* machine, GameState* state) {
			machine->changeState(state);
		}
		
	protected:
        GameState() { paused = false; };
        virtual ~GameState() {};
};

#endif
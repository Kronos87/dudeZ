#include "Machine.h"

#include "SDL.h"

#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Playstate.h"


int Machine::WIDTH;
int Machine::HEIGHT;

int Machine::ACTUAL_WIDTH;
int Machine::ACTUAL_HEIGHT;

int Machine::CENTER_X;
int Machine::CENTER_Y;
float Machine::RATIO;


SDL_Renderer* Machine::getRenderer() {
	return gRenderer;
}

SDL_Event* Machine::getEvent() {
	return gEvent;
}

SDL_Window* Machine::getWindow() {
	return gWindow;
}

void Machine::setRunning(bool crunning) {
    running = crunning;
}

Machine::Machine(std::string title, int width, int height) {
	WIDTH = width;
	HEIGHT = height;
    
    CENTER_X = width / 2;
    CENTER_Y = height / 2;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	
	gWindow = SDL_CreateWindow(title.c_str(), 0, 0, width, height, SDL_WINDOW_BORDERLESS);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	SDL_RenderSetLogicalSize(gRenderer, width, height);
	
    
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags)) {
		//error
	}
	TTF_Init();
    
    
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    
    printf("display w: %d, h: %d\n", current.w, current.h);
    
    ACTUAL_WIDTH = current.w;
    ACTUAL_HEIGHT = current.h;
    
    RATIO = (float)current.w / (float)current.h;
}

void Machine::setColor(SDL_Color* color) {
	SDL_SetRenderDrawColor(gRenderer, color->r, color->g, color->b, color->a);
}

void Machine::setColor(int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(gRenderer, r, g, b, a);
}

float Machine::getDeltaTime() {
	return deltaTime;
}

void Machine::changeState(GameState* state) {
	while (!states.empty()) {
        states.back()->pause();
		states.pop_back();
	}
	
	states.push_back(state);
	states.back()->init(this);
}

/*
void Machine::pushState(GameState* state) {
	if (!states.empty()) {
		states.back()->pause();
	}

	states.push_back(state);
	states.back()->init(this);
}

void Machine::popState() {
	if (!states.empty()) {
		states.back()->cleanUp();
		states.pop_back();
	}

	if (!states.empty()) {
		states.back()->resume();
	}
}
 */

int SDLCALL myEventFilter(void *userdata, SDL_Event* event) {
    if (event->type == SDL_APP_WILLENTERBACKGROUND) {
        if (!(*(std::vector<GameState*>*)userdata).empty()) {
            (*(std::vector<GameState*>*)userdata).back()->pause();
            printf("ab in den hintergrund\n");
        }
    } else if(event->type == SDL_APP_WILLENTERFOREGROUND) {
        if (!(*(std::vector<GameState*>*)userdata).empty()) {
            (*(std::vector<GameState*>*)userdata).back()->resume();
            printf("ab in den vordergrund\n");
        }
    }
    
    return 1;
}


void renderiOS(void* param) {
    Machine* machine = (Machine*)param;
    
    machine->thisTime = SDL_GetTicks();
    machine->deltaTime = (float)(machine->thisTime - machine->lastTime);
    machine->lastTime = machine->thisTime;
    
    if (!machine->getStates()->empty()) {
        machine->getStates()->back()->update(machine);
    }
        
    
    SDL_RenderClear(machine->getRenderer());

    
    if (!machine->getStates()->empty())
        machine->getStates()->back()->render(machine);
    
    SDL_RenderPresent(machine->getRenderer());
    
    SDL_Delay(1);
}

void Machine::start() {
	//Mainloop
	
	gEvent = new SDL_Event();
    
    SDL_AddEventWatch(myEventFilter, &states);
    SDL_iPhoneSetAnimationCallback(gWindow, 1, renderiOS, this);
    
    running = true;
	
	while(running) {
        //loop
        /*
         */
        while(SDL_PollEvent(gEvent) != 0) {
            if(gEvent->type == SDL_QUIT) {
                running = false;
        
            } else {
                if (!states.empty())
                    states.back()->handleEvents(this);
         
            }
        }
  
	}
	
	//CleanUP
	while (!states.empty()) {
		states.back()->cleanUp();
		states.pop_back();
	}
	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	
	delete gEvent;
	
    
	TTF_Quit();
	IMG_Quit();
	
    SDL_Quit();
}

void Machine::quit() {
	running = false;
}

Machine::~Machine() {
	
}


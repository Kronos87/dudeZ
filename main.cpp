#include "Machine.h"
#include "Introstate.h"

#include "SDL.h"

int main(int argc, char* argv[]) {
    
	Machine* machine = new Machine("DudeZ", 480, 320);
	
	machine->changeState(IntroState::Instance());
	machine->start();
	
	
	return 0;
}
#include "Machine.h"
#include "Playstate.h"
#include "AStar.h"
#include "Util.h"
#include "Gridelement.h"

#include "Player.h"
#include "Particle.h"
#include "Font.h"
#include "Animation.h"
#include "Texture.h"
#include "Geom.h"
#include "Zombie.h"
#include "Survivor.h"

#include <sstream>
#include <deque>
#include <vector>

#include "Mover.h"

PlayState PlayState::instance;

//Textures
Texture* texGrass;
Texture* texPause;
Texture* texItemButton;
Texture* texPlayer;
Texture* texTree;
Texture* texZombie;
Texture* texHouse;
Texture* texSurvivorF;
Texture* texSurvivorM;

//Animations
Animation* aniPause;

GridElement** grid;
int gridSize = 20;
SDL_Rect* rect = nullptr;

//Buttons
RectF* btnPause;
RectF* btnItm0;

//Testzone

std::vector<Mover*> movers;
Vector2F wind {0.5, 0};


int gmx, gmy;

Font* font;

ParticleEmitter* partEffect;
SDL_Color partColor {167, 44, 55, 255};

Player* player;
int points = 0;

RectF* rectHouse;

std::vector<Zombie*> zombies;
std::vector<Survivor*> survivors;


void PlayState::pause() {
    paused = true;
}

void PlayState::resume() {
    paused = false;
}


void generate(int tx, int ty) {

    //int oldx = player->x / gridSize;
    //int oldy = player->y / gridSize;
    //grid[oldx][oldy].type = &GridElementType::PLAYER;
    
    player->findPath(tx, ty);

    //grid[oldx][oldy].type = &GridElementType::GROUND;
    
    
    /*
    for (std::deque<Waypoint*>::iterator it = bestway.begin(); it != bestway.end(); ++it)
        printf("bwX: %d bwY: %d\n", (*it)->x, (*it)->y);
     */
}

void PlayState::init(Machine* machine) {
    srand((unsigned)time(NULL));
    
    rect = new SDL_Rect;
    rect->w = gridSize;
    rect->h = gridSize;
    
    grid = new GridElement*[Machine::WIDTH / gridSize];
    
    for(int i = 0; i < Machine::WIDTH / gridSize; i++)
        grid[i] = new GridElement[Machine::HEIGHT / gridSize];
    
    //Set Ground aka blocking false
    for(int i=0;i<Machine::WIDTH / gridSize; i++)
        for(int j=0;j<Machine::HEIGHT / gridSize; j++) {
            grid[i][j].type = &GridElementType::GROUND;
        }
    
    
    for(int i=0;i<25;i++) {
        int rx = Util::rndNo(0, Machine::WIDTH / gridSize - 1);
        int ry = Util::rndNo(0, Machine::HEIGHT / gridSize - 1);
        grid[rx][ry].type = &GridElementType::TREE;
    }
    
    //HOUSE
    grid[10][5].type = &GridElementType::HOUSE;
    rectHouse = new RectF(10 * gridSize, 5 * gridSize, gridSize, gridSize);
    
    partEffect = new ParticleEmitter(machine->getRenderer(), 300, 33, 5, 250, 1400, 0, 0.008f, &partColor, true);
    
    //Textures
    texGrass = new Texture(machine->getRenderer(), "grass.png");
    texPause = new Texture(machine->getRenderer(), "pause.png");
    texItemButton = new Texture(machine->getRenderer(), "itemButton.png");
    texPlayer = new Texture(machine->getRenderer(), "player.png");
    texTree = new Texture(machine->getRenderer(), "tree.png");
    texZombie = new Texture(machine->getRenderer(), "zombie.png");
    texHouse = new Texture(machine->getRenderer(), "house.png");
    texSurvivorF = new Texture(machine->getRenderer(), "survivor_f.png");
    texSurvivorM = new Texture(machine->getRenderer(), "survivor_m.png");
    
    //Animations
    aniPause = new Animation(texPause, 15, 10);
    
    //Buttons
    btnPause = new RectF(5, 5, 15, 21);
    btnItm0 = new RectF(5, Machine::HEIGHT - 5 - texItemButton->getHeight(), texItemButton->getWidth(), texItemButton->getHeight());
    
    //Font
    font = new Font("04B_03.ttf", 20, 255, 255, 255);
    
    player = new Player(machine, &grid, gridSize);
    player->x = 8 * gridSize;
    player->y = 8 * gridSize;
    
    player->setTexture(texPlayer);
    
    
    for(int i=0; i < 5; i++) {
        Zombie* zombie = new Zombie(machine, &grid, gridSize);
        zombie->setTexture(texZombie);
        zombie->findPath(Util::rndNo(0, Machine::WIDTH / gridSize), Util::rndNo(0, Machine::HEIGHT / gridSize));
        zombies.push_back(zombie);
    }
    
    for(int i=0; i < 4; i++) {
        Survivor* survivor = new Survivor(machine, &grid, gridSize);
        survivor->setTexture(Util::rndBool() ? texSurvivorF : texSurvivorM);
        //survivor->findPath(Util::rndNo(0, Machine::WIDTH / gridSize), Util::rndNo(0, Machine::HEIGHT / gridSize));
        survivor->x = Util::rndNo(0, Machine::WIDTH / gridSize) * gridSize;
        survivor->y = Util::rndNo(0, Machine::HEIGHT / gridSize) * gridSize;
        survivors.push_back(survivor);
    }
    
    
    //generate method is debug
    generate(11, 11);
    
    
    ////// TEEST
    for(int i = 0; i < 10; i++)
        movers.push_back(new Mover(0, 0, Util::rndNo(1, 20)));
    
}

void alarmZombie(Zombie* z, Unit* u) {
    if(!z->alarmed) {
        z->findPath(u->x / gridSize, u->y / gridSize);
        z->alarmed = true;
    }
}

void alarmSurvivor(Survivor* s, Unit* u) {
    if(!s->alarmed) {
        s->findPath(u->x / gridSize, u->y / gridSize);
        s->alarmed = true;
    }
}

void PlayState::update(Machine *machine) {
    if(!paused) {
        player->update(machine);
        //partEffect->update(machine);
        
        
        for(int i=0; i < zombies.size(); i++) {
            if(zombies[i]->alarmBox->intersects(player->alarmBox)) {
                alarmZombie(zombies[i], player);
            }
            
            for(int j=0; j < survivors.size(); j++) {
                if(zombies[i]->alarmBox->intersects(survivors[j]->alarmBox)) {
                    alarmZombie(zombies[i], survivors[j]);
                }
            }
            
            
            zombies[i]->update(machine);
        }
        
        for(int i=0; i < survivors.size(); i++) {
            
            if(!survivors[i]->counted && survivors[i]->intersects(rectHouse)) {
                points += 100;
                survivors[i]->counted = true;
            }
            
            if(survivors[i]->alarmBox->intersects(player->alarmBox)) {
                alarmSurvivor(survivors[i], player);
            }
            
            if(survivors[i]->intersects(player)) {
                survivors[i]->stop();
            }
            
            survivors[i]->update(machine);
        }
        /*
         for(int i=0; i < movers.size(); i++) {
         movers[i]->applyForce(&wind);
         movers[i]->update(machine, gmx, gmy);
         }
         */
    } // Ende paused
}

void PlayState::render(Machine* machine) {

    
    //Render Grid
    for(int i=0;i<Machine::WIDTH / gridSize; i++) {
        for(int j=0;j<Machine::HEIGHT / gridSize; j++) {
            
            /*
            if(!grid[i][j].type->blocking){
                machine->setColor(0, 222, 22, 255);
            } else {
            }
            */
            rect->x = i * gridSize;
            rect->y = j * gridSize;
            
            //machine->setColor(255, 255, 255, 0);
            
            texGrass->render(machine->getRenderer(), rect);
            
            if(grid[i][j].type == &GridElementType::GROUND) {
                
            } else if(grid[i][j].type == &GridElementType::TREE){
                texTree->render(machine->getRenderer(), rect);
            }
            
        }
    }
    
    for(int i=0; i < zombies.size(); i++)
        zombies[i]->renderPath(machine);
    
    for(int i=0; i < survivors.size(); i++)
        survivors[i]->renderPath(machine);
    
    player->renderPath(machine);
    
    for(int i=0;i<Machine::WIDTH / gridSize; i++) {
        for(int j=0;j<Machine::HEIGHT / gridSize; j++) {
            rect->x = i * gridSize;
            rect->y = j * gridSize;
            
            if(grid[i][j].type == &GridElementType::HOUSE){
                texHouse->render(machine->getRenderer(), rect);
            }
        }
    }
    
    for(int i=0; i < zombies.size(); i++)
        zombies[i]->render(machine);
    
    for(int i=0; i < survivors.size(); i++)
        survivors[i]->render(machine);
    
    player->render(machine);
    //partEffect->render(player->x, player->y, machine);
    
    aniPause->updatePBP(machine->getDeltaTime());
    aniPause->renderPBP(machine, 5, 5);
    
    std::stringstream sstr;
    
    sstr << points; // << machine->getDeltaTime();
    font->renderFontOutlined(machine->getRenderer(), sstr.str(), Machine::CENTER_X, 5, 2, 200);
    //texItemButton->render(machine->getRenderer(), btnItm0->getSDL_Rect());
    
    /*
    for(int i=0; i < movers.size(); i++)
        movers[i]->render(machine);
     */
}



void PlayState::handleEvents(Machine* machine) {
    
    if(machine->getEvent()->type == SDL_MOUSEBUTTONDOWN) {
        
        int mx, my;
        SDL_GetMouseState(&mx, &my);
        
        mx *= float(Machine::WIDTH) / float(Machine::ACTUAL_WIDTH);
        my *= float(Machine::HEIGHT) / float(Machine::ACTUAL_HEIGHT);
        
        int gx, gy;
        gx = mx / gridSize;
        gy = my / gridSize;
            
        printf("mx: %d my: %d\n", mx, my);
        
        //TODO put btns in vector and iterate through
        if(btnPause->contains(mx, my)) {
            aniPause->restart();
            paused = !paused;
            return;
        }
        
        generate(gx, gy);
        
        
    } else if(machine->getEvent()->type == SDL_MOUSEMOTION) {

        SDL_GetMouseState(&gmx, &gmy);
        
        gmx *= float(Machine::WIDTH) / float(Machine::ACTUAL_WIDTH);
        gmy *= float(Machine::HEIGHT) / float(Machine::ACTUAL_HEIGHT);
        
        
    }
}

void PlayState::cleanUp() {
    delete[] grid;
    
    delete texGrass;
    delete rect;
    delete player;
    
    delete partEffect;
}
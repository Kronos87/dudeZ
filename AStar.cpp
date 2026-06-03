#include "AStar.h"
#include "Util.h"
#include "Gridelement.h"
#include <vector>

/////////// Waypoint ///////////

Waypoint::Waypoint(int cx, int cy, int ccosts, int cheuristic, Waypoint* cprevious) : x(cx), y(cy), costs(ccosts), heuristic(cheuristic), previous(cprevious) {
    
}

Waypoint::~Waypoint() {
    delete previous;
}

int Waypoint::getCostsTotal() {
    return getCurrentWaycosts() + costs + heuristic;
}

int Waypoint::getCurrentWaycosts() {
    if(previous == nullptr)
        return 0;
    return previous->getCurrentWaycosts() + costs;
}

void Waypoint::setPrevious(Waypoint* nprevious) {
    previous = nprevious;
}

Waypoint* Waypoint::getPrevious() {
    return previous;
}

/////////// Astar ///////////
int counter;

AStar::AStar(int gridSize, int width, int height, GridElement*** cgrid) : grid(cgrid) {
    //TODO relativ unwichtig!
    gridsX = width / gridSize;
    gridsY = height / gridSize;
    
    counter = 0;
}

void AStar::set(int px, int py, int ntx, int nty) {
    x = px;
    y = py;
    tx = ntx;
    ty = nty;
    
    openList.push_back(new Waypoint(px, py, 1, computeHeuristic(px, py), nullptr));
    
    searching = true;
}

AStar::~AStar() {    
    delete finish;
}

int AStar::getFirstBestListEntry(std::vector<Waypoint*>* list) {
    int best = (*list)[0]->getCostsTotal();
    
    for(int i = 0; i < (*list).size(); i++) {
        if((*list)[i]->getCostsTotal() < best) {
            best = (*list)[i]->getCostsTotal();
        }
    }
    
    for(int i = 0; i < list->size(); i++) {
        if((*list)[i]->getCostsTotal() == best) {
            return i;
        }
    }
    
    return 0;
}

bool AStar::isWaypointInList(int nx, int ny, std::vector<Waypoint*>* list) {
    for(int i = 0; i < list->size(); i++) {
        if((*list)[i]->x == nx && (*list)[i]->y == ny) {
            return true;
        }
    }
    return false;
}

int AStar::computeHeuristic(int nx, int ny) {
    int dx = nx - tx;
    if(dx < 0) {
        dx = -dx;
    }
    
    int dy = ny - ty;
    if(dy < 0) {
        dy = -dy;
    }
    
    return dx + dy;
}

void AStar::openListAddHelper(int nx, int ny, Waypoint* previous) {
    if(nx < 0 || ny < 0 || nx >= gridsX || ny >= gridsY) {
        
    } else {
        if(!isWaypointInList(nx, ny, &closedList) && !(*grid)[nx][ny].type->blocking && !isWaypointInList(nx, ny, &openList)) {
            openList.push_back(new Waypoint(nx, ny, 1, computeHeuristic(nx, ny), previous));
        }
    }
}

Waypoint* AStar::astar() {
    int best = getFirstBestListEntry(&openList);
    Waypoint* wp = openList[best];
    closedList.push_back(wp);
    openList.erase(openList.begin() + best);
    
    if(wp->x == tx && wp->y == ty) {
        finish = wp;
        return wp;
    }
    
    //oberhalb
    openListAddHelper(wp->x, wp->y - 1, wp);
    //rechts
    openListAddHelper(wp->x + 1, wp->y, wp);
    //unterhalb
    openListAddHelper(wp->x, wp->y + 1, wp);
    //links
    openListAddHelper(wp->x - 1, wp->y, wp);
    
    return wp;
}

bool AStar::findPath() {
    
    if(counter >= gridsX * gridsY)
        return true;
    
    if(finish != nullptr) {
        searching = false;
    } else if(!openList.empty() && searching == true) {
        astar();
    }
    
    counter++;
    
    return !searching;
}

bool AStar::isSearching() const {
    return searching;
}

Waypoint* AStar::getBestPath() {
    return finish;
}

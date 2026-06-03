#ifndef AStar_H_
#define AStar_H_

#include <vector>
#include "Gridelement.h"

class Waypoint {
private:
    int costs;
    int heuristic;
    
    Waypoint* previous = nullptr;
    
public:
    Waypoint(int cx, int cy, int ccosts, int cheuristic, Waypoint* cprevious);
    ~Waypoint();
    
    int x, y;
    
    int getCostsTotal();
    int getCurrentWaycosts();
    void setPrevious(Waypoint* nprevious);
    Waypoint* getPrevious();
    
};


class AStar {
private:
    //TODO implement heap
    std::vector<Waypoint*> openList;
    std::vector<Waypoint*> closedList;
    
    Waypoint* finish = nullptr;

    bool searching;
    GridElement*** grid;
    int gridsX, gridsY;
    
    int x, y, tx, ty;
    
    int getFirstBestListEntry(std::vector<Waypoint*>* list);
    bool isWaypointInList(int x, int y, std::vector<Waypoint*>* list);
    int computeHeuristic(int px, int py);
    void openListAddHelper(int x, int y, Waypoint* previous);
    Waypoint* astar();
    
public:
    AStar(int gridSize, int width, int height, GridElement*** cgrid);
    ~AStar();
    
    void set(int px, int py, int ntx, int nty);
    
    bool findPath();
    bool isSearching() const;
    
    Waypoint* getBestPath();
    
};

#endif

#ifndef GRIDELEMENT_H_
#define GRIDELEMENT_H_

class GridElementType {
public:
    static GridElementType GROUND;
    static GridElementType TREE;
    static GridElementType HOUSE;
    
    
    static GridElementType BLOCK;
    static GridElementType ZOMBIE;
    static GridElementType PLAYER;
    static GridElementType TARGET;
    
    bool blocking;
    
private:
    GridElementType(bool cblocking): blocking(cblocking) { }
};


class GridElement {
private:
    
public:
    GridElementType* type;
    
    GridElement() { }
};

#endif /* defined(GRIDELEMENT_H_) */
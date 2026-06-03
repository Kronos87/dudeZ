#include "Gridelement.h"

GridElementType GridElementType::GROUND = GridElementType(false);
GridElementType GridElementType::TREE = GridElementType(true);
GridElementType GridElementType::HOUSE = GridElementType(false);

GridElementType GridElementType::BLOCK = GridElementType(true);
GridElementType GridElementType::PLAYER = GridElementType(false);
GridElementType GridElementType::TARGET = GridElementType(false);
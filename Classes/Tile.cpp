/*
 * Tile.cpp
 *
 *  Created on: 2013-1-6
 *      Author: sky
 */

#include "Tile.h"

namespace ecoolsoft {

Tile::Tile(CCPoint pos, PlanePart planePart)
:pTile(NULL)
,pos(pos)
,planePart(planePart){

}

Tile::~Tile() {
}

} /* namespace ecoolsoft */

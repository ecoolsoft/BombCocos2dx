/*
 * Tile.h
 *
 *  Created on: 2013-1-6
 *      Author: sky
 */

#ifndef TILE_H_
#define TILE_H_

#include "cocos2d.h"

USING_NS_CC;

namespace ecoolsoft {

enum PlanePart {
	HEAD = 0,
	BODY = 1,
	NONE = 2
};

class Tile : public CCObject{
public:
	Tile(CCPoint pos, PlanePart planePart);
	virtual ~Tile();
	CCPoint pos;
private:
	PlanePart planePart;
	CCSprite *pTile;
};

} /* namespace ecoolsoft */
#endif /* TILE_H_ */

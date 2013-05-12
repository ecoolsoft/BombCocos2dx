/*
 * Plane.h
 *
 *  Created on: 2013-1-5
 *      Author: sky
 */

#ifndef PLANE_H_
#define PLANE_H_

#include "Tile.h"
#include "cocos2d.h"

USING_NS_CC;

namespace ecoolsoft {


enum Direction {
	EAST = 0,
	WEST = 1,
	SOUTH = 2,
	NORTH = 3
};

class Plane : public CCObject{
public:
	Plane();
	Plane(CCPoint pos, Direction direction, bool isVisible=true);
	virtual ~Plane();
	bool contain(CCPoint &pos);
	Tile* getTile(CCPoint &pos);
	void addTiles(Direction &direct);
	bool conflict(Plane* plane);
	void setPPlane(CCSprite *pPlane);
	CCSprite* getPPlane();
	CCPoint pos;
	Direction direction;
	void changePosition(CCPoint& boardPos, float lenPerTile, float scale=1);
	bool containPoint(CCPoint * point);
private:
	CCMutableArray<Tile*> *tileList;
	bool isVisible;
	CCSprite *pPlane;
	//Direction getRotateDirection(Direction direction);
};

} /* namespace ecoolsoft */
#endif /* PLANE_H_ */

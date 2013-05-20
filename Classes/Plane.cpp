/*
 * Plane.cpp
 *
 *  Created on: 2013-1-5
 *      Author: sky
 */

#include "Plane.h"

namespace ecoolsoft {

Plane::Plane() :
		tileList(NULL), pPlane(NULL), isVisible(true) {

}

Plane::~Plane() {
	// TODO Auto-generated destructor stub
}

Plane::Plane(CCPoint pos, Direction direction, bool isVisible) :
		pos(pos), direction(direction) {
	tileList = new CCMutableArray<Tile*>();
	addTiles(direction);
	this->isVisible = isVisible;
}

void Plane::setPPlane(CCSprite *pPlane) {
	this->pPlane = pPlane;
}

CCSprite* Plane::getPPlane() {
	return pPlane;
}

bool Plane::contain(CCPoint &pos) {
	for (int i = 0; i < tileList->count(); i++) {
		Tile *tile = (Tile *) tileList->getObjectAtIndex(i);
		if (CCPoint::CCPointEqualToPoint(ccp(this->pos.x + tile->pos.x, this->pos.y + tile->pos.y), pos)) {
			return true;
		}
	}
	return false;
}

Tile* Plane::getTile(CCPoint &pos) {
	for (int i = 0; i < tileList->count(); i++) {
		Tile *tile = (Tile *) tileList->getObjectAtIndex(i);
		if (CCPoint::CCPointEqualToPoint(tile->pos, pos)) {
			return tile;
		}
	}
	return NULL;
}

void Plane::addTiles(Direction &direct) {
	if (tileList == NULL) {
		tileList = new CCMutableArray<Tile*>();
	}
	switch (direct) {
	case NORTH:
		tileList->addObject(new Tile(ccp(2, 3), HEAD));
		tileList->addObject(new Tile(ccp(0, 2), BODY));
		tileList->addObject(new Tile(ccp(1, 2), BODY));
		tileList->addObject(new Tile(ccp(2, 2), BODY));
		tileList->addObject(new Tile(ccp(3, 2), BODY));
		tileList->addObject(new Tile(ccp(4, 2), BODY));
		tileList->addObject(new Tile(ccp(2, 1), BODY));
		tileList->addObject(new Tile(ccp(1, 0), BODY));
		tileList->addObject(new Tile(ccp(2, 0), BODY));
		tileList->addObject(new Tile(ccp(3, 0), BODY));
		break;
	case SOUTH:
		tileList->addObject(new Tile(ccp(2, 0), HEAD));
		tileList->addObject(new Tile(ccp(0, 1), BODY));
		tileList->addObject(new Tile(ccp(1, 1), BODY));
		tileList->addObject(new Tile(ccp(2, 1), BODY));
		tileList->addObject(new Tile(ccp(3, 1), BODY));
		tileList->addObject(new Tile(ccp(4, 1), BODY));
		tileList->addObject(new Tile(ccp(2, 2), BODY));
		tileList->addObject(new Tile(ccp(1, 3), BODY));
		tileList->addObject(new Tile(ccp(2, 3), BODY));
		tileList->addObject(new Tile(ccp(3, 3), BODY));
		break;
	case EAST:
		tileList->addObject(new Tile(ccp(3, 2), HEAD));
		tileList->addObject(new Tile(ccp(2, 0), BODY));
		tileList->addObject(new Tile(ccp(2, 1), BODY));
		tileList->addObject(new Tile(ccp(2, 2), BODY));
		tileList->addObject(new Tile(ccp(2, 3), BODY));
		tileList->addObject(new Tile(ccp(2, 4), BODY));
		tileList->addObject(new Tile(ccp(1, 2), BODY));
		tileList->addObject(new Tile(ccp(0, 1), BODY));
		tileList->addObject(new Tile(ccp(0, 2), BODY));
		tileList->addObject(new Tile(ccp(0, 3), BODY));
		break;
	case WEST:
		tileList->addObject(new Tile(ccp(0, 2), HEAD));
		tileList->addObject(new Tile(ccp(1, 0), BODY));
		tileList->addObject(new Tile(ccp(1, 1), BODY));
		tileList->addObject(new Tile(ccp(1, 2), BODY));
		tileList->addObject(new Tile(ccp(1, 3), BODY));
		tileList->addObject(new Tile(ccp(1, 4), BODY));
		tileList->addObject(new Tile(ccp(2, 2), BODY));
		tileList->addObject(new Tile(ccp(3, 1), BODY));
		tileList->addObject(new Tile(ccp(3, 2), BODY));
		tileList->addObject(new Tile(ccp(3, 3), BODY));
		break;
	default:
		break;
	}
}

bool Plane::conflict(Plane* plane) {
	for(int i=0; i<tileList->count(); i++) {
		Tile *tile = (Tile *) tileList->getObjectAtIndex(i);
		for(int j=0; j<plane->tileList->count(); j++) {
			Tile *tileOfPlane = (Tile *) plane->tileList->getObjectAtIndex(j);
			//CCLog("in conflict pos.x=%f,pos.y=%f, tile->pos.x=%f, tile->pos.y=%f, plane->pos.x=%f, plane->pos.y=%f, tileOfPlane->pos.x=%f, tileOfPlane->pos.y=%f", this->pos.x, this->pos.y, tile->pos.x, tile->pos.y, plane->pos.x, plane->pos.y, tileOfPlane->pos.x, tileOfPlane->pos.y);
			if(this->pos.x + tile->pos.x == plane->pos.x + tileOfPlane->pos.x && this->pos.y + tile->pos.y == plane->pos.y + tileOfPlane->pos.y ) {
				return true;
			}
		}
	}
	return false;
}

void Plane::changePosition(CCPoint& boardPos, float lenPerTile, float scale) {
	//CCLog("before change:%f,%f", pPlane->getContentSizeInPixels().height, pPlane->getContentSizeInPixels().width);
	//CCLog("before change:%d,%f,%f", isMain, scale, pPlane->getScale());
	//bug fix 解决放大缩小不正确 问题
	if(pPlane->getScale() != 1.0) {
		pPlane->setScale(1);
	} else {
		pPlane->setScale(scale);
	}

	//pPlane->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("cloud1.png"));//not work
	pPlane->setPosition(ccp(boardPos.x + pos.x*lenPerTile, boardPos.y + pos.y*lenPerTile));
	//CCLog("change:%f,%f", pPlane->getContentSizeInPixels().height, pPlane->getContentSizeInPixels().width);
	//CCLog("plane change pos:%f, %f, %f,%f,%f", boardPos.x, pos.x, boardPos.y, pos.y, lenPerTile);
	//CCLog("plane change:%f", pPlane->getScale());
}

}
/* namespace ecoolsoft */

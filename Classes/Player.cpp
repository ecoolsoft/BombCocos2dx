/*
 * Player.cpp
 *
 *  Created on: 2012-12-30
 *      Author: sky
 */

#include "Player.h"

namespace ecoolsoft {

Player::Player()
:planeList(NULL)
,attackedTileList(NULL)
,playerType(MAIN)
,layer(NULL){
}

Player::Player(PlayerType playerType, CCLayer* layer, CCPoint boardPos, float lenPerTile)
:attackedTileList(NULL)
,playerType(playerType)
,layer(layer)
,boardPos(boardPos)
,lenPerTile(lenPerTile){
	planeList = new CCMutableArray<Plane*>(3);
}

Player::~Player() {
	if(planeList) {
		planeList->release();
		planeList = NULL;
	}
	if(attackedTileList) {
		attackedTileList->release();
		attackedTileList = NULL;
	}
}

void Player::setPlayerType(PlayerType &playerType) {
	this->playerType = playerType;
}

bool Player::containPoint(CCPoint* location) {
	if(location != NULL && location->x > boardPos.x && location->x < boardPos.x + Constants::ROW_COUNT * lenPerTile
			&& location->y > boardPos.y && location->y	< boardPos.y + Constants::COLUMN_COUNT * lenPerTile) {
		return true;
	} else {
		return false;
	}
}

//TODO 是否可见、资源图片与主用户和从用户有关
void Player::addPlane(Direction direction, CCPoint pos, std::string strSrc, bool isVisible) {
	Plane *plane = new Plane(pos, direction);

	CCSprite* pPlane;
	switch(direction) {
	case EAST:
		pPlane = CCSprite::spriteWithFile(strSrc.append("plane_east.png").c_str());
		break;
	case WEST:
		pPlane = CCSprite::spriteWithFile(strSrc.append("plane_west.png").c_str());
		break;
	case NORTH:
		pPlane = CCSprite::spriteWithFile(strSrc.append("plane_north.png").c_str());
		break;
	case SOUTH:
		pPlane = CCSprite::spriteWithFile(strSrc.append("plane_south.png").c_str());
		break;
	}
	pPlane->setIsVisible(isVisible);
	pPlane->setAnchorPoint(ccp(0,0));
	pPlane->setPosition(ccp(boardPos.x + pos.x*lenPerTile, boardPos.y + pos.y*lenPerTile));
	layer->addChild(pPlane, 2);
	CCLog("add plane:%f,%f,%f,%f,%f", boardPos.x, boardPos.y, pos.x, pos.y, lenPerTile);
	plane->setPPlane(pPlane);
	planeList->addObject(plane);
}

Plane * Player::genRandomPlane() {
	//随机生成一个方向
	Direction direction = getRandomDirection();

	//随机生成一个位置
	// TODO 写死的数字移走
	CCPoint pos;
	if(direction == NORTH || direction == SOUTH) {
		pos.x = arc4random() % (int)Constants::NORTH_SOURTH_LIMIT_POSITION_X;
		pos.y = arc4random() % (int)Constants::NORTH_SOURTH_LIMIT_POSITION_Y;
	} else {
		pos.x = arc4random() % (int)Constants::WEST_EAST_LIMIT_POSITION_X;
		pos.y = arc4random() % (int)Constants::WEST_EAST_LIMIT_POSITION_Y;
	}
	return new Plane(pos, direction);

}

bool Player::isPlaneConflicts(Plane* p, Plane* ignorePlane) {
	//判断新位置是否与已有的飞机冲突
	for (int i = 0; i < planeList->count(); i++) {
		Plane *plane = (Plane *) planeList->getObjectAtIndex(i);
		//CCLog("isPlaneConflicts x=%f,y=%f", plane->pos.x, plane->pos.y);
		if(plane == ignorePlane) {
			continue;
		}
		if(plane->conflict(p)) {
			return true;
		}
	}
	return false;
}
//TODO 写死的数字修改
bool Player::isPlaneInBoard(CCPoint pos, Direction direct) {
	if(direct == NORTH || direct == SOUTH) {
		return pos.x>=0 && pos.x<=5 && pos.y>=0 && pos.y<=6;
	} else {
		return pos.x>=0 && pos.x<=6 && pos.y>=0 && pos.y<=5;
	}
}
//TODO 崩溃 未重现
bool Player::rotate(Plane *plane) {
	Direction direct = getRotateDirection(plane->direction);
	Plane * newPlane = new Plane(plane->pos, direct);
	if(!isPlaneConflicts(newPlane, plane) && isPlaneInBoard(plane->pos, direct)) {
		newPlane->release();
		CCLog("plane rotate");
		CCPoint pos = plane->pos;
		deletePlane(plane);
		addPlane(direct, pos);
		return true;
	}
	newPlane->release();
	return false;
}
//TODO 崩溃 未重现
bool Player::move(Plane *plane, int x, int y) {
	CCLog("************plane move:%f",plane->pos.x);
	CCPoint pos = ccp(plane->pos.x+x,plane->pos.y+y);
	Direction direct = plane->direction;
	Plane * newPlane = new Plane(pos, direct);
	if(!isPlaneConflicts(newPlane, plane) && isPlaneInBoard(pos, direct)) {
		CCLog("**************delete plane");
		deletePlane(plane);
		addPlane(direct, pos);
		newPlane->release();
		CCLog("**************newPlane release true");
		return true;
	}
	newPlane->release();
	CCLog("***************newPlane release false");
	return false;
}

Direction Player::getRotateDirection(Direction &direction) {
	switch(direction) {
	case EAST:
		return SOUTH;
	case WEST:
		return NORTH;
	case SOUTH:
		return WEST;
	case NORTH:
		return EAST;
	}
}

void Player::addRandomPlane(std::string strSrc, bool isVisible) {
	int i = 0;
	bool isAdded = false;
	while(i<10 && !isAdded) {
		Plane* plane = genRandomPlane();
		if(!isPlaneConflicts(plane)) {
			//添加飞机
			addPlane(plane->direction, plane->pos, strSrc, isVisible);
			isAdded = true;
			CCLog("addRandomPlane_isAdded x=%f,y=%f", plane->pos.x, plane->pos.y);
		}
		i++;
	}
	//遍历的方式来保证可以顺利添加
	if(!isAdded) {	//TODO 写死的数字修改
		Direction direction = getRandomDirection();
		float posX=0.0f, posY=0.0f;
		if(direction == NORTH || direction == SOUTH) {
			posX = 6;
			posY = 7;
		} else {
			posX = 7;
			posY = 6;
		}
		for(int i=0; i<posX; i++) {
			for(int j=0; j<posY; j++) {
				if(!isPlaneConflicts(new Plane(ccp(i,j), direction))) {
					addPlane(direction, ccp(i,j), strSrc, isVisible);	//bugfix 在右侧添加了盟军飞机
					CCLog("addRandomPlane_isAdded_false x=%f,y=%f", i, j);
					return;
				}
			}
		}
	}
}

Direction Player::getRandomDirection() {
	int number = 4;
	int direction = arc4random() % number;
	switch (direction){
	case 0:
		return EAST;
	case 1:
		return WEST;
	case 2:
		return SOUTH;
	default:
		return NORTH;
	}
}

void Player::deletePlane(Plane *plane) {
	//CCLog("*********plane pos x removeChild:%f", plane->pPlane->getPosition().x);
	plane->getPPlane()->retain();
	layer->removeChild(plane->getPPlane(), true);
	//CCLog("*********plane pos x release:%f", plane->pPlane->getPosition().x);
	plane->getPPlane()->release();
	//CCLog("*********plane pos x removeObject:%f", plane->pos.x);
	planeList->removeObject(plane);
}

void Player::deletePlane() {
	deletePlane(planeList->getObjectAtIndex(planeList->count()-1));
}

Plane* Player::getPlane(CCPoint &pos) {
	CCPoint boardPos = convertPos(pos);
	for(int i=0; i<planeList->count(); i++) {
		if(planeList->getObjectAtIndex(i)->contain(boardPos)) {
			return planeList->getObjectAtIndex(i);
		}
	}
}

CCPoint Player::convertPos(CCPoint &pos) {
	int x = (pos.x - boardPos.x)/lenPerTile;
	int y = (pos.y - boardPos.y)/lenPerTile;
	CCLog("convertPos x=%d,y=%d", x, y);
	return ccp(x, y);
}

void Player::changePositon(CCPoint &boardPos, float lenPerTile) {
	float scale = lenPerTile/this->lenPerTile;
	//修改基本信息
	this->boardPos = boardPos;
	this->lenPerTile = lenPerTile;
	//CCLog("boardPos.x:%f, y:%f, lenPerTile:%f", boardPos.x, boardPos.y, lenPerTile);

	//缩放
	for (int i = 0; i < planeList->count(); i++) {
		Plane *plane = (Plane *) planeList->getObjectAtIndex(i);
		CCLog("plane");
		plane->changePosition(boardPos, lenPerTile, scale);
	}
}

bool Player::isPlaneEnough() {
	return (planeList->count() == 3);
}

bool Player::isHavePlane() {
	return (planeList->count() > 0);
}

} /* namespace ecoolsoft */

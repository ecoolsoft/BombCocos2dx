/*
 * Player.h
 *
 *  Created on: 2012-12-30
 *      Author: sky
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "cocos2d.h"
#include "Plane.h"
#include "Constants.h"

USING_NS_CC;

namespace ecoolsoft {

enum PlayerType {
	/*NativePlayer,		//单机用户
	NativeComputer,		//单机电脑
	BluetoothPlayer,	//蓝牙用户
	WifiPlayer,			//wifi用户
	WifiComputer		//wifi电脑（wifi电脑模拟用户）*/
	MAIN = 0,				//主用户
	SUBORDINATE = 1			//从属用户
};

class Player : CCObject {
public:
	Player();
	Player(PlayerType playerType, CCLayer* layer, CCPoint boardPos, float lenPerTile);
	virtual ~Player();
	//void release(void);

	void setPlayerType(PlayerType &playerType);
	/**
	 * 被攻击坐标
	 */
	CCMutableArray<Tile*> *attackedTileList;
	/**
	 * 添加飞机
	 */
	void addPlane(Direction direction, CCPoint pos, std::string strSrc="main_", bool isVisible=true);
	/**
	 * 添加随机飞机
	 */
	void addRandomPlane(std::string strSrc="main_", bool isVisible=true);
	/**
	 * 绘图区域坐标
	 */
	CCPoint boardPos;
	/**
	 * 每个方块的宽度
	 */
	float lenPerTile;
	/**
	 * 删除最后一个添加的飞机
	 */
	void deletePlane();
	/**
	 * 根据位置获得飞机（该位置是全局位置）
	 */
	Plane* getPlane(CCPoint &pos);
	/**
	 * 旋转飞机
	 */
	bool rotate(Plane *plane);
	/**
	 * 移动飞机
	 */
	bool move(Plane *plane, int x, int y);
	/**
	 * 改变位置
	 */
	void changePositon(CCPoint &boardPos, float lenPerTile);
	/**
	 * 是否飞机数已经够了
	 */
	bool isPlaneEnough();
	/**
	  * 是否有飞机
	  */
	bool isHavePlane();
	/**
	 * 是否包括该
	 */
	bool containPoint(CCPoint* location);
private:
	/**
	  * 飞机列表
	  */
	CCMutableArray<Plane*> *planeList;
	/**
	 * 玩家类型
	 */
	PlayerType playerType;
	/**
	 *
	 */
	CCLayer * layer;
	/**
	 * 获取随机方向
	 * TODO 移到合适的位置
	 */
	Direction getRandomDirection();
	Plane * genRandomPlane();
	bool isPlaneConflicts(Plane* plane, Plane* ignorePlane = NULL);
	/**
	 * 屏幕坐标转换为绘图坐标
	 */
	CCPoint convertPos(CCPoint &pos);
	Direction getRotateDirection(Direction &direction);
	void deletePlane(Plane *plane);
	bool isPlaneInBoard(CCPoint pos, Direction direct);
};



} /* namespace ecoolsoft */
#endif /* PLAYER_H_ */

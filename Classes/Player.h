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

USING_NS_CC;

namespace ecoolsoft {

enum PlayerType {
	/*NativePlayer,		//�����û�
	NativeComputer,		//��������
	BluetoothPlayer,	//�����û�
	WifiPlayer,			//wifi�û�
	WifiComputer		//wifi���ԣ�wifi����ģ���û���*/
	MAIN = 0,				//���û�
	SUBORDINATE = 1			//�����û�
};

class Player : CCObject {
public:
	Player();
	Player(PlayerType playerType, CCLayer* layer, CCPoint boardPos, float lenPerTile);
	virtual ~Player();
	//void release(void);

	void setPlayerType(PlayerType &playerType);
	/**
	 * �ɻ��б�
	 */
	CCMutableArray<Plane*> *planeList;
	/**
	 * ����������
	 */
	CCMutableArray<Tile*> *attackedTileList;
	/**
	 * ��ӷɻ�
	 */
	void addPlane(Direction direction, CCPoint pos);
	/**
	 * �������ɻ�
	 */
	void addRandomPlane();
	/**
	 * ��ͼ��������
	 */
	CCPoint boardPos;
	/**
	 * ÿ������Ŀ��
	 */
	float lenPerTile;
	/**
	 * ɾ�����һ����ӵķɻ�
	 */
	void deletePlane();
	/**
	 * ����λ�û�÷ɻ�����λ����ȫ��λ�ã�
	 */
	Plane* getPlane(CCPoint &pos);
	/**
	 *
	 */
	bool rotate(Plane *plane);
	/**
	 *
	 */
	bool move(Plane *plane, int x, int y);
private:
	/**
	 * �������
	 */
	PlayerType playerType;
	/**
	 *
	 */
	CCLayer * layer;
	/**
	 * ��ȡ�������
	 * TODO �Ƶ����ʵ�λ��
	 */
	Direction getRandomDirection();
	Plane * genRandomPlane();
	bool isPlaneConflicts(Plane* plane, Plane* ignorePlane = NULL);
	/**
	 * ��Ļ����ת��Ϊ��ͼ����
	 */
	CCPoint convertPos(CCPoint &pos);
	Direction getRotateDirection(Direction &direction);
	void deletePlane(Plane *plane);
	bool isPlaneInBoard(CCPoint pos, Direction direct);
};



} /* namespace ecoolsoft */
#endif /* PLAYER_H_ */

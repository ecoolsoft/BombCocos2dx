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
	 * ����������
	 */
	CCMutableArray<Tile*> *attackedTileList;
	/**
	 * ��ӷɻ�
	 */
	void addPlane(Direction direction, CCPoint pos, std::string strSrc="main_", bool isVisible=true);
	/**
	 * �������ɻ�
	 */
	void addRandomPlane(std::string strSrc="main_", bool isVisible=true);
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
	 * ��ת�ɻ�
	 */
	bool rotate(Plane *plane);
	/**
	 * �ƶ��ɻ�
	 */
	bool move(Plane *plane, int x, int y);
	/**
	 * �ı�λ��
	 */
	void changePositon(CCPoint &boardPos, float lenPerTile);
	/**
	 * �Ƿ�ɻ����Ѿ�����
	 */
	bool isPlaneEnough();
	/**
	  * �Ƿ��зɻ�
	  */
	bool isHavePlane();
	/**
	 * �Ƿ������
	 */
	bool containPoint(CCPoint* location);
private:
	/**
	  * �ɻ��б�
	  */
	CCMutableArray<Plane*> *planeList;
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

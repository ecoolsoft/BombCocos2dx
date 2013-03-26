#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "HXmlParse.h"
#include "Constants.h"

USING_NS_CC;
using namespace ecoolsoft;

/**
 *TODO Activity idle timeout for HistoryRecord
 */
class HelloWorld : public cocos2d::CCLayer
{
public:
	HelloWorld();
	~HelloWorld();
	//��ʼ��
	virtual bool init();  
	//��ʼ������
	static CCScene* scene();

	/**
	 * ��ť�ص�
	 */
	virtual void menuCloseCallback(CCObject* pSender);

	virtual void menuSettingCallback(CCObject* pSender);

	virtual void menuAddCallback(CCObject* pSender);

	virtual void menuDeleteCallback(CCObject* pSender);

	virtual void menuStartCallback(CCObject* pSender);

	virtual void menuSoundCallback(CCObject* pSender);

	/**
	 * �Ʋ��ƶ��ص�
	 */
	void spriteCloudMoveFinished(CCNode *node);

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(HelloWorld);

	//�����ص�
	void registerWithTouchDispatcher();

private:
	/**
	 * ��ʼ����ť
	 */
	void initBtn();

	/**
	 * ��ʼ������
	 */
	void initBackground();

	/**
	 * ��ʼ���������
	 */
	void initLeftArea();

	/**
	 * ��ʼ���Ҳ�����
	 */
	void initRightArea();

	/**
	 *�ı����λ��
	 */
	void changePlayerPosition(Player* main, Player* subordinate);
	/**
	 * ��ʼ���û�
	 */
	void initPlayer();
	/**
	 * ������ʼ
	 */
	void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	/**
	 * ��������
	 */
	void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	/**
	 * ���û�
	 */
	Player *playerMain;
	/**
	 * ���û�
	 */
	Player *playerSubordinate;
	/**
	 * ��ǰ�����û�
	 */
	Player *currentPlayer;
	/**
	 * ����
	 */
	CCString *strLanguage;
	/*
	 * ��Ļ��С
	 */
	CCSize screenSize;
	/*
	 * xml��Դ�ļ�������
	 */
	HXmlParse *xmlParse;
	CCMenuItemImage *pAddItem;
	CCMenuItemImage *pDeleteItem;
	CCMenuItemImage *pStartItem;
	/**
	 * ��ʼλ��
	 */
	CCPoint startLocation;
};

#endif // __HELLOWORLD_SCENE_H__

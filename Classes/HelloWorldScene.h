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
	//初始化
	virtual bool init();  
	//初始化场景
	static CCScene* scene();

	/**
	 * 按钮回调
	 */
	virtual void menuCloseCallback(CCObject* pSender);

	virtual void menuSettingCallback(CCObject* pSender);

	virtual void menuAddCallback(CCObject* pSender);

	virtual void menuDeleteCallback(CCObject* pSender);

	virtual void menuStartCallback(CCObject* pSender);

	virtual void menuSoundCallback(CCObject* pSender);

	/**
	 * 云彩移动回调
	 */
	void spriteCloudMoveFinished(CCNode *node);

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(HelloWorld);

	//触摸回调
	void registerWithTouchDispatcher();

private:
	/**
	 * 初始化按钮
	 */
	void initBtn();

	/**
	 * 初始化背景
	 */
	void initBackground();

	/**
	 * 初始化左侧区域
	 */
	void initLeftArea();

	/**
	 * 初始化右侧区域
	 */
	void initRightArea();

	/**
	 *改变玩家位置
	 */
	void changePlayerPosition(Player* main, Player* subordinate);
	/**
	 * 初始化用户
	 */
	void initPlayer();
	/**
	 * 触摸开始
	 */
	void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	/**
	 * 触摸结束
	 */
	void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	/**
	 * 主用户
	 */
	Player *playerMain;
	/**
	 * 副用户
	 */
	Player *playerSubordinate;
	/**
	 * 当前操作用户
	 */
	Player *currentPlayer;
	/**
	 * 语言
	 */
	CCString *strLanguage;
	/*
	 * 屏幕大小
	 */
	CCSize screenSize;
	/*
	 * xml资源文件解析器
	 */
	HXmlParse *xmlParse;
	CCMenuItemImage *pAddItem;
	CCMenuItemImage *pDeleteItem;
	CCMenuItemImage *pStartItem;
	/**
	 * 开始位置
	 */
	CCPoint startLocation;
};

#endif // __HELLOWORLD_SCENE_H__

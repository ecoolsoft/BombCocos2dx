#include "HelloWorldScene.h"
//#include "PureMVC/PureMVC.hpp"

//USING_NS_CC;
//using namespace ecoolsoft;

HelloWorld::HelloWorld() :
	strLanguage(NULL), playerMain(NULL), playerSubordinate(NULL),
			currentPlayer(NULL), xmlParse(NULL) {
}//, leftPos(NULL), rightPos(NULL), leftLenPerTile(0.0f), rightLenPerTile(0.0f)

HelloWorld::~HelloWorld() {
	if (strLanguage) {
		strLanguage->release();
		strLanguage = NULL;
	}
	// TODO release
	/*	if (player1) {
	 player1->release();
	 player1 = NULL;
	 }
	 if (player2) {
	 player2->release();
	 player2 = NULL;
	 }
	 if (currentPlayer) {
	 currentPlayer->release();
	 currentPlayer = NULL;
	 }*/
}

CCScene* HelloWorld::scene() {
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();

	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::node();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init()) {
		return false;
	}

	//启用触摸
	this->setIsTouchEnabled(true);

	screenSize = CCDirector::sharedDirector()->getWinSize();
	xmlParse = HXmlParse::parserWithFile("string.xml");

	initBackground();
	initBtn();
	initLeftArea();
	initRightArea();
	initPlayer();

	return true;
}

void HelloWorld::initRightArea() {
	/*
	 * 右侧区域
	 */
	CCSprite* pSpriteRight = CCSprite::spriteWithFile("right.png");
	pSpriteRight->setAnchorPoint(ccp(0,0));
	pSpriteRight->setPosition(ccp(270, 60));
	this->addChild(pSpriteRight, 1);

	//添加文字
	CCLabelTTF* pLabelRight = CCLabelTTF::labelWithString(
			((CCString *) xmlParse->mDic->objectForKey("enemy"))->getCString(),
			"Arial", 14);
	pLabelRight->setAnchorPoint(ccp(1,1));
	//setPosition是相对于parent来说的
	pLabelRight->setPosition(
			ccp(pSpriteRight->getContentSize().width-3, pSpriteRight->getContentSize().height));
	pSpriteRight->addChild(pLabelRight, 1);
}

void HelloWorld::initLeftArea() {
	/*
	 * 左侧区域
	 */
	CCSprite* pSpriteLeft = CCSprite::spriteWithFile("left.png");
	pSpriteLeft->setAnchorPoint(ccp(0,0));
	pSpriteLeft->setPosition(ccp(0, 0));
	this->addChild(pSpriteLeft, 1);

	//添加文字
	CCLabelTTF
			* pLabelLeft =
					CCLabelTTF::labelWithString(
							((CCString *) xmlParse->mDic->objectForKey("allies"))->getCString(),
							"Arial", 14);
	pLabelLeft->setAnchorPoint(ccp(0,1));
	pLabelLeft->setPosition(
			ccp(3, pSpriteLeft->getPosition().y+pSpriteLeft->getContentSize().height));
	pSpriteLeft->addChild(pLabelLeft, 1);
}

void HelloWorld::initBackground() {
	/*
	 * 背景
	 */
	CCSprite* pSpriteBK = CCSprite::spriteWithFile("bk.png");
	pSpriteBK->setAnchorPoint(ccp(0,0));
	pSpriteBK->setPosition(ccp(0, 0));
	this->addChild(pSpriteBK, 0);

	/*
	 * 移动云彩
	 */
	float cloud1Height = 270;
	//float actualDuration = 20;
	CCSprite* pSpriteCloud1 = CCSprite::spriteWithFile("cloud1.png"); //42*34
	pSpriteCloud1->setAnchorPoint(ccp(0,0));
	pSpriteCloud1->setPosition(
			ccp(-pSpriteCloud1->getContentSize().width, cloud1Height));
	this->addChild(pSpriteCloud1, 1);

	CCFiniteTimeAction* actionMoveCloud1 = CCMoveTo::actionWithDuration(
			(ccTime) Constants::SPRITE_MOVE_DURATION,
			ccp(screenSize.width, cloud1Height));
	CCFiniteTimeAction* actionMoveDoneCloud1 = CCCallFuncN::actionWithTarget(
			this, callfuncN_selector(HelloWorld::spriteCloudMoveFinished));
	pSpriteCloud1->runAction(
			CCSequence::actions(actionMoveCloud1, actionMoveDoneCloud1, NULL));

}

void HelloWorld::initBtn() {
	/**
	 * 关闭按钮
	 */
	CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(
			"CloseNormal.png", "CloseSelected.png", this,
			menu_selector(HelloWorld::menuCloseCallback));
	pCloseItem->setAnchorPoint(ccp(0,0));
	pCloseItem->setPosition(ccp(screenSize.width - 35, screenSize.height - 35));

	/**
	 * 设置按钮
	 */
	CCMenuItemImage *pSettingItem = CCMenuItemImage::itemFromNormalImage(
			"SettingNormal.png", "SettingSelected.png", this,
			menu_selector(HelloWorld::menuSettingCallback));
	pSettingItem->setAnchorPoint(ccp(0,0));
	pSettingItem->setPosition(
			ccp(screenSize.width - 75, screenSize.height - 35));

	pAddItem
			= CCMenuItemImage::itemFromNormalImage("AddNormal.png",
					"AddSelected.png", this,
					menu_selector(HelloWorld::menuAddCallback));
	pAddItem->setAnchorPoint(ccp(0,0));
	pAddItem->setPosition(ccp(284, 32));
	// TODO 修改禁用的图片
	CCSprite *pAddItemDisable = CCSprite::spriteWithFile("AddDisable.png");
	pAddItem->setDisabledImage(pAddItemDisable);
	pAddItem->setIsEnabled(true);

	/**
	 * 删除按钮
	 */
	pDeleteItem = CCMenuItemImage::itemFromNormalImage("DeleteNormal.png",
			"DeleteSelected.png", this,
			menu_selector(HelloWorld::menuDeleteCallback));
	pDeleteItem->setAnchorPoint(ccp(0,0));
	pDeleteItem->setPosition(ccp(322, 32));
	// TODO 修改禁用的图片
	CCSprite *pDeleteItemDisable =
			CCSprite::spriteWithFile("DeleteDisable.png");
	pDeleteItem->setDisabledImage(pDeleteItemDisable);
	pDeleteItem->setIsEnabled(true);

	/**
	 * 开始按钮
	 */
	pStartItem = CCMenuItemImage::itemFromNormalImage("StartNormal.png",
			"StartSelected.png", this,
			menu_selector(HelloWorld::menuStartCallback));
	pStartItem->setAnchorPoint(ccp(0,0));
	pStartItem->setPosition(ccp(435, 0));
	// TODO 修改禁用的图片
	CCSprite *pStartItemDisable = CCSprite::spriteWithFile("StartDisable.png");
	pStartItem->setDisabledImage(pStartItemDisable);
	pStartItem->setIsEnabled(false);

	/**
	 * 声音按钮
	 */
	CCMenuItemImage *pSoundItem = CCMenuItemImage::itemFromNormalImage(
			"SoundNormal.png", "SoundSelected.png", this,
			menu_selector(HelloWorld::menuSoundCallback));
	pSoundItem->setAnchorPoint(ccp(0,0));
	pSoundItem->setPosition(ccp(360, 32));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::menuWithItems(pSettingItem, pCloseItem, pAddItem,
			pDeleteItem, pStartItem, pSoundItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
}

void HelloWorld::initPlayer() {
	playerMain = new Player(MAIN, this, ccp(15,15+20), 22);//字母数字20*20，边框15
	playerSubordinate = new Player(SUBORDINATE, this, ccp(277,67+16), 18);//字母数字16*16，边框7
}

void HelloWorld::menuCloseCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::menuSettingCallback(CCObject* pSender) {

}

void HelloWorld::menuAddCallback(CCObject* pSender) {
	//添加飞机
	if (!playerMain->isPlaneEnough()) {
		playerMain->addRandomPlane();
		pDeleteItem->setIsEnabled(true);
	}
	//如果已经添加了三架飞机，按钮变灰
	if (playerMain->isPlaneEnough()) {
		pAddItem->setIsEnabled(false);
		pStartItem->setIsEnabled(true);
	}

	//敌人添加飞机，隐藏的
	if (!playerSubordinate->isPlaneEnough()) {
		playerSubordinate->addRandomPlane("sub_", false);
	}
}

void HelloWorld::menuDeleteCallback(CCObject* pSender) {
	if (playerMain->isHavePlane()) {
		playerMain->deletePlane();
		pAddItem->setIsEnabled(true);
	}
	if (!playerMain->isHavePlane()) {
		pDeleteItem->setIsEnabled(false);
	}
	pStartItem->setIsEnabled(false);
}

void HelloWorld::changePlayerPosition(Player* main, Player* subordinate) {
	CCPoint posTemp = main->boardPos;
	float lenTemp = main->lenPerTile;

	//更改主用户坐标
	main->changePositon(subordinate->boardPos, subordinate->lenPerTile);

	//更改从用户坐标
	//subordinate->changePositon(posTemp, lenTemp);
}

void HelloWorld::menuStartCallback(CCObject* pSender) {
	changePlayerPosition(playerMain, playerSubordinate);
	pDeleteItem->setIsEnabled(false);
}

void HelloWorld::menuSoundCallback(CCObject* pSender) {
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pew-pew-lei.wav");
}

void HelloWorld::spriteCloudMoveFinished(CCNode *node) {
	CCSprite *sprite = (CCSprite *) node;
	//CCLog("actualDuration:%f", Constants::SPRITE_MOVE_DURATION);
	sprite->setPosition(
			ccp(-sprite->getContentSize().width, sprite->getPosition().y));
	//CCLog("sprite->getContentSize().width:%f", sprite->getContentSize().width);
	//CCLog("sprite->getPosition().y:%f", sprite->getPosition().y);
	CCFiniteTimeAction* actionMoveCloud1 = CCMoveTo::actionWithDuration(
			(ccTime) Constants::SPRITE_MOVE_DURATION,
			ccp(screenSize.width, sprite->getPosition().y));
	CCFiniteTimeAction* actionMoveDoneCloud1 = CCCallFuncN::actionWithTarget(
			this, callfuncN_selector(HelloWorld::spriteCloudMoveFinished));
	sprite->runAction(
			CCSequence::actions(actionMoveCloud1, actionMoveDoneCloud1, NULL));
}

void HelloWorld::registerWithTouchDispatcher() {
	// CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
	CCTouchDispatcher::sharedDispatcher()->addStandardDelegate(this, 0);
}

void HelloWorld::ccTouchesBegan(CCSet* touches, CCEvent* event) {
	CCTouch* touch = (CCTouch*) (touches->anyObject());
	CCPoint location = touch->locationInView();

	//CCLog("++++++++begin befor  x:%f, y:%f", location.x, location.y);
	startLocation = CCDirector::sharedDirector()->convertToGL(location);
	//CCLog("++++++++begin after  x:%f, y:%f", startLocation.x, startLocation.y);
}

void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event) {
	CCTouch* touch = (CCTouch*) (touches->anyObject());
	CCPoint location = touch->locationInView();

	//CCLog("++++++++end befor  x:%f, y:%f", location.x, location.y);
	location = CCDirector::sharedDirector()->convertToGL(location);
	//CCLog("++++++++end after  x:%f, y:%f", location.x, location.y);

	if (startLocation.x > playerMain->boardPos.x && startLocation.x
			< playerMain->boardPos.x + 10 * playerMain->lenPerTile
			&& startLocation.y > playerMain->boardPos.y && startLocation.y
			< playerMain->boardPos.y + 10 * playerMain->lenPerTile
	//&& location.x > playerMain->boardPos.x
	//&& location.x < playerMain->boardPos.x + 10*playerMain->lenPerTile
	//&& location.y > playerMain->boardPos.y
	//&& location.y < playerMain->boardPos.y + 10*playerMain->lenPerTile
	) {
		//CCLog("in board");
		Plane* plane = playerMain->getPlane(startLocation);
		if (plane != NULL) {
			CCLog("not null");
			//如果是旋转
			if (startLocation.x - location.x > playerMain->lenPerTile
					&& startLocation.y - location.y > playerMain->lenPerTile) {
				CCLog("***********rotate");
				playerMain->rotate(plane);
			} else if (startLocation.x - location.x > playerMain->lenPerTile
					&& fabs(startLocation.y - location.y)
							< playerMain->lenPerTile) { //左移
				playerMain->move(plane, -1, 0);
			} else if (location.x - startLocation.x > playerMain->lenPerTile
					&& fabs(startLocation.y - location.y)
							< playerMain->lenPerTile) { //右移
				CCLog("***********right");
				CCLog("***********plane:%f", plane->pos.x);
				playerMain->move(plane, 1, 0);
			} else if (fabs(location.x - startLocation.x)
					< playerMain->lenPerTile && location.y - startLocation.y
					> playerMain->lenPerTile) { //上移
				playerMain->move(plane, 0, 1);
			} else if (fabs(location.x - startLocation.x)
					< playerMain->lenPerTile && startLocation.y - location.y
					> playerMain->lenPerTile) { //下移
				playerMain->move(plane, 0, -1);
			}
		}
	}
}

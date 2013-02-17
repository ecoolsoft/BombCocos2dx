#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "CCApplication.h"

/**
@brief	The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by CCDirector.
第一个规则：和公有继承相反，如果两个类之间的继承关系为私有，编译器一般不会将派生类对象转换成基类对象。
第二个规则: 从私有基类继承而来的成员都成为了派生类的私有成员，即使它们在基类中是保护或公有成员。
*/
class  AppDelegate : private cocos2d::CCApplication
{
public:
	AppDelegate();
	virtual ~AppDelegate();

    /**
    @brief	Implement for initialize OpenGL instance, set source path, etc...
    */
    virtual bool initInstance();

    /**
    @brief	Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_


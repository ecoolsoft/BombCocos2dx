//
//  HXmlParse.h
//  HAnimation
//
//  Created by Himi on 12-3-22.
//  Copyright (c) 2012年 Augustimpression. All rights reserved.
//

#ifndef HAnimation_HXmlParse_h
#define HAnimation_HXmlParse_h

#include "cocos2d.h"
#include "CCSAXParser.h"
#include "CCObject.h"
#include "CCMutableDictionary.h"

using namespace cocos2d;

class CC_DLL HXmlParse :public CCObject, public CCSAXDelegator
{

public:

    static HXmlParse * parserWithFile(const char *tmxFile);

    bool initHXmlParse(const char* xmlName);

    //  使用 CCSAXDelegator 重写3个回调函数

    void startElement(void *ctx, const char *name, const char **atts);

    void endElement(void *ctx, const char *name);

    void textHandler(void *ctx, const char *ch, int len);

    std::string root_name;

    bool isJumpHeadData;

    CCMutableDictionary<std::string,CCString*> *mDic;

private:

    std::string startXmlElement;//用来记录每个key前字段

    std::string endXmlElement;//用来记录每个key后字段

    std::string currString;//记录每个value的值

};

#endif

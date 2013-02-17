//
//  HXmlParse.cpp
//  HAnimation
//
//  Created by Himi on 12-3-22.
//  Copyright (c) 2012�� Augustimpression. All rights reserved.
//

#include "HXmlParse.h"
#include "CCSAXParser.h"

HXmlParse * HXmlParse::parserWithFile(const char *tmxFile)
{
    HXmlParse *pRet = new HXmlParse();
    if(pRet->initHXmlParse(tmxFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool HXmlParse::initHXmlParse(const char* xmlName)

{

    mDic = new CCMutableDictionary<std::string,CCString*>();

    CCSAXParser _par;

    if (false == _par.init("UTF-8") )

    {
        CCLog("-----��ʹ��utf-8��ʽ!");
        return false;
    }
    _par.setDelegator(this);
    const char* _path =CCFileUtils::fullPathFromRelativePath(xmlName);
    return _par.parse(_path);

}

//�ص�����

void HXmlParse::startElement(void *ctx, const char *name, const char **atts)

{

    CC_UNUSED_PARAM(ctx);

    startXmlElement = (char*)name;
    if(!isJumpHeadData){//��������ͷ
        CCLog("------����root name");
        isJumpHeadData=true;
        root_name=startXmlElement;
        return;
    }

//    CCLog("-startElement----%s",startXmlElement.c_str());

}

void HXmlParse::endElement(void *ctx, const char *name)

{
    CC_UNUSED_PARAM(ctx);

    endXmlElement = (char*)name;
    if(endXmlElement==root_name){//����β
        CCLog("��ȡxml����");
        isJumpHeadData=false;
        root_name="";
        return;
    }

//    CCLog("-endElement----%s",endXmlElement.c_str());
}
//��ֵ�ԵĽ����ֶ�
void HXmlParse::textHandler(void *ctx, const char *ch, int len)
{

    CC_UNUSED_PARAM(ctx);
    currString=string((char*)ch,0,len);
    CCString *ccStr =new CCString();//��ע3
    ccStr->m_sString=currString;
    if(root_name!=""){
         mDic->setObject(ccStr,startXmlElement);
        CCLog("-----key:%s, value:%s",startXmlElement.c_str(),mDic->objectForKey(startXmlElement)->m_sString.c_str());
    }

//    CCLog("-textHandler----%s",currString.c_str());

}

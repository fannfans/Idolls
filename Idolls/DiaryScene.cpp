//
//  DiaryScene.cpp
//  Idolls
//
//  Created by 효은 김 on 13. 8. 21..
//
//

#include "DiaryScene.h"
#include "global.h"

using namespace cocos2d;


#define IMG_WIDTH 441


CCScene* DiaryScene::scene()
{
    
    CCScene *scene = CCScene::create();
    
    
    DiaryScene *layer = DiaryScene::create();
    
    
    scene->addChild(layer);
    
    
    return scene;
}


bool DiaryScene::init()
{
    
    if ( !CCLayerColor::initWithColor(ccc4(255,255,255,255)) )
    {
        return false;
    }
    
    // 디바이스 사이즈
    winSize = CCDirector::sharedDirector()->getWinSize();
    
    //배경
    CCSprite *diary_background = CCSprite::create("diary_background.png");
    diary_background->setScale(winSize.width/3200*2.5);
    diary_background->setPosition(ccp(winSize.width/2,winSize.height/2));
    
    //다이어리 배경레이어
    CCLayer *diary_bglayer= CCLayerColor::create(ccc4(255,0,255,255));
    diary_bglayer->setAnchorPoint(CCPointZero);
    diary_bglayer->setPosition(ccp(0,0));
    diary_bglayer->setContentSize(CCSizeMake(winSize.width,winSize.height));
    
    diary_bglayer->addChild(diary_background);
    
    return true;
}



void DiaryScene::onEnter(){
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCLayer::onEnter();
    
}

void DiaryScene::onExit(){
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    
    CCLayer::onExit();
}

void DiaryScene::scrollViewDidScroll(cocos2d::extension::CCScrollView *view){
    
}

void DiaryScene::scrollViewDidZoom(cocos2d::extension::CCScrollView *view){
    
    
}

bool DiaryScene::ccTouchBegan(CCTouch *pTouch, CCEvent* event){
    CCPoint touchPoint = pTouch->getLocation();
    CCLOG("Touches Began....(%f, %f)",touchPoint.x,touchPoint.y);
    return true;
}

void DiaryScene::ccTouchMoved(CCTouch *pTouch, CCEvent* event){
    CCPoint touchPoint = pTouch->getLocation();
    CCLOG("Touches Moved....(%f,%f)",touchPoint.x, touchPoint.y);
}

//터치 후 손가락을 화면에서 뗐을 때 캐릭터이동
void DiaryScene::ccTouchEnded(CCTouch *pTouch, CCEvent* event){
    CCPoint touchPoint = pTouch->getLocation();
    //CCMoveTo* chMove = CCMoveTo::create(2,ccp(touchPoint.x, touchPoint.y));
    //maincharacter->runAction(chMove);
    CCLOG("Touches Endeds....(%f, %f)",touchPoint.x, touchPoint.y);
}

void DiaryScene::ccTouchCancelled(CCTouch *pTouch, CCEvent* event){
    CCLOG("Touches Cancelled");
    
}
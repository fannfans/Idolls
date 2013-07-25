//
//  MyroomScene.cpp
//  Idolls
//
//  Created by 효은 김 on 13. 7. 24..
//
//

#include "MyroomScene.h"

using namespace cocos2d;


#define IMG_WIDTH 441

CCScene* MyroomScene::scene()
{

    CCScene *scene = CCScene::create();
    

    MyroomScene *layer = MyroomScene::create();
    

    scene->addChild(layer);
    

    return scene;
}


bool MyroomScene::init()
{
    
    if ( !CCLayerColor::initWithColor(ccc4(255,255,255,255)) )
    {
        return false;
    }
    
    CCSprite *sprite1 = CCSprite::create("background1.png");
    
    
    
    sprite1->setScale(1);
    
    
    sprite1->setPosition(ccp(150,240));
    
    
    CCLayerColor *layer= CCLayerColor::create(ccc4(255,0,255,255));
    layer->setAnchorPoint(CCPointZero);
    layer->setPosition(ccp(0,0));
    layer->setContentSize(CCSizeMake(320,480));
    
    layer->addChild(sprite1);
    
    
    scrollView = CCScrollView::create();
    scrollView->retain();
    scrollView->setDirection(kCCScrollViewDirectionHorizontal);
    scrollView->setViewSize(CCSizeMake(320,480));
    scrollView->setContentSize(layer->getContentSize());
    scrollView->setContentOffset(CCPointZero, false);
    scrollView->setPosition(ccp(0,0));
    scrollView->setContainer(layer);
    scrollView->setDelegate(this);
    
    this->addChild(scrollView);
    
    return true;
}


void MyroomScene::onEnter(){
    
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
    
}

void MyroomScene::onExit(){
    
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
    
}

void MyroomScene::scrollViewDidScroll(cocos2d::extension::CCScrollView *view){
    
}



void MyroomScene::scrollViewDidZoom(cocos2d::extension::CCScrollView *view){
    
    
}

bool MyroomScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    return true;
}

void MyroomScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    CCLOG("move");
    
}

void MyroomScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    
    
}

void MyroomScene::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    

}
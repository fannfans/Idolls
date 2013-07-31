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
    
    //배경
    CCSprite *bg1 = CCSprite::create("background1.png");
    bg1->setScale(1);
    bg1->setPosition(ccp(160,240));
    
    //헤더
    CCSprite *hd1 = CCSprite::create("top_bar.png");
    hd1->setPosition(ccp(160,455));
    
    
//    마이룸배경레이어
    CCLayerColor *bglayer= CCLayerColor::create(ccc4(255,0,255,255));
    bglayer->setAnchorPoint(CCPointZero);
    bglayer->setPosition(ccp(0,0));
    bglayer->setContentSize(CCSizeMake(320,480));
    
    bglayer->addChild(bg1);
    
    scrollView = CCScrollView::create();
    scrollView->retain();
    scrollView->setDirection(kCCScrollViewDirectionHorizontal);
    scrollView->setViewSize(CCSizeMake(320,480));
    scrollView->setContentSize(bglayer->getContentSize());
    scrollView->setContentOffset(CCPointZero, false);
    scrollView->setPosition(ccp(0,0));
    scrollView->setContainer(bglayer);
    scrollView->setDelegate(this);
    this->addChild(scrollView);
    
//    헤더레이어
    CCLayerColor *hdlayer = CCLayerColor::create(ccc4(255,0,255,255));
    hdlayer->setAnchorPoint(CCPointZero);
    hdlayer->setPosition(ccp(0,0));
    hdlayer->setContentSize(CCSizeMake(320, 50));
    hdlayer->addChild(hd1);
    
//    헤더 코인/스타
    CCMenuItemImage *pMenuStars = CCMenuItemImage::create("money_star_box.png","money_star_box.png",this, menu_selector(MyroomScene::stars));
    CCMenuItemImage *pMenuCoins = CCMenuItemImage::create("money_coin_box.png","money_coin_box.png",this, menu_selector(MyroomScene::coins));

    CCMenu* pHdMenu = CCMenu::create(pMenuStars,pMenuCoins,NULL);
    pHdMenu->alignItemsHorizontally();
    pHdMenu->setPosition(ccp(220,450));
    
    hdlayer->addChild(pHdMenu);
    
    CCSprite *nickName = CCSprite::create("nick_box.png");

    nickName->setPosition(ccp(65,450));
    hdlayer->addChild(nickName);
    
    this->addChild(hdlayer);
    
    
//    캐릭터
    maincharacter = CCSprite::create("character.png");
    maincharacter->setPosition(ccp(50,120));
    scrollView->addChild(maincharacter);
    
//    캐릭터애니메이션
    CCAnimation *animation = CCAnimation::create();
    animation->setDelayPerUnit(0.3);
    animation->addSpriteFrameWithFileName("character2.png");
    animation->addSpriteFrameWithFileName("character3.png");
    animation->addSpriteFrameWithFileName("character.png");
    CCAnimate *animate = CCAnimate::create(animation);
    CCAction *rep = CCRepeatForever::create(animate);
    maincharacter->runAction(rep);
    
    
    
    
//    하단메뉴
    CCLayerColor *menulayer = CCLayerColor::create(ccc4(255,0,255,255));
    menulayer->setAnchorPoint(CCPointZero);
    menulayer->setPosition(ccp(0,0));
    menulayer->setContentSize(CCSizeMake(320,20));
    
    CCMenuItemImage *pMenuSchedule = CCMenuItemImage::create("schedule.png", "schedule.png", this, menu_selector(MyroomScene::schedule));
    CCMenuItemImage *pMenuCloset = CCMenuItemImage::create("closet.png","closet.png",this, menu_selector(MyroomScene::closet));
    CCMenuItemImage *pMenuDiary = CCMenuItemImage::create("diary.png", "diary.png", this, menu_selector(MyroomScene::diary));
    CCMenu* pMenu = CCMenu::create(pMenuSchedule,pMenuCloset,pMenuDiary,NULL);
    
    pMenu->alignItemsHorizontally();
    pMenu->setPosition(ccp(160,20));
    menulayer->addChild(pMenu);
    this->addChild(menulayer);
    
    
    return true;
}


void MyroomScene::onEnter(){
    
//    CCLayer::onEnter();
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCLayer::onEnter();
    
}

void MyroomScene::onExit(){
    
//    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
//    CCLayer::onExit();
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    
    CCLayer::onExit();
}

void MyroomScene::scrollViewDidScroll(cocos2d::extension::CCScrollView *view){
    
}



void MyroomScene::scrollViewDidZoom(cocos2d::extension::CCScrollView *view){
    
    
}

bool MyroomScene::ccTouchBegan(CCTouch *pTouch, CCEvent* event){
    CCPoint touchPoint = pTouch->getLocation();
    CCLOG("Touches Began....(%f, %f)",touchPoint.x,touchPoint.y);
    return true;
}
void MyroomScene::ccTouchMoved(CCTouch *pTouch, CCEvent* event){
    CCPoint touchPoint = pTouch->getLocation();
    CCLOG("Touches Moved....(%f,%f)",touchPoint.x, touchPoint.y);
}
//터치 후 손가락을 화면에서 뗐을 때 이동
void MyroomScene::ccTouchEnded(CCTouch *pTouch, CCEvent* event){
    CCPoint touchPoint = pTouch->getLocation();
    CCMoveTo* chMove = CCMoveTo::create(2,ccp(touchPoint.x, touchPoint.y));
    maincharacter->runAction(chMove);
    CCLOG("Touches Endeds....(%f, %f)",touchPoint.x, touchPoint.y);
}

void MyroomScene::ccTouchCancelled(CCTouch *pTouch, CCEvent* event){
    CCLOG("Touches Cancelled");

}


void MyroomScene::schedule(){
    
}
void MyroomScene::closet(){
    
}
void MyroomScene::diary(){
    
}
void MyroomScene::stars(){
    
}
void MyroomScene::coins(){
    
}
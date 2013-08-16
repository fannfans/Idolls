//
//  MyroomScene.cpp
//  Idolls
//
//  Created by 효은 김 on 13. 7. 24..
//
//

#include "global.h"

#include "MyroomScene.h"
//#include "ClosetScene.h"
#include "MarketScene.h"

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
    
    // 디바이스 사이즈
    winSize = CCDirector::sharedDirector()->getWinSize();
    //배경
    CCSprite *bg1 = CCSprite::create("myroom_background.png");
    bg1->setScale(winSize.width/3200*2.5);
    bg1->setPosition(ccp(winSize.width/2,winSize.height/2));
    
    //    마이룸배경레이어
    bglayer= CCLayerColor::create(ccc4(255,0,255,255));
    bglayer->setAnchorPoint(CCPointZero);
    bglayer->setPosition(ccp(0,0));
    bglayer->setContentSize(CCSizeMake(winSize.width,winSize.height));
    
    bglayer->addChild(bg1);
    
    scrollView = CCScrollView::create();
    scrollView->retain();
    scrollView->setDirection(kCCScrollViewDirectionHorizontal);
    scrollView->setViewSize(CCSizeMake(winSize.width,winSize.height));
    scrollView->setContentSize(bglayer->getContentSize());
    scrollView->setContentOffset(CCPointZero, true);
    scrollView->setPosition(ccp(0,0));
    scrollView->setContainer(bglayer);
    scrollView->setDelegate(this);
    this->addChild(scrollView);
    
    //    헤더레이어
    /*
     CCLayerColor *hdlayer = CCLayerColor::create(ccc4(255,0,255,255));
     hdlayer->setAnchorPoint(CCPointZero);
     hdlayer->setPosition(ccp(0,0));
     hdlayer->setContentSize(CCSizeMake(320, 50));
     hdlayer->addChild(hd1);*/
    
    
    
    //    헤더 코인/스타
    money_star_button = CCMenuItemImage::create("money_star_button.png","money_star_button.png",this, menu_selector(MyroomScene::stars));
    
    money_coin_button = CCMenuItemImage::create("money_coin_button.png","money_coin_button.png",this, menu_selector(MyroomScene::coins));
    
    CCMenu* moneyMenu = CCMenu::create(money_star_button, money_coin_button, NULL);
    
    moneyMenu->alignItemsHorizontally();
    moneyMenu->setScale(winSize.width/3200*1.8);
    moneyMenu->setPosition(ccp(winSize.width/10*2.6,winSize.height/10*5.5));
    bglayer->getParent()->getParent()->addChild(moneyMenu);
    
    
    //    캐릭터
    maincharacter = CCSprite::create("character4.png");
    maincharacter->setScale(0.5);
    maincharacter->setPosition(ccp(50,120));
    scrollView->addChild(maincharacter);
    
    //    캐릭터애니메이션
    CCAnimation *animation = CCAnimation::create();
    animation->setDelayPerUnit(0.3);
    animation->addSpriteFrameWithFileName("character5.png");
    animation->addSpriteFrameWithFileName("character4.png");
    animation->addSpriteFrameWithFileName("character5.png");
    CCAnimate *animate = CCAnimate::create(animation);
    CCAction *rep = CCRepeatForever::create(animate);
    maincharacter->runAction(rep);
    
    
    //  하단메뉴
    /*
     popoffMenuLayer : 메뉴나오기 전 +버튼
     popupMenuLayer  : +버튼 눌렀을 때 나오는 메뉴레이어
     */
    popoffMenuLayer = CCLayerColor::create(ccc4(255,0,255,255));
    
    popoffMenuLayer->setAnchorPoint(CCPointZero);
    popoffMenuLayer->setContentSize(CCSizeMake(0,0));
    CCMenuItemImage *popoffButton = CCMenuItemImage::create("menu_button_off.png", "menu_button_off.png",this, menu_selector(MyroomScene::popup));
    popoffButton->setScale(winSize.width/3200*1.8);
    CCMenu* popoffMenu = CCMenu::create(popoffButton,NULL);
    popoffMenu->alignItemsHorizontally();
    popoffMenu->setPosition(ccp(winSize.width/10*9.15,winSize.height/10*0.7));
    popoffMenuLayer->addChild(popoffMenu);
    bglayer->getParent()->getParent()->addChild(popoffMenuLayer);
    
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
//터치 후 손가락을 화면에서 뗐을 때 캐릭터이동
void MyroomScene::ccTouchEnded(CCTouch *pTouch, CCEvent* event){
    CCPoint touchPoint = pTouch->getLocation();
    CCMoveTo* chMove = CCMoveTo::create(2,ccp(touchPoint.x, touchPoint.y));
    maincharacter->runAction(chMove);
    CCLOG("Touches Endeds....(%f, %f)",touchPoint.x, touchPoint.y);
}

void MyroomScene::ccTouchCancelled(CCTouch *pTouch, CCEvent* event){
    CCLOG("Touches Cancelled");
    
}

/*
 * 화살표 눌렀을 때 호출되는 메소드
 * 아래에서 슝 올라옴
 * Method when Direction Pointer is clicked
 * Shuuoong Move to Up from Under the Display
 */
void MyroomScene::popup(){
    popoffMenuLayer->setVisible(false);
    
    popupMenuLayer = CCLayerColor::create(ccc4(255,0,255,255));
    popupMenuLayer->setAnchorPoint(CCPointZero);
    //Move Up from Under
    CCActionInterval* move = CCMoveTo::create(2, ccp(0,winSize.height/10*0.9));
    CCActionInterval* move_ease_out = CCEaseElasticOut::create((CCActionInterval*)(move->copy()->autorelease()));
    
    popupMenuLayer->setContentSize(CCSizeMake(0,0));
    CCMenuItemImage *pMenuSchedule = CCMenuItemImage::create("schedule_button.png", "schedule_button.png", this, menu_selector(MyroomScene::schedule));
    CCMenuItemImage *pMenuCloset = CCMenuItemImage::create("closet_button.png","closet_button.png",this, menu_selector(MyroomScene::closet));
    CCMenuItemImage *pMenuDiary = CCMenuItemImage::create("diary_button.png", "diary_button.png", this, menu_selector(MyroomScene::diary));
    CCMenuItemImage *pMenuMarket = CCMenuItemImage::create("market_button.png","market_button.png", this, menu_selector(MyroomScene::market));
    CCMenuItemImage *pMenuPopoff = CCMenuItemImage::create("menu_button_on.png","menu_button_on.png",this, menu_selector(MyroomScene::popoff));
    
    
    pMenuSchedule->setScale(winSize.width/3200*2.8);
    pMenuCloset->setScale(winSize.width/3200*2.8);
    pMenuDiary->setScale(winSize.width/3200*2.8);
    pMenuMarket->setScale(winSize.width/3200*2.8);
    pMenuPopoff->setScale(winSize.width/3200*1.8);
    
    pMenuPopoff->setPosition(ccp(winSize.width/10*9,winSize.height/10*0.4));
    CCMenu* pMenu = CCMenu::create(pMenuSchedule,pMenuCloset,pMenuDiary,pMenuMarket,pMenuPopoff,NULL);
    
    pMenu->alignItemsHorizontally();
    
    pMenu->setPosition(ccp(winSize.width/10*5,winSize.height/10*-0.1));
    popupMenuLayer->addChild(pMenu);
    popupMenuLayer->runAction(move_ease_out);
    bglayer->getParent()->getParent()->getParent()->addChild(popupMenuLayer);
    
}
/*
 * x 아이콘을 눌렀을 때 사라지고 다시
 * 화살표가 나오도록 함
 * Direction Pointer appear when 'X' Button is clicked
 */
void MyroomScene::popoff(){
    popupMenuLayer->setVisible(false);
    popoffMenuLayer->setVisible(true);
    popoffMenuLayer->setPosition(ccp(0,winSize.height/10*-0.1));
    
    //Move Up from Under
    CCActionInterval* move = CCMoveTo::create(2, ccp(0,winSize.height/10*0.1));
    CCActionInterval* move_ease_out = CCEaseElasticOut::create((CCActionInterval*)(move->copy()->autorelease()));
    popoffMenuLayer->runAction(move_ease_out);
}

void MyroomScene::schedule(){
}
void MyroomScene::closet(){
    /*
    CCScene* pScene = ClosetScene::scene();
    CCDirector::sharedDirector()->pushScene(pScene);
     */
}
void MyroomScene::diary(){
    
}
void MyroomScene::market(){
    
    CCScene* pScene = MarketScene::scene();
    CCDirector::sharedDirector()->pushScene(pScene);
}
void MyroomScene::stars(){
    
}
void MyroomScene::coins(){
    
}
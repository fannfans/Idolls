//
//  ClosetScene.cpp
//  Idolls
//
//  Created by 효은 김 on 13. 8. 5..
//
//

#include "ClosetScene.h"
#include "global.h"
#include "MyroomScene.h"


using namespace cocos2d ;
using namespace cocos2d::extension;

CCScene* ClosetScene::scene()
{
    
    CCScene *scene = CCScene::create();
    
    
    ClosetScene *layer = ClosetScene::create();
    
    
    scene->addChild(layer);
    
    
    return scene;
}

bool ClosetScene::init()
{
    
    if ( !CCLayerColor::initWithColor(ccc4(0,0,0,0)) )
    {
        return false;
    }
    // 디바이스 사이즈
    winSize = CCDirector::sharedDirector()->getWinSize();
    
    // 옷장 배경
    CCSprite *closet_background = CCSprite::create("closet_background.png");
    closet_background->setScale(winSize.width/3200*2.5);
    closet_background->setPosition(ccp(winSize.width/10*5,winSize.height/10*5));
    
    //    옷장 배경레이어
    
    closet_bglayer= CCLayerColor::create(ccc4(255,0,255,255));
    closet_bglayer->setAnchorPoint(CCPointZero);
    closet_bglayer->setPosition(ccp(0,0));
    closet_bglayer->setContentSize(CCSizeMake(320,480));
    
    this->addChild(closet_bglayer);
    
    closet_bglayer->addChild(closet_background);
    
    // 상단 돈
    CCSprite* money_box = CCSprite::create("money_box.png");
    
    money_box->setScale(winSize.width/3200*2.5);
    
    money_box->setPosition(ccp(winSize.width/10*6.7,winSize.height/10*9.6));
    
    closet_bglayer->getParent()->addChild(money_box);
    
    
    money_star_button = CCMenuItemImage::create("money_star_button.png","money_star_button.png",this, menu_selector(ClosetScene::chargeStar));
    
    money_coin_button = CCMenuItemImage::create("money_coin_button.png","money_coin_button.png",this, menu_selector(ClosetScene::chargeCoin));
    
    CCMenu* pMenu = CCMenu::create(money_star_button, money_coin_button, NULL);
    
    pMenu->alignItemsHorizontally();
    pMenu->setScale(winSize.width/3200*1.8);
    pMenu->setPosition(ccp(winSize.width/10*2.6,winSize.height/10*5.5));
    closet_bglayer->getParent()->addChild(pMenu);
    
    // 입어보기, 원래대로 버튼
    CCMenuItemImage *closet_reset_button = CCMenuItemImage::create("closet_reset_button_off.png","closet_reset_button_on.png",this, menu_selector(ClosetScene::reset));
    
    CCMenuItemImage *closet_wear_button = CCMenuItemImage::create("closet_wear_button_off.png","closet_wear_button_on.png",this, menu_selector(ClosetScene::wear));
    
    CCMenu* closetMenu = CCMenu::create(closet_reset_button , closet_wear_button, NULL);
    
    closetMenu->alignItemsHorizontally();
    closetMenu->setScale(winSize.width/3200*2.5);
    closetMenu->setPosition(ccp(winSize.width/10*3,winSize.height/10*4.5));
    closet_bglayer->getParent()->addChild(closetMenu);
    //  하단메뉴
    /*
     popoffMenuLayer : 메뉴나오기 전 +버튼
     popupMenuLayer  : +버튼 눌렀을 때 나오는 메뉴레이어
     */
    popoffMenuLayer = CCLayerColor::create(ccc4(255,0,255,255));
    
    popoffMenuLayer->setAnchorPoint(CCPointZero);
    popoffMenuLayer->setContentSize(CCSizeMake(0,0));
    CCMenuItemImage *popoffButton = CCMenuItemImage::create("menu_button_off.png", "menu_button_off.png",this, menu_selector(ClosetScene::popup));
    popoffButton->setScale(winSize.width/3200*1.8);
    CCMenu* popoffMenu = CCMenu::create(popoffButton,NULL);
    popoffMenu->alignItemsHorizontally();
    popoffMenu->setPosition(ccp(winSize.width/10*9.15,winSize.height/10*0.7));
    popoffMenuLayer->addChild(popoffMenu);
    closet_bglayer->getParent()->addChild(popoffMenuLayer);
    
    
    return true ;
    
    
}
/*
 * 화살표 눌렀을 때 호출되는 메소드
 * 아래에서 슝 올라옴
 * Method when Direction Pointer is clicked
 * Shuuoong Move to Up from Under the Display
 */
void ClosetScene::popup(){
    popoffMenuLayer->setVisible(false);
    
    popupMenuLayer = CCLayerColor::create(ccc4(255,0,255,255));
    popupMenuLayer->setAnchorPoint(CCPointZero);
    //Move Up from Under
    CCActionInterval* move = CCMoveTo::create(2, ccp(0,winSize.height/10*0.9));
    CCActionInterval* move_ease_out = CCEaseElasticOut::create((CCActionInterval*)(move->copy()->autorelease()));
    
    popupMenuLayer->setContentSize(CCSizeMake(0,0));
    
    CCMenuItemImage *pMenuMyroom = CCMenuItemImage::create("myroom_button.png","myroom_button.png",this, menu_selector(ClosetScene::myroom));
    CCMenuItemImage *pMenuSchedule = CCMenuItemImage::create("schedule_button.png", "schedule_button.png", this, menu_selector(ClosetScene::schedule));
    CCMenuItemImage *pMenuDiary = CCMenuItemImage::create("diary_button.png", "diary_button.png", this, menu_selector(ClosetScene::diary));
    CCMenuItemImage *pMenuMarket = CCMenuItemImage::create("market_button.png","market_button.png", this, menu_selector(ClosetScene::market));
    CCMenuItemImage *pMenuPopoff = CCMenuItemImage::create("menu_button_on.png","menu_button_on.png",this, menu_selector(ClosetScene::popoff));
    

    pMenuMyroom->setScale(winSize.width/3200*2.8);
    pMenuSchedule->setScale(winSize.width/3200*2.8);
    pMenuDiary->setScale(winSize.width/3200*2.8);
    pMenuMarket->setScale(winSize.width/3200*2.8);
    pMenuPopoff->setScale(winSize.width/3200*1.8);
    
    pMenuPopoff->setPosition(ccp(winSize.width/10*9,winSize.height/10*0.4));
    CCMenu* pMenu = CCMenu::create(pMenuMyroom,pMenuSchedule,pMenuDiary,pMenuMarket,pMenuPopoff,NULL);
    
    pMenu->alignItemsHorizontally();
    
    pMenu->setPosition(ccp(winSize.width/10*5,winSize.height/10*-0.1));
    popupMenuLayer->addChild(pMenu);
    popupMenuLayer->runAction(move_ease_out);
    closet_bglayer->getParent()->getParent()->addChild(popupMenuLayer);
    
}
/*
 * x 아이콘을 눌렀을 때 사라지고 다시
 * 화살표가 나오도록 함
 * Direction Pointer appear when 'X' Button is clicked
 */
void ClosetScene::popoff(){
    popupMenuLayer->setVisible(false);
    popoffMenuLayer->setVisible(true);
    popoffMenuLayer->setPosition(ccp(0,winSize.height/10*-0.1));
    
    //Move Up from Under
    CCActionInterval* move = CCMoveTo::create(2, ccp(0,winSize.height/10*0.1));
    CCActionInterval* move_ease_out = CCEaseElasticOut::create((CCActionInterval*)(move->copy()->autorelease()));
    popoffMenuLayer->runAction(move_ease_out);
}


void ClosetScene::chargeStar(){
    
    
}

void ClosetScene::chargeCoin(){
    
    
}

void ClosetScene::openMenu(){
    
    
}

void ClosetScene::myroom(){
    
    CCScene* pScene = MyroomScene::scene();
    CCDirector::sharedDirector()->pushScene(pScene);
}

void ClosetScene::schedule(){
    
    
}

void ClosetScene::diary(){
    
    
}

void ClosetScene::market(){
    
    
}

void ClosetScene::reset(){
    
}

void ClosetScene::wear(){
    
}
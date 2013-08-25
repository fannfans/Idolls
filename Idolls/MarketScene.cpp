//
//  MarketScene.cpp
//  Idolls
//
//  Created by 효은 김 on 13. 7. 31..
//
//

#include "MarketScene.h"
#include "MyroomScene.h"

#include "global.h"
#include <stdio.h>
#include <stdlib.h>


using namespace cocos2d ;

//아이템들
CCMenuItemImage *item1;
CCMenuItemImage *item2;
CCMenuItemImage *item3;

CCSprite *now_item_img; //선택한 아이템 이미지
CCLabelTTF *now_item_exp; //선택한 아이템 설명

CCMenu* tapMenu; // 탭 메뉴
// 탭 버튼들
CCMenuItemImage *market_hair_button;
CCMenuItemImage *market_top_button;
CCMenuItemImage *market_bottom_button;
CCMenuItemImage *market_shoes_button;
CCMenuItemImage *market_etc_button;

CCLayerColor *market_item_layer;

CCPoint startPoint; // 터치 시 위치
CCPoint nowPoint; //스크롤시 위치

bool scroll_flag = true;

char items[12][20] ; // 아이템 배열
int prev, now, next; // 현재 보이는 아이템들 번호

CCScene* MarketScene::scene()
{
    
    CCScene *scene = CCScene::create();
    
    
    MarketScene *layer = MarketScene::create();
    
    
    scene->addChild(layer);
    
    
    return scene;
}

bool MarketScene::init()
{
    
    if ( !CCLayerColor::initWithColor(ccc4(0,0,0,0)) )
    {
        return false;
    }
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    
    
    // 배경
    CCSprite* market_background = CCSprite::create("market_background.png");
    
    market_background->setScale(winSize.width/3200*2.5);
    
    market_background->setPosition(ccp(winSize.width/2,winSize.height/2));
    
    //  마켓 배경레이어
    
    market_bglayer = CCLayerColor::create(ccc4(255,0,255,255));
    market_bglayer->setAnchorPoint(ccp(0,0));
    market_bglayer->setPosition(ccp(0,0));
    market_bglayer->setContentSize(CCSizeMake(winSize.width,winSize.height));
    
    this->addChild(market_bglayer);
    
    market_bglayer->addChild(market_background);
    
    
    //    헤더 코인/스타
    money_star_button = CCMenuItemImage::create("money_star_button.png","money_star_button.png",this, menu_selector(MarketScene::chargeStar));
    
    money_coin_button = CCMenuItemImage::create("money_coin_button.png","money_coin_button.png",this, menu_selector(MarketScene::chargeCoin));
    
    CCMenu* moneyMenu = CCMenu::create(money_star_button, money_coin_button, NULL);
    
    moneyMenu->alignItemsHorizontally();
    moneyMenu->setScale(winSize.width/3200*2.5);
    moneyMenu->setPosition(ccp(winSize.width/10*3.3,winSize.height/10*5.9));
    market_bglayer->getParent()->addChild(moneyMenu);    
    
    // 현재 선택한 아이템
    now_item_img = CCSprite::create();
    now_item_img->setScale(winSize.width/3200*7.5);
    now_item_img->setPosition(ccp(winSize.width/10*7.2,winSize.height/10*7.6));
    market_bglayer->getParent()->addChild(now_item_img);
    
    //아이템 설명
    now_item_exp = CCLabelTTF::create("", "Thonburi", 25);
    now_item_exp->setPosition(ccp(winSize.width/10*7.2,winSize.height/10*6));
    market_bglayer->getParent()->addChild(now_item_exp);
    
    // 구매 버튼
    CCMenuItemImage *market_buy_button = CCMenuItemImage::create("market_buy_button_off.png", "market_buy_button_on.png", this, menu_selector(MarketScene::buyItem));
    
    CCMenu* itemMenu = CCMenu::create(market_buy_button, NULL);
    
    itemMenu->alignItemsHorizontally();
    itemMenu->setScale(winSize.width/3200*2.5);
    itemMenu->setPosition(ccp(winSize.width/10*3.4,winSize.height/10*0.4));
    market_bglayer->getParent()->addChild(itemMenu);
    
    
    //캐릭터
    maincharacter = CCSprite::create("character1.png");
    maincharacter->setScale(0.12);
    
    //캐릭터 레이어
    CCLayer *character_layer = CCLayer::create();
    character_layer->setAnchorPoint(CCPointZero);
    character_layer->setPosition(ccp(winSize.width/10*2.5,winSize.height/10*6.5));
    character_layer->addChild(maincharacter);
    
    market_bglayer->getParent()->addChild(character_layer);
    
    // 아이템 탭
    market_hair_button = CCMenuItemImage::create("market_hair_button_on.png", "market_hair_button_on.png", this, menu_selector(MarketScene::hairtap));
    
    market_top_button = CCMenuItemImage::create("market_top_button_off.png", "market_top_button_on.png", this, menu_selector(MarketScene::toptap));
    
    market_bottom_button = CCMenuItemImage::create("market_bottom_button_off.png", "market_bottom_button_on.png", this, menu_selector(MarketScene::bottomtap));
    
    market_shoes_button = CCMenuItemImage::create("market_shoes_button_off.png", "market_shoes_button_on.png", this, menu_selector(MarketScene::shoestap));
    
    market_etc_button = CCMenuItemImage::create("market_etc_button_off.png", "market_etc_button_on.png", this, menu_selector(MarketScene::etctap));
    
    tapMenu = CCMenu::create(market_hair_button, market_top_button, market_bottom_button,market_shoes_button, market_etc_button, NULL);
    
    tapMenu->alignItemsHorizontallyWithPadding(0);
    tapMenu->setScale(winSize.width/3200*2.5);
    tapMenu->setAnchorPoint(ccp(0,0));
    tapMenu->setPosition(ccp(winSize.width/10*5.03,winSize.height/10*3.2));
    market_bglayer->addChild(tapMenu);
    

    char s1[] = "item";
    char s2[] = ".png";

    for (int i=0; i<10; i++) {
        
        char s[3] ;
        char temp[20] = "" ;
        sprintf(s, "%d", i+1);
        
        strcat(temp, s1);
        strcat(temp, s);
        strcat(temp, s2);
       
        strcpy(items[i], temp);

    }

    
    
    // 스크롤뷰 올릴 레이어
    market_item_layer = CCLayerColor::create(ccc4(255,0,255,0));
    market_item_layer->setAnchorPoint(ccp(0,0));
    market_item_layer->setPosition(ccp(0,0));
    market_item_layer->setContentSize(CCSizeMake(winSize.width/10*5, winSize.height/10*2));
    
    market_bglayer->addChild(market_item_layer);

    // 아이템들
    prev = 0;
    now = 1;
    next = 2;
    item1 = CCMenuItemImage::create(items[prev], items[prev], this, menu_selector(MarketScene::selectItem));
    item2 = CCMenuItemImage::create(items[now], items[now], this, menu_selector(MarketScene::selectItem));
    item3 = CCMenuItemImage::create(items[next], items[next], this, menu_selector(MarketScene::selectItem));
    
    CCMenu* itemView = CCMenu::create(item1, item2, item3, NULL);
    
    itemView->alignItemsHorizontallyWithPadding(80.0f);
    itemView->setScale(winSize.width/3200*5);
    itemView->setPosition(ccp(winSize.width/10*2.3,winSize.height/10*(-0.7)));
    market_item_layer->addChild(itemView);
        
    //  하단메뉴
    /*
     popoffMenuLayer : 메뉴나오기 전 +버튼
     popupMenuLayer  : +버튼 눌렀을 때 나오는 메뉴레이어
     */
    popoffMenuLayer = CCLayerColor::create(ccc4(255,0,255,255));
    
    popoffMenuLayer->setAnchorPoint(CCPointZero);
    popoffMenuLayer->setContentSize(CCSizeMake(0,0));
    
    
    CCMenuItemImage *popoffButton = CCMenuItemImage::create("menu_button_off.png", "menu_button_off.png",this, menu_selector(MarketScene::popup));
    popoffButton->setScale(winSize.width/3200*1.8);
    
    CCMenu* popoffMenu = CCMenu::create(popoffButton,NULL);
    popoffMenu->alignItemsHorizontally();
    popoffMenu->setPosition(ccp(winSize.width/10*9.15,winSize.height/10*0.7));
    popoffMenuLayer->addChild(popoffMenu);
    
    market_bglayer->getParent()->addChild(popoffMenuLayer);
    
    
    
    return true ;
}

void MarketScene::onEnter(){
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCLayer::onEnter();
    
}

void MarketScene::onExit(){
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    
    CCLayer::onExit();
}


void MarketScene::scrollViewDidScroll(cocos2d::extension::CCScrollView *view){
    
    //CCLog("Scrolled!!!!!");

}

void MarketScene::scrollViewDidZoom(cocos2d::extension::CCScrollView *view){
    
}

bool MarketScene::ccTouchBegan(CCTouch *pTouch, CCEvent* event){

    startPoint = pTouch->getLocation();
    CCLOG("Touches Moved....(%f,%f)",startPoint.x, startPoint.y);
    
    // 터치한 부분이 아이템 탭 밖에있으면 스크롤 하지 않음
   /* if (startPoint.x>300 || startPoint.x<0) {
        
        scroll_flag=false;
    }
    else if(startPoint.y>300 || startPoint.y<0){
        scroll_flag=false;
    }*/
    
    return true;
}

void MarketScene::ccTouchMoved(CCTouch *pTouch, CCEvent* event){

    if (scroll_flag) {
        nowPoint = pTouch->getLocation();
        CCLOG("Touches Moved....(%f,%f)",nowPoint.x, nowPoint.y);
        
        // prevItem 방향으로 스크롤
        if (startPoint.x > nowPoint.x){
            
            nextItem();
        }
        // nextItem 방향으로 스크롤
        else{
            
            prevItem();
        }
        scroll_flag=false;
    }
    else{

    }

    
    
    
}

//스크롤하고 손 뗐을 때 아이템 위치 변경
void MarketScene::ccTouchEnded(CCTouch *pTouch, CCEvent* event){

    scroll_flag=true;
    
}

void MarketScene::ccTouchCancelled(CCTouch *pTouch, CCEvent* event){
    CCLOG("Touches Cancelled");
    
}

void MarketScene::prevItem(){
    /*
    CCActionInterval* moveLeft = CCMoveBy::create(0.3, ccp(100,0));
    CCAction* next_fadeout = CCHide::create();
    
    CCActionInterval* prevItem = CCMoveBy::create(0.3, ccp(-20,0));
    CCActionInterval* nowItem = CCMoveBy::create(0.3, ccp(100,0));
    CCFiniteTimeAction* nextItem = CCSequence::create(moveLeft,next_fadeout,NULL);
    
    item1->runAction(prevItem);
    item2->runAction(nowItem);
    item3->runAction(nextItem);
    */
    // 아이템 다시 배치
    
    item1->removeFromParentAndCleanup(true);
    item2->removeFromParentAndCleanup(true);
    item3->removeFromParentAndCleanup(true);
   
    if (prev!=0) {
        
        prev--;
        now--;
        next--;
    }

    // 아이템들
    item1 = CCMenuItemImage::create(items[prev], items[prev], this, menu_selector(MarketScene::selectItem));
    item2 = CCMenuItemImage::create(items[now], items[now], this, menu_selector(MarketScene::selectItem));
    item3 = CCMenuItemImage::create(items[next], items[next], this, menu_selector(MarketScene::selectItem));
    
    CCMenu* itemView = CCMenu::create(item1, item2, item3, NULL);
    
    itemView->alignItemsHorizontallyWithPadding(80.0f);
    itemView->setScale(winSize.width/3200*5);
    itemView->setPosition(ccp(winSize.width/10*2.3,winSize.height/10*(-0.7)));
    market_item_layer->addChild(itemView);

}

void MarketScene::nextItem(){
    /*
    CCActionInterval* moveLeft = CCMoveBy::create(0.3, ccp(-20,0));
    CCAction* prev_fadeout = CCHide::create();
    
    CCFiniteTimeAction* prevItem = CCSequence::create(moveLeft,prev_fadeout,NULL);
    CCActionInterval* nowItem = CCMoveBy::create(0.3, ccp(-100,0));
    CCActionInterval* nextItem = CCMoveBy::create(0.3, ccp(-100,0));
    
    item1->runAction(prevItem);
    item2->runAction(nowItem);
    item3->runAction(nextItem);
     */
    
    // 아이템 다시 배치
    
    item1->removeFromParentAndCleanup(true);
    item2->removeFromParentAndCleanup(true);
    item3->removeFromParentAndCleanup(true);
    
    if(next!=sizeof(items)){
        prev++;
        now++;
        next++;
    }
    // 아이템들
    item1 = CCMenuItemImage::create(items[prev], items[prev], this, menu_selector(MarketScene::selectItem));
    item2 = CCMenuItemImage::create(items[now], items[now], this, menu_selector(MarketScene::selectItem));
    
    item3 = CCMenuItemImage::create(items[next], items[next], this, menu_selector(MarketScene::selectItem));
    
    
    CCMenu* itemView = CCMenu::create(item1, item2, item3, NULL);
    
    itemView->alignItemsHorizontallyWithPadding(80.0f);
    itemView->setScale(winSize.width/3200*5);
    itemView->setPosition(ccp(winSize.width/10*2.3,winSize.height/10*(-0.7)));
    market_item_layer->addChild(itemView);

}

void MarketScene::chargeStar(){
    
    
    
    
}

void MarketScene::chargeCoin(){
    
    
    
    
}

// 아이템 클릭하면 설명이 보임
void MarketScene::selectItem(){
    
    // 현재 선택한 아이템
    now_item_img->removeFromParentAndCleanup(true);
    now_item_exp->removeFromParentAndCleanup(true);
    
    now_item_img = CCSprite::create(items[now]);
    now_item_img->setScale(winSize.width/3200*7.5);
    now_item_img->setPosition(ccp(winSize.width/10*7.2,winSize.height/10*7.6));
    market_bglayer->getParent()->addChild(now_item_img, true);
    
    //아이템 설명
    now_item_exp = CCLabelTTF::create(items[now], "Thonburi", 25);
    now_item_exp->setPosition(ccp(winSize.width/10*7.2,winSize.height/10*6));
    market_bglayer->getParent()->addChild(now_item_exp, true);
    
}

// 구매 버튼 눌렀을 때 호출되는 메소드
void MarketScene::buyItem(){
    
    
}

/*
 * 화살표 눌렀을 때 호출되는 메소드
 * 아래에서 슝 올라옴
 * Method when Direction Pointer is clicked
 * Shuuoong Move to Up from Under the Display
 */
void MarketScene::popup(){
    popoffMenuLayer->setVisible(false);
    
    popupMenuLayer = CCLayerColor::create(ccc4(255,0,255,255));
    popupMenuLayer->setAnchorPoint(CCPointZero);
    //Move Up from Under
    CCActionInterval* move = CCMoveTo::create(2, ccp(0,winSize.height/10*0.9));
    CCActionInterval* move_ease_out = CCEaseElasticOut::create((CCActionInterval*)(move->copy()->autorelease()));
    
    popupMenuLayer->setContentSize(CCSizeMake(0,0));
    
    CCMenuItemImage *pMenuMyroom = CCMenuItemImage::create("myroom_button_off.png","myroom_button_on.png", this, menu_selector(MarketScene::myroom));
    CCMenuItemImage *pMenuSchedule = CCMenuItemImage::create("schedule_button_off.png", "schedule_button_on.png", this, menu_selector(MarketScene::schedule));
    
    CCMenuItemImage *pMenuCloset = CCMenuItemImage::create("closet_button_off.png","closet_button_on.png",this, menu_selector(MarketScene::closet));
    
    CCMenuItemImage *pMenuDiary = CCMenuItemImage::create("diary_button_off.png", "diary_button_on.png", this, menu_selector(MarketScene::diary));
    
    CCMenuItemImage *pMenuPopoff = CCMenuItemImage::create("menu_button_on.png","menu_button_on.png",this, menu_selector(MarketScene::popoff));
    
    
    pMenuSchedule->setScale(winSize.width/3200*2.8);
    pMenuCloset->setScale(winSize.width/3200*2.8);
    pMenuDiary->setScale(winSize.width/3200*2.8);
    pMenuMyroom->setScale(winSize.width/3200*2.8);
    pMenuPopoff->setScale(winSize.width/3200*1.8);
    
    pMenuPopoff->setPosition(ccp(winSize.width/10*9,winSize.height/10*0.4));
    CCMenu* pMenu = CCMenu::create(pMenuMyroom,pMenuSchedule,pMenuCloset,pMenuDiary,pMenuPopoff,NULL);
    
    pMenu->alignItemsHorizontallyWithPadding(0.1);
    pMenu->setPosition(ccp(winSize.width/10*5,winSize.height/10*-0.1));
    popupMenuLayer->addChild(pMenu);
    popupMenuLayer->runAction(move_ease_out);
    market_bglayer->getParent()->getParent()->addChild(popupMenuLayer);
    
}
/*
 * x 아이콘을 눌렀을 때 사라지고 다시
 * 화살표가 나오도록 함
 * Direction Pointer appear when 'X' Button is clicked
 */
void MarketScene::popoff(){
    popupMenuLayer->setVisible(false);
    popoffMenuLayer->setVisible(true);
    popoffMenuLayer->setPosition(ccp(0,winSize.height/10*-0.1));
    
    //Move Up from Under
    CCActionInterval* move = CCMoveTo::create(2, ccp(0,winSize.height/10*0.1));
    CCActionInterval* move_ease_out = CCEaseElasticOut::create((CCActionInterval*)(move->copy()->autorelease()));
    popoffMenuLayer->runAction(move_ease_out);
}

//하단 메뉴 버튼들 onclick
void MarketScene::closet(){
    
    
}

void MarketScene::myroom(){
    
    CCScene* pScene = MyroomScene::scene();
    CCDirector::sharedDirector()->pushScene(pScene);
    
}

void MarketScene::diary(){
    
    
}

void MarketScene::schedule(){
    
    
}

void MarketScene::hairtap(){
 

    // 현재 탭 삭제
    tapMenu->removeFromParentAndCleanup(true);
    
    market_hair_button = CCMenuItemImage::create("market_hair_button_on.png", "market_hair_button_on.png", this, menu_selector(MarketScene::hairtap));
    
    market_top_button = CCMenuItemImage::create("market_top_button_off.png", "market_top_button_on.png", this, menu_selector(MarketScene::toptap));
    
    market_bottom_button = CCMenuItemImage::create("market_bottom_button_off.png", "market_bottom_button_on.png", this, menu_selector(MarketScene::bottomtap));
    
    market_shoes_button = CCMenuItemImage::create("market_shoes_button_off.png", "market_shoes_button_on.png", this, menu_selector(MarketScene::shoestap));
    
    market_etc_button = CCMenuItemImage::create("market_etc_button_off.png", "market_etc_button_on.png", this, menu_selector(MarketScene::etctap));
    
    tapMenu = CCMenu::create(market_hair_button, market_top_button, market_bottom_button,market_shoes_button, market_etc_button, NULL);
    
    tapMenu->alignItemsHorizontallyWithPadding(0);
    tapMenu->setScale(winSize.width/3200*2.5);
    tapMenu->setAnchorPoint(ccp(0,0));
    tapMenu->setPosition(ccp(winSize.width/10*5.03,winSize.height/10*3.2));
    market_bglayer->addChild(tapMenu, true);
}

void MarketScene::toptap(){
    
    // 현재 탭 삭제
    tapMenu->removeFromParentAndCleanup(true);
    
    market_hair_button = CCMenuItemImage::create("market_hair_button_off.png", "market_hair_button_on.png", this, menu_selector(MarketScene::hairtap));
    
    market_top_button = CCMenuItemImage::create("market_top_button_on.png", "market_top_button_on.png", this, menu_selector(MarketScene::toptap));
    
    market_bottom_button = CCMenuItemImage::create("market_bottom_button_off.png", "market_bottom_button_on.png", this, menu_selector(MarketScene::bottomtap));
    
    market_shoes_button = CCMenuItemImage::create("market_shoes_button_off.png", "market_shoes_button_on.png", this, menu_selector(MarketScene::shoestap));
    
    market_etc_button = CCMenuItemImage::create("market_etc_button_off.png", "market_etc_button_on.png", this, menu_selector(MarketScene::etctap));
    
    tapMenu = CCMenu::create(market_hair_button, market_top_button, market_bottom_button,market_shoes_button, market_etc_button, NULL);
    
    tapMenu->alignItemsHorizontallyWithPadding(0);
    tapMenu->setScale(winSize.width/3200*2.5);
    tapMenu->setAnchorPoint(ccp(0,0));
    tapMenu->setPosition(ccp(winSize.width/10*5.03,winSize.height/10*3.2));
    market_bglayer->addChild(tapMenu, true);
}

void MarketScene::bottomtap(){
    
    // 현재 탭 삭제
    tapMenu->removeFromParentAndCleanup(true);
    
    market_hair_button = CCMenuItemImage::create("market_hair_button_off.png", "market_hair_button_on.png", this, menu_selector(MarketScene::hairtap));
    
    market_top_button = CCMenuItemImage::create("market_top_button_off.png", "market_top_button_on.png", this, menu_selector(MarketScene::toptap));
    
    market_bottom_button = CCMenuItemImage::create("market_bottom_button_on.png", "market_bottom_button_on.png", this, menu_selector(MarketScene::bottomtap));
    
    market_shoes_button = CCMenuItemImage::create("market_shoes_button_off.png", "market_shoes_button_on.png", this, menu_selector(MarketScene::shoestap));
    
    market_etc_button = CCMenuItemImage::create("market_etc_button_off.png", "market_etc_button_on.png", this, menu_selector(MarketScene::etctap));
    
    tapMenu = CCMenu::create(market_hair_button, market_top_button, market_bottom_button,market_shoes_button, market_etc_button, NULL);
    
    tapMenu->alignItemsHorizontallyWithPadding(0);
    tapMenu->setScale(winSize.width/3200*2.5);
    tapMenu->setAnchorPoint(ccp(0,0));
    tapMenu->setPosition(ccp(winSize.width/10*5.03,winSize.height/10*3.2));
    market_bglayer->addChild(tapMenu, true);
}

void MarketScene::shoestap(){
    
    // 현재 탭 삭제
    tapMenu->removeFromParentAndCleanup(true);
    
    market_hair_button = CCMenuItemImage::create("market_hair_button_off.png", "market_hair_button_on.png", this, menu_selector(MarketScene::hairtap));
    
    market_top_button = CCMenuItemImage::create("market_top_button_off.png", "market_top_button_on.png", this, menu_selector(MarketScene::toptap));
    
    market_bottom_button = CCMenuItemImage::create("market_bottom_button_off.png", "market_bottom_button_on.png", this, menu_selector(MarketScene::bottomtap));
    
    market_shoes_button = CCMenuItemImage::create("market_shoes_button_on.png", "market_shoes_button_on.png", this, menu_selector(MarketScene::shoestap));
    
    market_etc_button = CCMenuItemImage::create("market_etc_button_off.png", "market_etc_button_on.png", this, menu_selector(MarketScene::etctap));
    
    tapMenu = CCMenu::create(market_hair_button, market_top_button, market_bottom_button,market_shoes_button, market_etc_button, NULL);
    
    tapMenu->alignItemsHorizontallyWithPadding(0);
    tapMenu->setScale(winSize.width/3200*2.5);
    tapMenu->setAnchorPoint(ccp(0,0));
    tapMenu->setPosition(ccp(winSize.width/10*5.03,winSize.height/10*3.2));
    market_bglayer->addChild(tapMenu, true);
}

void MarketScene::etctap(){
    
    // 현재 탭 삭제
    tapMenu->removeFromParentAndCleanup(true);
    
    market_hair_button = CCMenuItemImage::create("market_hair_button_off.png", "market_hair_button_on.png", this, menu_selector(MarketScene::hairtap));
    
    market_top_button = CCMenuItemImage::create("market_top_button_off.png", "market_top_button_on.png", this, menu_selector(MarketScene::toptap));
    
    market_bottom_button = CCMenuItemImage::create("market_bottom_button_off.png", "market_bottom_button_on.png", this, menu_selector(MarketScene::bottomtap));
    
    market_shoes_button = CCMenuItemImage::create("market_shoes_button_off.png", "market_shoes_button_on.png", this, menu_selector(MarketScene::shoestap));
    
    market_etc_button = CCMenuItemImage::create("market_etc_button_on.png", "market_etc_button_on.png", this, menu_selector(MarketScene::etctap));
    
    tapMenu = CCMenu::create(market_hair_button, market_top_button, market_bottom_button,market_shoes_button, market_etc_button, NULL);
    
    tapMenu->alignItemsHorizontallyWithPadding(0);
    tapMenu->setScale(winSize.width/3200*2.5);
    tapMenu->setAnchorPoint(ccp(0,0));
    tapMenu->setPosition(ccp(winSize.width/10*5.03,winSize.height/10*3.2));
    market_bglayer->addChild(tapMenu, true);
}
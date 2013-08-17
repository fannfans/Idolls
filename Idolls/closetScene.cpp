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

CCSprite *now_item_hair, *now_item_top, *now_item_bottom ; //현재 착용 아이템들
CCLayer *item_now_scroll; // 현재 착용 아이템 스크롤
CCLayer *closet_tab_layer; // 옷장 탭 부분 레이어
CCLayer *closet_scroll_layer; // 옷장 탭 스크롤
CCSprite *itemPrev, *itemNow, *itemNext ; //현재 보여지는 아이템들
CCArray *itemArray ; // 아이템 배열


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
    
    closet_bglayer = CCLayer::create();
    closet_bglayer->setAnchorPoint(ccp(0.5,0.5));
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
    closetMenu->setPosition(ccp(winSize.width/10*2.9,winSize.height/10*4.5));
    closet_bglayer->getParent()->addChild(closetMenu);
    
    // 현재 착용 아이템들
    now_item_hair = CCSprite::create("item1.png");
    now_item_hair->setScale(winSize.width/3200*5);
    now_item_hair->setPosition(ccp(winSize.width/10*1,winSize.height/10*1));
    
    now_item_top = CCSprite::create("item2.png");
    now_item_top->setScale(winSize.width/3200*5);
    now_item_top->setPosition(ccp(winSize.width/10*4,winSize.height/10*1));
    
    now_item_bottom = CCSprite::create("item3.png");
    now_item_bottom->setScale(winSize.width/3200*5);
    now_item_bottom->setPosition(ccp(winSize.width/10*7,winSize.height/10*1));
    
    //현재 착용 아이템 레이어(스크롤)
    item_now_scroll = CCLayerColor::create(ccc4(240,20,50,255));
    item_now_scroll->setAnchorPoint(CCPointZero);
    item_now_scroll->setPosition(ccp(10,0));
    item_now_scroll->setContentSize(CCSizeMake(winSize.width/10*5,winSize.height/10*1));
    
    item_now_scroll->addChild(now_item_hair);
    item_now_scroll->addChild(now_item_top);
    item_now_scroll->addChild(now_item_bottom);
    
    now_scroll= CCScrollView::create();
    now_scroll->retain();
    now_scroll->setAnchorPoint(ccp(0.5,0.5));
    now_scroll->setDirection(kCCScrollViewDirectionHorizontal);
    now_scroll->setViewSize(CCSizeMake(winSize.width/10*8,winSize.height/10*3));
    now_scroll->setContentSize(bglayer->getContentSize());
    now_scroll->setContentOffset(ccp(0,0), false);
    now_scroll->setPosition(ccp(winSize.width/10*3,winSize.height/10*6));
    now_scroll->setContainer(item_now_scroll);
    now_scroll->setDelegate(this);
    
    closet_bglayer->addChild(now_scroll);
    
    
    // 옷장 탭 레이어
    closet_tab_layer = CCLayer::create();
    closet_tab_layer->setAnchorPoint(ccp(0,0));
    closet_tab_layer->setPosition(ccp(winSize.width/10*2,winSize.height/10*1));
    closet_tab_layer->setContentSize(CCSizeMake(320,300));
    
    //옷장 탭 박스
    CCSprite *closet_tab_box = CCSprite::create();
    closet_tab_box->setAnchorPoint(ccp(0.5,0.5));
    closet_tab_box->setScale(winSize.width/3200*2.5);
    closet_tab_box->setPosition(ccp(winSize.width/10*3.05,winSize.height/10*2));
    
    this->addChild(closet_tab_layer);
    closet_tab_layer->addChild(closet_tab_box);
    
    // 옷장 탭
    CCMenuItemImage *closet_hair_button = CCMenuItemImage::create("closet_hair_button_on.png","closet_hair_button_on.png",this, menu_selector(ClosetScene::hair));
    
    CCMenuItemImage *closet_top_button = CCMenuItemImage::create("closet_top_button_off.png","closet_top_button_on.png",this, menu_selector(ClosetScene::top));
    
    CCMenuItemImage *closet_bottom_button = CCMenuItemImage::create("closet_bottom_button_off.png","closet_bottom_button_on.png",this, menu_selector(ClosetScene::bottom));
    
    CCMenuItemImage *closet_shoes_button = CCMenuItemImage::create("closet_shoes_button_off.png","closet_shoes_button_on.png",this, menu_selector(ClosetScene::shoes));
    
    CCMenuItemImage *closet_etc_button = CCMenuItemImage::create("closet_etc_button_off.png","closet_etc_button_on.png",this, menu_selector(ClosetScene::etc));
    
    CCMenu* closetTab = CCMenu::create(closet_hair_button , closet_top_button, closet_bottom_button, closet_shoes_button, closet_etc_button, NULL);
    
    closetTab->alignItemsHorizontally();
    closetTab->setAnchorPoint(ccp(0,0));
    closetTab->setScale(winSize.width/3200*2.5);
    closetTab->setPosition(ccp(winSize.width/10*3,winSize.height/10*4.05));
    closet_tab_layer->addChild(closetTab);
    
    itemArray = CCArray::createWithCapacity(20);

    //탭 박스 아이템들
    itemPrev = CCSprite::create("item1.png");
    itemPrev->setScale(winSize.width/3200*5);
    itemPrev->setPosition(ccp(winSize.width/10*1,winSize.height/10*1));
    
    itemNow = CCSprite::create("item2.png");
    itemNow->setScale(winSize.width/3200*7.5);
    itemNow->setPosition(ccp(winSize.width/10*4,winSize.height/10*1));
    
    itemNext = CCSprite::create("item3.png");
    itemNext->setScale(winSize.width/3200*5);
    itemNext->setPosition(ccp(winSize.width/10*7,winSize.height/10*1));
    
    //탭 박스 스크롤 레이어
    closet_scroll_layer= CCLayer::create();
    closet_scroll_layer->setAnchorPoint(CCPointZero);
    closet_scroll_layer->setPosition(ccp(10,0));
    closet_scroll_layer->setContentSize(CCSizeMake(winSize.width/10*8,winSize.height/10*2));
    
    closet_scroll_layer->addChild(itemPrev);
    closet_scroll_layer->addChild(itemNow);
    closet_scroll_layer->addChild(itemNext);
    
    closet_scroll= CCScrollView::create();
    closet_scroll->retain();
    closet_scroll->setAnchorPoint(ccp(0.5,0.5));
    closet_scroll->setDirection(kCCScrollViewDirectionHorizontal);
    closet_scroll->setViewSize(CCSizeMake(winSize.width/10*8,winSize.height/10*3));
    closet_scroll->setContentSize(bglayer->getContentSize());
    closet_scroll->setContentOffset(ccp(0,0), false);
    closet_scroll->setPosition(ccp(winSize.width/10*(-1),winSize.height/10*1));
    closet_scroll->setContainer(closet_scroll_layer);
    closet_scroll->setDelegate(this);
    
    closet_tab_layer->addChild(closet_scroll);
    
    
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

void ClosetScene::onEnter(){
    
    //    CCLayer::onEnter();
    //    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCLayer::onEnter();
    
}

void ClosetScene::onExit(){
    
    //    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    //    CCLayer::onExit();
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    
    CCLayer::onExit();
}


void ClosetScene::scrollViewDidScroll(cocos2d::extension::CCScrollView *view){
    
}

void ClosetScene::scrollViewDidZoom(cocos2d::extension::CCScrollView *view){
    
    
}

bool ClosetScene::ccTouchBegan(CCTouch *pTouch, CCEvent* event){
    CCPoint touchPoint = pTouch->getLocation();
    CCLOG("Touches Began....(%f, %f)",touchPoint.x,touchPoint.y);
    return true;
}
void ClosetScene::ccTouchMoved(CCTouch *pTouch, CCEvent* event){
    CCPoint touchPoint = pTouch->getLocation();
    CCLOG("Touches Moved....(%f,%f)",touchPoint.x, touchPoint.y);
}
//터치 후 손가락을 화면에서 뗐을 때 캐릭터이동
void ClosetScene::ccTouchEnded(CCTouch *pTouch, CCEvent* event){

    CCPoint touchPoint = pTouch->getLocation();
    
    itemPrev->removeFromParentAndCleanup(true);
    itemNow->removeFromParentAndCleanup(true);
    itemNext->removeFromParentAndCleanup(true);
    
    itemPrev = CCSprite::create("item2.png");
    itemPrev->setScale(winSize.width/3200*5);
    itemPrev->setPosition(ccp(winSize.width/10*1,winSize.height/10*1));
    
    itemNow = CCSprite::create("item3.png");
    itemNow->setScale(winSize.width/3200*7.5);
    itemNow->setPosition(ccp(winSize.width/10*4,winSize.height/10*1));
    
    itemNext = CCSprite::create("item4.png");
    itemNext->setScale(winSize.width/3200*5);
    itemNext->setPosition(ccp(winSize.width/10*7,winSize.height/10*1));
    
    //탭 박스 스크롤 레이어
    /*
    closet_scroll_layer= CCLayer::create();
    closet_scroll_layer->setAnchorPoint(CCPointZero);
    closet_scroll_layer->setPosition(ccp(10,0));
    closet_scroll_layer->setContentSize(CCSizeMake(winSize.width/10*8,winSize.height/10*2));
    */
    closet_scroll_layer->addChild(itemPrev,true);
    closet_scroll_layer->addChild(itemNow, true);
    closet_scroll_layer->addChild(itemNext, true);
    
    //CCMoveTo* chMove = CCMoveTo::create(2,ccp(touchPoint.x, touchPoint.y));

    CCLOG("Touches Endeds....(%f, %f)",touchPoint.x, touchPoint.y);
}

void ClosetScene::ccTouchCancelled(CCTouch *pTouch, CCEvent* event){
    CCLOG("Touches Cancelled");
    
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

// 헤어 탭 누르면
void ClosetScene::hair(){
    
    closet_tab_layer->setVisible(false);
    
    CCMenuItemImage *closet_hair_button = CCMenuItemImage::create("closet_hair_button_on.png","closet_hair_button_on.png",this, menu_selector(ClosetScene::hair));
    
    CCMenuItemImage *closet_top_button = CCMenuItemImage::create("closet_top_button_off.png","closet_top_button_on.png",this, menu_selector(ClosetScene::top));
    
    CCMenuItemImage *closet_bottom_button = CCMenuItemImage::create("closet_bottom_button_off.png","closet_bottom_button_on.png",this, menu_selector(ClosetScene::bottom));
    
    CCMenuItemImage *closet_shoes_button = CCMenuItemImage::create("closet_shoes_button_off.png","closet_shoes_button_on.png",this, menu_selector(ClosetScene::shoes));
    
    CCMenuItemImage *closet_etc_button = CCMenuItemImage::create("closet_etc_button_off.png","closet_etc_button_on.png",this, menu_selector(ClosetScene::etc));
    
    CCMenu* closetTab = CCMenu::create(closet_hair_button , closet_top_button, closet_bottom_button, closet_shoes_button, closet_etc_button, NULL);
    
    closetTab->alignItemsHorizontally();
    closetTab->setAnchorPoint(ccp(0,0));
    closetTab->setScale(winSize.width/3200*2.5);
    closetTab->setPosition(ccp(winSize.width/10*3,winSize.height/10*4.05));
    closet_tab_layer->addChild(closetTab);
    
    closet_tab_layer->setVisible(true);
    
    
    
}

// 상의 탭 누르면
void ClosetScene::top(){
    closet_tab_layer->setVisible(false);
    
    // 옷장 탭
    CCMenuItemImage *closet_hair_button = CCMenuItemImage::create("closet_hair_button_off.png","closet_hair_button_on.png",this, menu_selector(ClosetScene::hair));
    
    CCMenuItemImage *closet_top_button = CCMenuItemImage::create("closet_top_button_on.png","closet_top_button_on.png",this, menu_selector(ClosetScene::top));
    
    CCMenuItemImage *closet_bottom_button = CCMenuItemImage::create("closet_bottom_button_off.png","closet_bottom_button_on.png",this, menu_selector(ClosetScene::bottom));
    
    CCMenuItemImage *closet_shoes_button = CCMenuItemImage::create("closet_shoes_button_off.png","closet_shoes_button_on.png",this, menu_selector(ClosetScene::shoes));
    
    CCMenuItemImage *closet_etc_button = CCMenuItemImage::create("closet_etc_button_off.png","closet_etc_button_on.png",this, menu_selector(ClosetScene::etc));
    
    CCMenu* closetTab = CCMenu::create(closet_hair_button , closet_top_button, closet_bottom_button, closet_shoes_button, closet_etc_button, NULL);
    
    closetTab->alignItemsHorizontally();
    closetTab->setAnchorPoint(ccp(0,0));
    closetTab->setScale(winSize.width/3200*2.5);
    closetTab->setPosition(ccp(winSize.width/10*3,winSize.height/10*4.05));
    closet_tab_layer->addChild(closetTab);
    
    closet_tab_layer->setVisible(true);
}

//하의 탭 누르면
void ClosetScene::bottom(){
    closet_tab_layer->setVisible(false);
    
    // 옷장 탭
    CCMenuItemImage *closet_hair_button = CCMenuItemImage::create("closet_hair_button_off.png","closet_hair_button_on.png",this, menu_selector(ClosetScene::hair));
    
    CCMenuItemImage *closet_top_button = CCMenuItemImage::create("closet_top_button_off.png","closet_top_button_on.png",this, menu_selector(ClosetScene::top));
    
    CCMenuItemImage *closet_bottom_button = CCMenuItemImage::create("closet_bottom_button_on.png","closet_bottom_button_on.png",this, menu_selector(ClosetScene::bottom));
    
    CCMenuItemImage *closet_shoes_button = CCMenuItemImage::create("closet_shoes_button_off.png","closet_shoes_button_on.png",this, menu_selector(ClosetScene::shoes));
    
    CCMenuItemImage *closet_etc_button = CCMenuItemImage::create("closet_etc_button_off.png","closet_etc_button_on.png",this, menu_selector(ClosetScene::etc));
    
    CCMenu* closetTab = CCMenu::create(closet_hair_button , closet_top_button, closet_bottom_button, closet_shoes_button, closet_etc_button, NULL);
    
    closetTab->alignItemsHorizontally();
    closetTab->setAnchorPoint(ccp(0,0));
    closetTab->setScale(winSize.width/3200*2.5);
    closetTab->setPosition(ccp(winSize.width/10*3,winSize.height/10*4.05));
    closet_tab_layer->addChild(closetTab);
    
    closet_tab_layer->setVisible(true);
}

// 신발 탭 누르면
void ClosetScene::shoes(){
    
    closet_tab_layer->setVisible(false);
    
    // 옷장 탭
    CCMenuItemImage *closet_hair_button = CCMenuItemImage::create("closet_hair_button_off.png","closet_hair_button_on.png",this, menu_selector(ClosetScene::hair));
    
    CCMenuItemImage *closet_top_button = CCMenuItemImage::create("closet_top_button_off.png","closet_top_button_on.png",this, menu_selector(ClosetScene::top));
    
    CCMenuItemImage *closet_bottom_button = CCMenuItemImage::create("closet_bottom_button_off.png","closet_bottom_button_on.png",this, menu_selector(ClosetScene::bottom));
    
    CCMenuItemImage *closet_shoes_button = CCMenuItemImage::create("closet_shoes_button_on.png","closet_shoes_button_on.png",this, menu_selector(ClosetScene::shoes));
    
    CCMenuItemImage *closet_etc_button = CCMenuItemImage::create("closet_etc_button_off.png","closet_etc_button_on.png",this, menu_selector(ClosetScene::etc));
    
    CCMenu* closetTab = CCMenu::create(closet_hair_button , closet_top_button, closet_bottom_button, closet_shoes_button, closet_etc_button, NULL);
    
    closetTab->alignItemsHorizontally();
    closetTab->setAnchorPoint(ccp(0,0));
    closetTab->setScale(winSize.width/3200*2.5);
    closetTab->setPosition(ccp(winSize.width/10*3,winSize.height/10*4.05));
    closet_tab_layer->addChild(closetTab);
    
    closet_tab_layer->setVisible(true);
}

// 기타 탭 누르면
void ClosetScene::etc(){
    
    closet_tab_layer->setVisible(false);
    
    // 옷장 탭
    CCMenuItemImage *closet_hair_button = CCMenuItemImage::create("closet_hair_button_off.png","closet_hair_button_on.png",this, menu_selector(ClosetScene::hair));
    
    CCMenuItemImage *closet_top_button = CCMenuItemImage::create("closet_top_button_off.png","closet_top_button_on.png",this, menu_selector(ClosetScene::top));
    
    CCMenuItemImage *closet_bottom_button = CCMenuItemImage::create("closet_bottom_button_off.png","closet_bottom_button_on.png",this, menu_selector(ClosetScene::bottom));
    
    CCMenuItemImage *closet_shoes_button = CCMenuItemImage::create("closet_shoes_button_off.png","closet_shoes_button_on.png",this, menu_selector(ClosetScene::shoes));
    
    CCMenuItemImage *closet_etc_button = CCMenuItemImage::create("closet_etc_button_on.png","closet_etc_button_on.png",this, menu_selector(ClosetScene::etc));
    
    CCMenu* closetTab = CCMenu::create(closet_hair_button , closet_top_button, closet_bottom_button, closet_shoes_button, closet_etc_button, NULL);
    
    closetTab->alignItemsHorizontally();
    closetTab->setAnchorPoint(ccp(0,0));
    closetTab->setScale(winSize.width/3200*2.5);
    closetTab->setPosition(ccp(winSize.width/10*3,winSize.height/10*4.05));
    closet_tab_layer->addChild(closetTab);
    
    closet_tab_layer->setVisible(true);
}
//
//  MyroomScene.cpp
//  Idolls
//
//  Created by 효은 김 on 13. 7. 24..
//
//

#include "MyroomScene.h"
#include "global.h"

using namespace cocos2d;


#define IMG_WIDTH 441



CCLayerColor *bglayer;
CCSprite *bg1; //마이룸 배경
CCLayer *toplayer;

bool scroll_flag = false ;
bool start_flag = true ;
//애니메이션 변수들
CCAnimation *animation;
CCAnimate *animate;
CCAction * rep;

CCPoint startPoint;
CCPoint endPoint;
CCPoint movePoint ;

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
    bg1= CCSprite::create("myroom_background_bluever.png");
    bg1->setAnchorPoint(ccp(0.5,0.5));
    bg1->setScale(winSize.width/3200*2.5);
    bg1->setPosition(ccp(winSize.width/2,winSize.height/2));

    bglayer= CCLayerColor::create(ccc4(255,0,255,0));
    bglayer->setAnchorPoint(CCPointZero);
    bglayer->setPosition(ccp(0,0));
    bglayer->setContentSize(CCSizeMake(winSize.width/320*320,winSize.height/480*480));
    bglayer->addChild(bg1);
    
    // 스크롤 뷰
    scrollView = CCScrollView::create();
    scrollView->retain();
    scrollView->setDirection(kCCScrollViewDirectionHorizontal);
    scrollView->setViewSize(CCSizeMake(winSize.width/320*320,winSize.height/480*480));
    scrollView->setContentSize(bglayer->getContentSize());
    scrollView->setContentOffset(ccp(0,0), true);
    scrollView->setPosition(ccp(0,0));
    scrollView->setContainer(bglayer);
    scrollView->setDelegate(this);
    this->addChild(scrollView,1);
    
    // 버튼 레이어
    toplayer = CCLayer::create();
    toplayer->setAnchorPoint(CCPointZero);
    toplayer->setPosition(ccp(0,0));
    toplayer->setContentSize(CCSizeMake(winSize.width/320*320,winSize.height/480*480));
    this->addChild(toplayer,2);
    
    //    캐릭터
    maincharacter = CCSprite::create("character1.png");
    maincharacter->setAnchorPoint(ccp(0,0));
    maincharacter->setScale(winSize.width/3200*1.5);
    maincharacter->setPosition(ccp(100,150));
    bglayer->addChild(maincharacter);
    
    //    캐릭터애니메이션
    animation = CCAnimation::create();
    animation->setDelayPerUnit(0.3);
    animation->addSpriteFrameWithFileName("character2.png");
    animation->addSpriteFrameWithFileName("character3.png");
    animation->addSpriteFrameWithFileName("character4.png");
    animate = CCAnimate::create(animation);
    rep = CCRepeatForever::create(animate);
    maincharacter->runAction(rep);
    
    //    헤더 코인/스타
    money_star_button = CCMenuItemImage::create("money_star_button.png","money_star_button.png",this, menu_selector(MyroomScene::stars));
    
    money_coin_button = CCMenuItemImage::create("money_coin_button.png","money_coin_button.png",this, menu_selector(MyroomScene::coins));
    
    CCMenu* moneyMenu = CCMenu::create(money_star_button, money_coin_button, NULL);
    
    moneyMenu->alignItemsHorizontally();
    moneyMenu->setScale(winSize.width/3200*1.8);
    moneyMenu->setPosition(ccp(winSize.width/10*2.5,winSize.height/10*5.5));
    toplayer->addChild(moneyMenu);
    
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
    toplayer->addChild(popoffMenuLayer);
    
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
    startPoint = pTouch->getLocation();
    CCLOG("Touches Began....(%f, %f)",startPoint.x,startPoint.y);
    return true;
}

// 스크롤
void MyroomScene::ccTouchMoved(CCTouch *pTouch, CCEvent* event){
    CCPoint touchPoint = pTouch->getLocation();
    //CCLOG("Touches Moved....(%f,%f)",touchPoint.x, touchPoint.y);
    //시작시 스크롤 멈추기
    start_flag=false;
    scroll_flag=true;
}

//터치 후 손가락을 화면에서 뗐을 때 캐릭터이동
void MyroomScene::ccTouchEnded(CCTouch *pTouch, CCEvent* event){
    endPoint = pTouch->getLocation();

    CCLOG("Touches Endeds....(%f, %f)",endPoint.x, endPoint.y);
    
    /*scroll_flag==true이면 스크롤한 경우 */
    if (scroll_flag) {
        
        CCPoint difference ;
        difference.x = endPoint.x - startPoint.x;
        
        // 좌우 스크롤 구분
        if(difference.x>0){
            movePoint.x = movePoint.x + difference.x ;
            movePoint.y = 0;
            if(movePoint.x>120){
                movePoint.x = 120;
            }
        }
        else{
            movePoint.x = movePoint.x + difference.x ;
            movePoint.y = 0;
            
            if(movePoint.x<-120){
                movePoint.x = -120;
            }
        }
        // 현재 배경 삭제
        bglayer->setVisible(false);
        scrollView->removeFromParentAndCleanup(true);

        // 배경 위치 바꾸기
        bglayer->setPosition(CCPoint(movePoint.x,0));
        bglayer->setVisible(true);
        this->addChild(scrollView,1);
        scroll_flag=false;
    }
    /*화면을 터치한경우 = 캐릭터 움직임*/
    else{
        // 터치 영역 제한
        if(endPoint.y>150){
            endPoint.y = 150 ;
        }
        if(endPoint.y<50){
            endPoint.y=50;
        }
        CCMoveTo* chMove = CCMoveTo::create(2,ccp(endPoint.x, endPoint.y));
        maincharacter->runAction(chMove);        
    }
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
    CCMenuItemImage *pMenuSchedule = CCMenuItemImage::create("schedule_button_off.png", "schedule_button_on.png", this, menu_selector(MyroomScene::schedule));
    CCMenuItemImage *pMenuCloset = CCMenuItemImage::create("closet_button_off.png","closet_button_on.png",this, menu_selector(MyroomScene::closet));
    CCMenuItemImage *pMenuDiary = CCMenuItemImage::create("diary_button_off.png", "diary_button_on.png", this, menu_selector(MyroomScene::diary));
    CCMenuItemImage *pMenuMarket = CCMenuItemImage::create("market_button_off.png","market_button_on.png", this, menu_selector(MyroomScene::market));
    CCMenuItemImage *pMenuPopoff = CCMenuItemImage::create("menu_button_on.png","menu_button_on.png",this, menu_selector(MyroomScene::popoff));
    
    
    pMenuSchedule->setScale(winSize.width/3200*2.8);
    pMenuCloset->setScale(winSize.width/3200*2.8);
    pMenuDiary->setScale(winSize.width/3200*2.8);
    pMenuMarket->setScale(winSize.width/3200*2.8);
    pMenuPopoff->setScale(winSize.width/3200*1.8);
    
    pMenuPopoff->setPosition(ccp(winSize.width/10*9,winSize.height/10*0.4));
    CCMenu* pMenu = CCMenu::create(pMenuSchedule,pMenuCloset,pMenuDiary,pMenuMarket,pMenuPopoff,NULL);
    
    pMenu->alignItemsHorizontally();
    pMenu->alignItemsHorizontallyWithPadding(0.1);
    pMenu->setPosition(ccp(winSize.width/10*5,winSize.height/10*-0.1));
    popupMenuLayer->addChild(pMenu);
    popupMenuLayer->runAction(move_ease_out);
    toplayer->addChild(popupMenuLayer);
    
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
    
}
void MyroomScene::diary(){
    
}
void MyroomScene::market(){
    
}
void MyroomScene::stars(){
    
}
void MyroomScene::coins(){
    
}
//
//  ScheduleScene.cpp
//  Idolls
//
//  Created by 박성수 on 13. 8. 13..
//
//

#include "ScheduleScene.h"
#include "global.h"

using namespace cocos2d;

CCSprite *scheduleBg;
CCMenu *scheduleMenu;

CCScene* ScheduleScene::scene()
{
    CCScene *scene = CCScene::create();
    
    ScheduleScene *layer = ScheduleScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool ScheduleScene::init()
{
    if(!CCLayerColor::initWithColor(ccc4(255,255,255,255)))
    {
        return false;
    }
    /*
     * 스케쥴 배경화면
     * Schedule Background
     */
    schedule_bg_set();
        
    // 코인, 스타메뉴 추가 ( Coins, Star Menu Add)  / Z-order is 50
    Schedulebglayer->addChild(moneyMenu,50);
        
    /* 스케쥴 수행하기 버튼 메뉴
     * Schedule Doing Button Menu
     */
    CCMenuItemImage *sm1 = CCMenuItemImage::create("schedule_do_button_on.png","schedule_do_button_on.png",this,menu_selector(ScheduleScene::schedule_do_layer));
    CCMenuItemImage *sm2 = CCMenuItemImage::create("schedule_do_button_on.png","schedule_do_button_on.png",this,menu_selector(ScheduleScene::schedule_do_layer));
    scheduleMenu = CCMenu::create(sm1, sm2, NULL);
    scheduleMenu->alignItemsVertically();
    scheduleMenu->setScale(winSize.width/3200*1.8);
    scheduleMenu->setPosition(ccp(winSize.width/320*2,winSize.height/480*1.8));

    // 스케쥴 팝업화면 ( Schedule Popup Layer )
    schedule_do_set();
    
    this->addChild(Schedulebglayer);
    this->addChild(scheduleMenu);

    return true;

}
// 스케쥴 메인 배경화면 세팅
void ScheduleScene::schedule_bg_set(){
    scheduleBg = CCSprite::create("myroom_background.png");
    scheduleBg->setScale(winSize.width/3200*2.5);
    scheduleBg->setPosition(ccp(winSize.width/2, winSize.height/2));
    
    Schedulebglayer = CCLayerColor::create(ccc4(255,0,255,255));
    Schedulebglayer->setPosition(ccp(0,0));
    Schedulebglayer->setContentSize(CCSizeMake(winSize.width,winSize.height));
    
    Schedulebglayer->addChild(scheduleBg);    
}
// 수행하기 레이어 세팅
void ScheduleScene::schedule_do_set(){
    //팝업레이어
    SchedulePopupLayer = CCLayerColor::create(ccc4(0,0,0,0));
    //화면 2^4로 나눈 위치에 위치시킴
    CCLOG("POPUP Layer Position : ( %f, %f )", winSize.width/16, winSize.height/16);
    //팝업레이어 사이즈 임시로 그려놨음(비율X)
    //    SchedulePopupLayer->setContentSize(CCSizeMake(winSize.width-40,winSize.height-80));
    //    SchedulePopupLayer->setPosition(ccp(winSize.width/16,winSize.height/16));
    SchedulePopupLayer->setContentSize(CCSizeMake(winSize.width,winSize.height));
    SchedulePopupLayer->setPosition(ccp(0,0));
    SchedulePopupLayer->setOpacity(180);
    
    //팝업 배경레이어
    CCSprite *schedule_popup_bg = CCSprite::create("schedule_popup_bg.png");
    schedule_popup_bg->setScaleX(winSize.width/3200*9.5);
    //    schedule_popup_bg->setScaleY(winSize.height/3200*7);
    schedule_popup_bg->setPosition(ccp(winSize.width/2,(winSize.height-40)/2));
    SchedulePopupLayer->addChild(schedule_popup_bg);
    
    Schedulebglayer->addChild(SchedulePopupLayer);
    
    SchedulePopupLayer->setVisible(false);
}
// 수행하기 레이어
void ScheduleScene::schedule_do_layer(){
    scheduleMenu->setVisible(false); // 수행하기버튼 안보이게
    SchedulePopupLayer->setVisible(true);
}

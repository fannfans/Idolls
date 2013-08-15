//
//  global.cpp
//  Idolls
//
//  Created by 효은 김 on 13. 8. 13..
//
//

#include "global.h"

using namespace cocos2d;

CCSize winSize ; // device 사이즈

//하단 메뉴
CCLayerColor *popoffMenuLayer;
CCLayerColor *popupMenuLayer;

//메인캐릭터
CCSprite* maincharacter;

// 상단 스타/코인
CCMenuItemImage *money_star_button;
CCMenuItemImage *money_coin_button;
CCMenu *moneyMenu;


/* ScheduleScene 부분 */
CCLayerColor *Schedulebglayer;
CCLayerColor *SchedulePopupLayer;
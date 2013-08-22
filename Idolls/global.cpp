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

CCLayerColor *bglayer; // 마이룸 배경 레이어
CCLayerColor *closet_bglayer; //옷장 배경 레이어
CCLayerColor *market_bglayer; // 상점 배경 레이어

//하단 메뉴
CCLayerColor *popoffMenuLayer;
CCLayerColor *popupMenuLayer;

//메인캐릭터
CCSprite* maincharacter;

// 상단 스타/코인
CCMenuItemImage *money_star_button;
CCMenuItemImage *money_coin_button;
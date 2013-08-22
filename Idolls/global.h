//
//  global.h
//  Idolls
//
//  Created by 효은 김 on 13. 8. 13..
//
//

#ifndef __Idolls__global__
#define __Idolls__global__

#include "cocos2d.h"
#include "cocos-ext.h"

extern cocos2d::CCSize winSize ; //device 사이즈

extern cocos2d::CCLayerColor *bglayer; //마이룸 배경 레이어
extern cocos2d::CCLayerColor *closet_bglayer; //옷장 배경레이어
extern cocos2d::CCLayerColor *market_bglayer; // 상점 배경 레이어

//하단 메뉴
extern cocos2d::CCLayerColor *popoffMenuLayer;
extern cocos2d::CCLayerColor *popupMenuLayer;

extern cocos2d::CCSprite* maincharacter; //메인캐릭터

//상단 스타/코인
extern cocos2d::CCMenuItemImage *money_star_button;
extern cocos2d::CCMenuItemImage *money_coin_button;

#endif /* defined(__Idolls__global__) */

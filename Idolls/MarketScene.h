//
//  marketScene.h
//  Idolls
//
//  Created by 효은 김 on 13. 7. 31..
//
//

#ifndef __Idolls__marketScene__
#define __Idolls__marketScene__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MarketScene : public cocos2d::CCLayerColor,public CCScrollViewDelegate{
    
public:
    
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    
    CREATE_FUNC(MarketScene);
    
    // 스크롤뷰 메소드, 변수들
    virtual void onEnter();
    virtual void onExit();
    
    void scrollViewDidScroll(CCScrollView* view);
    void scrollViewDidZoom(CCScrollView* view);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    CCScrollView *market_item_scroll ;
    CCLayerColor *market_item_layer;
    
    // 스타/코인 버튼
    virtual void chargeStar();
    virtual void chargeCoin();
    
    // 상점 삭제,초기화,구매 버튼
    virtual void buyItem();
    
    // 아이템 탭
    virtual void hairtap();
    virtual void toptap();
    virtual void bottomtap();
    virtual void shoestap();
    virtual void etctap();
    
    //하단 메뉴
    virtual void closet();
    virtual void myroom();
    virtual void diary();
    virtual void schedule();
    
    virtual void popup();
    virtual void popoff();
};

#endif /* defined(__Idolls__marketScene__) */

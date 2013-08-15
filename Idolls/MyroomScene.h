//
//  MyroomScene.h
//  Idolls
//
//  Created by 효은 김 on 13. 7. 24..
//
//

#ifndef __Idolls__MyroomScene__
#define __Idolls__MyroomScene__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;


class MyroomScene : public cocos2d::CCLayerColor,
public CCScrollViewDelegate
{
    
public:
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(MyroomScene);
    
    void doClose(CCObject* pSender);
    
    virtual void onEnter();
    virtual void onExit();
    
//    CCMenuItemImage *money_star_button;
//    CCMenuItemImage *money_coin_button;
//    CCMenu* moneyMenu;
    
    void scrollViewDidScroll(CCScrollView* view);
    void scrollViewDidZoom(CCScrollView* view);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void popup();
    virtual void schedule();
    virtual void closet();
    virtual void diary();
    virtual void market();
    virtual void stars();
    virtual void coins();

    virtual void popoff();
    

    
    
    CCScrollView *scrollView ;
    
    
    
};

#endif /* defined(__Idolls__MyroomScene__) */

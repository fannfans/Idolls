//
//  ClosetScene.h
//  Idolls
//
//  Created by 효은 김 on 13. 8. 5..
//
//

#ifndef __Idolls__ClosetScene__
#define __Idolls__ClosetScene__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ClosetScene : public cocos2d::CCLayerColor, public CCScrollViewDelegate
{
public:
    
    virtual bool init();
    
    
    static cocos2d::CCScene* scene();
    
    
    CREATE_FUNC(ClosetScene);
    
    virtual void onEnter();
    virtual void onExit();
    
    void scrollViewDidScroll(CCScrollView* view);
    void scrollViewDidZoom(CCScrollView* view);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    CCScrollView *closet_scroll ;
    
    virtual void chargeStar();
    virtual void chargeCoin();
    
    virtual void openMenu();
    
    virtual void myroom();
    virtual void schedule();
    virtual void diary();
    virtual void market();
    
    virtual void reset();
    virtual void wear();
    
    virtual void hair();
    virtual void top();
    virtual void bottom();
    virtual void shoes();
    virtual void etc();
    
    virtual void popup();
    virtual void popoff();
    
    
};
#endif /* defined(__Idolls__ClosetScene__) */

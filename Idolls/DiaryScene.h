//
//  DiaryScene.h
//  Idolls
//
//  Created by 효은 김 on 13. 8. 21..
//
//

#ifndef __Idolls__DiaryScene__
#define __Idolls__DiaryScene__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;


class DiaryScene : public cocos2d::CCLayerColor,
public CCScrollViewDelegate
{
public:
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(DiaryScene);
    
    void doClose(CCObject* pSender);
    
    virtual void onEnter();
    virtual void onExit();
    
    void scrollViewDidScroll(CCScrollView* view);
    void scrollViewDidZoom(CCScrollView* view);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    CCScrollView *scrollView ;
    
};
#endif /* defined(__Idolls__DiaryScene__) */

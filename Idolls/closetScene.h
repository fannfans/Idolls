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

class ClosetScene : public cocos2d::CCLayerColor
{
public:
    
    virtual bool init();
    
    
    static cocos2d::CCScene* scene();
    
    
    CREATE_FUNC(ClosetScene);
    
    virtual void chargeStar();
    virtual void chargeCoin();
    
    virtual void openMenu();
    
    virtual void myroom();
    virtual void schedule();
    virtual void diary();
    virtual void market();
    
    virtual void reset();
    virtual void wear();
    
    virtual void popup();
    virtual void popoff();
    
    
};
#endif /* defined(__Idolls__ClosetScene__) */

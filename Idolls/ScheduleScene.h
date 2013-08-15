//
//  ScheduleScene.h
//  Idolls
//
//  Created by 박성수 on 13. 8. 13..
//
//

#ifndef Idolls_ScheduleScene_h
#define Idolls_ScheduleScene_h

#include "cocos2d.h"
#include "cocos-ext.h"

class ScheduleScene: public cocos2d::CCLayerColor
{
public:
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(ScheduleScene);

    
    virtual void schedule_bg_set();
    virtual void schedule_do_set();
    virtual void schedule_do_layer();
};


#endif

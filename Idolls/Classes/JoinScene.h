//
//  JoinScene.h
//  Idolls
//
//  Created by 효은 김 on 13. 7. 24..
//
//

#ifndef __Idolls__JoinScene__
#define __Idolls__JoinScene__

#include "cocos2d.h"
#include "cocos-ext.h"

class JoinScene : public cocos2d::CCLayerColor,
public cocos2d::extension::CCEditBoxDelegate
{
public:
    
    virtual bool init();
    
    
    static cocos2d::CCScene* scene();
    
    
    CREATE_FUNC(JoinScene);
    
    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
    

    
    cocos2d::extension::CCEditBox* m_pEditId;
    cocos2d::extension::CCEditBox* m_pEditPassword;
    cocos2d::extension::CCEditBox* m_pEditPasswordCheck;
    cocos2d::extension::CCEditBox* m_pEditEmail;
    
};

#endif /* defined(__Idolls__JoinScene__) */

//
//  JoinScene.cpp
//  Idolls
//
//  Created by 효은 김 on 13. 7. 24..
//
//

#include "JoinScene.h"

using namespace cocos2d ;
using namespace cocos2d::extension;

CCScene* JoinScene::scene()
{
    
    CCScene *scene = CCScene::create();
    
    
    JoinScene *layer = JoinScene::create();
    
    
    scene->addChild(layer);
    
    
    return scene;
}

bool JoinScene::init()
{
    
    if ( !CCLayerColor::initWithColor(ccc4(127,65,217,100)) )
    {
        return false;
    }
    
    CCSize editBoxSize = CCSizeMake(274, 50);
    
    m_pEditId = CCEditBox::create(editBoxSize, CCScale9Sprite::create("white_edit.png"));
    
    m_pEditId->setPosition(ccp(160,350));
    m_pEditId->setFontColor(ccGREEN);
    m_pEditId->setPlaceHolder("  ID");
    m_pEditId->setMaxLength(10);
    m_pEditId->setReturnType(kKeyboardReturnTypeDone);
    m_pEditId->setDelegate(this);
    addChild(m_pEditId);

    m_pEditPassword = CCEditBox::create(editBoxSize,CCScale9Sprite::create("white_edit.png"));
    
    m_pEditPassword->setPosition(ccp(160,300));
    m_pEditPassword->setFontColor(ccRED);
    m_pEditPassword->setPlaceHolder("  Password");
    m_pEditPassword->setMaxLength(8);
    m_pEditPassword->setInputFlag(kEditBoxInputFlagPassword);
    m_pEditPassword->setInputMode(kEditBoxInputModeSingleLine);
    m_pEditPassword->setDelegate(this);
    addChild(m_pEditPassword);
    
    m_pEditPasswordCheck = CCEditBox::create(editBoxSize,CCScale9Sprite::create("white_edit.png"));
    
    m_pEditPasswordCheck->setPosition(ccp(160,250));
    m_pEditPasswordCheck->setFontColor(ccRED);
    m_pEditPasswordCheck->setPlaceHolder("  PasswordCheck");
    m_pEditPasswordCheck->setMaxLength(8);
    m_pEditPasswordCheck->setInputFlag(kEditBoxInputFlagPassword);
    m_pEditPasswordCheck->setInputMode(kEditBoxInputModeSingleLine);
    m_pEditPasswordCheck->setDelegate(this);
    addChild(m_pEditPasswordCheck);

    m_pEditEmail = CCEditBox::create(editBoxSize,CCScale9Sprite::create("white_edit.png"));
    
    m_pEditEmail->setPosition(ccp(160,200));
    m_pEditEmail->setFontColor(ccBLACK);
    m_pEditEmail->setPlaceHolder("  khe0622@naver.com");
    m_pEditEmail->setMaxLength(20);
    m_pEditEmail->setReturnType(kKeyboardReturnTypeDone);
    m_pEditEmail->setDelegate(this);
    addChild(m_pEditEmail);

    return true ;

}
void JoinScene::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox){
    
    CCLog("Hi");
    
    
}
void JoinScene::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox){
    CCLog("Hi");
    
    
}
void JoinScene::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text){
    
    CCLog("Hi");
    
}
void JoinScene::editBoxReturn(CCEditBox* editBox){
    CCLog("Hi");
    
    
}
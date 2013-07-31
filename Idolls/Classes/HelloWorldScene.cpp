#include "HelloWorldScene.h"
#include "MyroomScene.h"
#include "JoinScene.h"

using namespace cocos2d;
using namespace cocos2d::extension;


CCScene* HelloWorld::scene()
{

    CCScene *scene = CCScene::create();
    

    HelloWorld *layer = HelloWorld::create();


    scene->addChild(layer);


    return scene;
}


bool HelloWorld::init()
{
    
    if ( !CCLayerColor::initWithColor(ccc4(127,65,217,100)) )
    {
        return false;
    }
    
    CCSize editBoxSize = CCSizeMake(274, 50);
    
    m_pEditId = CCEditBox::create(editBoxSize, CCScale9Sprite::create("white_edit.png"));
    
    m_pEditId->setPosition(ccp(160,300));
    m_pEditId->setFontColor(ccGREEN);
    m_pEditId->setPlaceHolder("  ID");
    m_pEditId->setMaxLength(10);
    m_pEditId->setReturnType(kKeyboardReturnTypeDone);
    m_pEditId->setDelegate(this);
    addChild(m_pEditId);

    m_pEditPassword = CCEditBox::create(editBoxSize,CCScale9Sprite::create("white_edit.png"));

    m_pEditPassword->setPosition(ccp(160,250));
    m_pEditPassword->setFontColor(ccRED);
    m_pEditPassword->setPlaceHolder("  Password");
    m_pEditPassword->setMaxLength(8);
    m_pEditPassword->setInputFlag(kEditBoxInputFlagPassword);
    m_pEditPassword->setInputMode(kEditBoxInputModeSingleLine);
    m_pEditPassword->setDelegate(this);
    addChild(m_pEditPassword);
    
    
    CCMenuItemImage *pMenuLogin = CCMenuItemImage::create("login_button.png", "login_button.png", this, menu_selector(HelloWorld::login));
    
    CCMenuItemImage *pMenuJoin = CCMenuItemImage::create("join_button.png", "join_button.png", this, menu_selector(HelloWorld::join));
    
    
    CCMenu* pMenu = CCMenu::create(pMenuLogin, pMenuJoin, NULL);
    pMenu->alignItemsVertically();
    pMenu->setPosition(ccp(160,150));
    this->addChild(pMenu);
    
    return true;
}

void HelloWorld::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox){
    
    CCLog("Hi");
    
    
}
void HelloWorld::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox){
        CCLog("Hi");
    
    
}
void HelloWorld::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text){
    
        CCLog("Hi");
    
}
void HelloWorld::editBoxReturn(CCEditBox* editBox){
        CCLog("Hi");
    
    
}

void HelloWorld::login(){
    
    CCScene* pScene = MyroomScene::scene();
    CCDirector::sharedDirector()->pushScene(pScene);

}

void HelloWorld::join(){
    
    CCScene* pScene = JoinScene::scene();
    CCDirector::sharedDirector()->pushScene(pScene);
}
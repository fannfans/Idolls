//
//  DiaryScene.cpp
//  Idolls
//
//  Created by 효은 김 on 13. 8. 21..
//
//

#include "DiaryScene.h"
#include "global.h"
#include "SimpleAudioEngine.h"
#include "DiaryCell.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCTableView* tableView;
int touchedCellIdx;// 터치된 셀 인덱스
bool touchflag = false; //셀이 터치 됐는지
bool scrollflag = false; //셀이 스크롤 됐는지

int countflag =0 ;

CCString* string; // 글 번호
enum{
    
    tagTableView = 10,
};

DiaryScene::~DiaryScene(){
    
    if(datalist) {
        datalist->release();
        datalist = NULL;
    }
}

CCScene* DiaryScene::scene()
{
    
    CCScene *scene = CCScene::create();
    DiaryScene *layer = DiaryScene::create();
    scene->addChild(layer);
    return scene;
}

bool DiaryScene::init()
{
    
    if ( !CCLayerColor::initWithColor(ccc4(0,0,0,255)) )
    {
        return false;
    }
    
    // 디바이스 사이즈
    winSize = CCDirector::sharedDirector()->getWinSize();
    
    //배경
    CCSprite *diary_background = CCSprite::create("diary_background.png");
    diary_background->setScale(winSize.width/3200*2.5);
    diary_background->setPosition(ccp(winSize.width/2,winSize.height/2));
    
    //다이어리 배경레이어
    CCLayer *diary_bglayer= CCLayer::create();
    diary_bglayer->setAnchorPoint(CCPointZero);
    diary_bglayer->setPosition(ccp(0,0));
    diary_bglayer->setContentSize(CCSizeMake(winSize.width,winSize.height));

    this->addChild(diary_bglayer);
    diary_bglayer->addChild(diary_background);
    
    // 상단 메뉴 버튼
    CCMenuItemImage* back_button = CCMenuItemImage::create("back_button_off.png","back_button_on.png",this, menu_selector(DiaryScene::goBack));
    
    CCMenuItemImage* message_button = CCMenuItemImage::create("message_button_off.png","message_button_on.png",this, menu_selector(DiaryScene::message));
    
    CCMenuItemImage* freinds_button = CCMenuItemImage::create("friends_button_off.png","friends_button_on.png",this, menu_selector(DiaryScene::freinds));
    
    CCMenuItemImage* community_button = CCMenuItemImage::create("community_button_off.png","community_button_on.png",this, menu_selector(DiaryScene::community));
    
    CCMenu* diaryMenu = CCMenu::create(back_button, message_button, freinds_button, community_button, NULL);
    
    diaryMenu->alignItemsHorizontallyWithPadding(10.0f);
    diaryMenu->setScale(winSize.width/3200*2.5);
    diaryMenu->setPosition(ccp(winSize.width/10*1.3,winSize.height/10*5.8));
    diary_bglayer->addChild(diaryMenu);
    
    //    캐릭터
    maincharacter = CCSprite::create("character1.png");
    maincharacter->setScale(0.09);
    maincharacter->setPosition(ccp(45,360));
    diary_bglayer->addChild(maincharacter,150);
    
    
    /* 테이블 뷰 (다이어리 글) */
    
    // 글쓰기 버튼
    CCLabelTTF* label = CCLabelTTF::create("글쓰기", "Helvetica", 20);
    CCMenuItem* addData = CCMenuItemLabel::create(label, this, menu_selector(DiaryScene::addDataFive));
    addData->setAnchorPoint(CCPointZero);
    addData->setPosition(ccp(260,230));
    
    CCMenu* pMenu = CCMenu::create(addData, NULL);
    pMenu->setPosition( CCPointZero );
    diary_bglayer->addChild(pMenu, 1);
    
    //data가 저장될 공간 생성
    datalist = CCArray::create();
    datalist->retain();
    
    //데이터 추가
    count = 0;
    for(int i=0; i < 20; i++){
        addDatalist(count);
        count++;
    }
    
    //테이블 뷰 생성
    tableView = CCTableView::create(this, CCSizeMake(311, 230));
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    tableView->setPosition(ccp(0, 0));
    
    //데이터를 가져오고나 터치 이벤트를 반환해줄 대리자를 이 클래스로 설정.
    tableView->setDelegate(this);
    diary_bglayer->addChild(tableView, 1, tagTableView);
    tableView->reloadData();
    
    return true;
}

/**
 datalist에 데이터를 추가한다.
 @param int num : 추가할 데이터 번호
 @returns void
 @exception not
 */
void DiaryScene::addDatalist(int num)
{
    char str[8] ;
    sprintf(str, "data %d", num);
    datalist->addObject(CCString::create(str));
}

//메뉴 콜백 함수
void DiaryScene::addDataFive()
{
    CCLog("글쓰기 , 데이터 추가");
    CCTableView* tb = (CCTableView*) this->getChildByTag(tagTableView);
    addDatalist(count);
    count++;

    //테이블 뷰의 크기를 다시 정의 한다. 원하는 퍼퍼먼스는 얻기 힘들었다;
    tb->_updateContentSize();
}

void DiaryScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//셀을 터치하면 콜백 된다. 어떤 셀이 터치 되었는지 알 수 있다. 이 함수 외에도 하일라이트 부분 콜백이나, 다시 셀이 재사용될 때 콜백도 있다.
void DiaryScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCPoint offset = table->getContentOffset();
    touchedCellIdx = cell->getIdx();
    CCLOG("cell touched at index: %i", touchedCellIdx);    
    touchflag=true;
    
    CCLOG("%d",countflag);
        countflag++;
    cell->removeAllChildrenWithCleanup(true);
    cell->removeFromParentAndCleanup(true);
    tableView->addChild(cell);
    // 셀 크기 변경
    CCLayerColor* mask = CCLayerColor::create(ccc4(255, 50, 50, 255), 311, 120);
    mask->setPosition(ccp(0,0));
    cell->addChild(mask,100,true);


    char temp[15] ;
    sprintf(temp, "data %d", touchedCellIdx);
    strcat(temp, "커짐");


    // 셀에 들어가는 글씨
    CCLabelTTF *label = CCLabelTTF::create(temp, "Helvetica", 20.0);
    label->setPosition(ccp(20,40));
    label->setAnchorPoint(CCPointZero);
    label->setColor(ccc3(0, 0, 0));
    label->setTag(123);
    cell->addChild(label,200);
    table->_updateContentSize();
    table->updateCellAtIndex(touchedCellIdx);

    
}

void DiaryScene::tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("하일라이트");

}

void DiaryScene::tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("언 하일라이트");
    
}

//CCTableViewDataSource
//cell(카톡게임에서 친구한명의 정보를 나타내는 영력)의 크기를 정의한다.
CCSize DiaryScene::cellSizeForTable(CCTableView *table)
{
   if(touchflag){
        CCLOG("oooooooooo");
        touchflag=false;
        return CCSizeMake(311, 120);

    }
    else{
        scrollflag=false;
        return CCSizeMake(311, 72);

    }
    

}

//reload가 호출 되거나, 스크롤이 움직여 안보이는 셀이 보여질 때 호출된다.
CCTableViewCell* DiaryScene::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    scrollflag =true;
    //테이블이 사용 중인 셀이 있다면 재활용한다. 테이블 뷰는 똑같은 모양에 데이터만 다른 경우가 많다. 그래서 하나의 셀을 재사용하고 데이터만 바꿔준다.
    CCTableViewCell *cell = table->dequeueCell();
    
    //datalist에서 데이터를 가져온다. 여기서는 CCString을 했지만, CCObject를 상속받은 커스텀 클래스를 만들어서 여러 정보를 담을 수 있을 것이다.
    string = (CCString*) datalist->objectAtIndex(idx);
    if (!cell) {
        //커스텀 셀을 이용했는데, 이는 커스텀 셀 부분의 draw 함수를 오버로딩하여 여러가지 효과를 줄 수 있기 때문이다. 이 예제에서는 아무런 추가 내용이 없지만, 이부분을 이용하여 3D리스트 뷰나, 크기가 바뀌는 리스트 뷰 같은 조금 더 다이나믹한 리스트뷰를 만들 수 있을 것 같다.
        CCLOG("2222222");
        cell = new DiaryCell();
        cell->autorelease();
        CCSprite* cell_background = CCSprite::create("cell_small_box.png");
        cell_background->setScale(0.25);

        CCLayer* mask = CCLayer::create();

        mask->addChild(cell_background);
        mask->setPosition(ccp(158,0));
        cell->addChild(mask,100, 44);
        
        // 셀에 들어가는 글씨
        CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0);
        label->setPosition(ccp(10,0));
        label->setAnchorPoint(CCPointZero);
        label->setColor(ccc3(0, 0, 0));
        label->setTag(123);
        cell->addChild(label,200);
    }
    else
    {
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
        label->setString(string->getCString());
    }
    
    return cell;}

//테이블이 셀 갯수에 대한 정보를 가져가는 곳이다.
unsigned int DiaryScene::numberOfCellsInTableView(CCTableView *table)
{
    return datalist->count();
}

void DiaryScene::goBack(){
    
    
}
void DiaryScene::message(){
    
}

void DiaryScene::freinds(){
    
}

void DiaryScene::community(){
    
}
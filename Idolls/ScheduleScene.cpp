//
//  ScheduleScene.cpp
//  Idolls
//
//  Created by 박성수 on 13. 8. 13..
//  Last Modified : 13. 08. 19..
//

#include "ScheduleScene.h"
#include "global.h"

using namespace std;
using namespace cocos2d;

CCSprite *scheduleBg;
CCLayerColor *s_layer;


/*  │ ┠ └ ─
    Schedulebglayer
        ┠─ scheduleBg (sprite 스케쥴씬 기본배경)
        ┠──── S_layer( 스케쥴 리스트 레이어)
        └──── Schedulepopuplayer(스케쥴 수행하기 팝업 레이어)
 */



CCScene* ScheduleScene::scene()
{
    CCScene *scene = CCScene::create();
    
    ScheduleScene *layer = ScheduleScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool ScheduleScene::init()
{
    if(!CCLayerColor::initWithColor(ccc4(255,255,255,255)))
    {
        return false;
    }
    /*
     * 스케쥴 배경화면
     * Schedule Background
     */
    schedule_bg_set();
    
    //    cout<<"@@@@@@@@@@@@@"<<schedule1_str<<endl;
    
    // 코인, 스타메뉴 추가 ( Coins, Star Menu Add)  / Z-order is 50
    Schedulebglayer->addChild(moneyMenu,50);
  
    // 스케쥴 팝업화면 ( Schedule Popup Layer )
    schedule_do_set();
    schedule_list();
    this->addChild(Schedulebglayer);

    return true;
}


// 스케쥴 메인 배경화면 세팅
void ScheduleScene::schedule_bg_set(){
    scheduleBg = CCSprite::create("schedule_background.png");
    scheduleBg->setScale(winSize.width/3200*2.5);
    scheduleBg->setPosition(ccp(winSize.width/2, winSize.height/2));
    
    Schedulebglayer = CCLayerColor::create(ccc4(255,0,255,255));
    Schedulebglayer->setPosition(ccp(0,0));
    Schedulebglayer->setContentSize(CCSizeMake(winSize.width,winSize.height));
    
    Schedulebglayer->addChild(scheduleBg);    
}


//스케쥴 리스트 세팅    
void ScheduleScene::schedule_list(){
    /*
     * 임시로 스케쥴 구현해놓은 상태.
     * 실제 구현시 서버에서 받아와서 저장하면 될듯. 
     */
    CCMenuItemImage *schedule_state0, *schedule_state1, *schedule_state2, *schedule_state3, *schedule_state4;
    string schedule0_str0, schedule1_str0, schedule2_str0, schedule3_str0, schedule4_str0;
    string schedule0_str1, schedule1_str1, schedule2_str1, schedule3_str1, schedule4_str1;
    CCMenu *sMenu0, *sMenu1, *sMenu2, *sMenu3, *sMenu4;
    string s_state0, s_state1, s_state2, s_state3, s_state4;
    string s_list [5][8];
    string start_ampm = "am";
    string end_ampm ="pm";
    s_state0 = "2"; // 스케쥴 수행상태. 1 = 아직 스케쥴 수행 안한상태 , 2 = 스케쥴 수행완료, 3 = 스케쥴 펑크
    s_list[0][0] = "1";  // 스케쥴 번호
    s_list[0][1] = start_ampm; //시작 시간(오전/오후)
    s_list[0][2] = "9"; //start time
    s_list[0][3] = "~"; // 물결
    s_list[0][4] = end_ampm; // 종료 시간(오전/오후)
    s_list[0][5] = "12"; //end time
    s_list[0][6] = "음악방송 사전녹화";
    s_list[0][7] = s_state0; //스케쥴 상태
    
    s_state1 = "1";
    s_list[1][0] = "2";
    s_list[1][1] = start_ampm;
    s_list[1][2] = "12";
    s_list[1][3] = "~";
    s_list[1][4] = end_ampm;
    s_list[1][5] = "15";
    s_list[1][6] = "KBS라디오 생방송";
    s_list[1][7] = s_state1;
    
    /*
     * 2중 배열에서 행은 각 스케쥴에대한 번호,
     * 열은 스케쥴에서 구성되는 각 스트링과 데이터에대한 번호임
     * 현재 방식은 이중배열이지만 더 좋은게 있다면 대체가 필요해보임..
     */

    
    schedule0_str0 = start_ampm + " " + s_list[0][2] + " " + s_list[0][3] + " " + s_list[0][4] + s_list[0][5];
    schedule0_str1 = s_list[0][6];
    schedule1_str0 = start_ampm + " " + s_list[1][2] + " " + s_list[1][3] + " " + s_list[1][4] + s_list[1][5];
    schedule1_str1 = s_list[1][6];
    
//    for(int i=1; i<6; i++){
//        schedule1_str0 += s_list[1][i];
//        schedule2_str0 += s_list[2][i];
//        schedule3_str0 += s_list[3][i];
//        schedule4_str0 += s_list[4][i];
//    }
//    schedule1_str1 = s_list[1][6];
//    schedule2_str1 = s_list[1][6];
//    schedule3_str1 = s_list[1][6];
//    schedule4_str1 = s_list[1][6];
    
    //  schedule-0 은 스케쥴 시간
    //  schedule-1 은 스케쥴 내용
    CCLabelTTF* schedule00 = CCLabelTTF::create(schedule0_str0.c_str(),"Thonburi", 16);
    CCLabelTTF* schedule01 = CCLabelTTF::create(schedule0_str1.c_str(),"Thonburi", 16);
    CCLabelTTF* schedule10 = CCLabelTTF::create(schedule1_str0.c_str(),"Thonburi", 16);
    CCLabelTTF* schedule11 = CCLabelTTF::create(schedule1_str1.c_str(),"Thonburi", 16);
    
    s_layer = CCLayerColor::create(ccc4(0,0,0,0)); //스케쥴 텍스트 부분에해당하는 레이어
    s_layer->addChild(schedule00);
    s_layer->addChild(schedule01);
    s_layer->addChild(schedule10);
    s_layer->addChild(schedule11);
    schedule00->setColor(ccc3(0,0,0));
    schedule01->setColor(ccc3(0,0,0));
    schedule10->setColor(ccc3(0,0,0));
    schedule11->setColor(ccc3(0,0,0));
    schedule00->setPosition(ccp(winSize.width/4, winSize.height/1.55));
    schedule01->setPosition(ccp(winSize.width/3.5, winSize.height/1.7));
    schedule10->setPosition(ccp(winSize.width/4, winSize.height/1.87));
    schedule11->setPosition(ccp(winSize.width/3.5, winSize.height/2.1));
    
    
    // 1번스케쥴부분
    // 1 : 수행하기 2 : 수행완료 3 : 방송펑크
    if(s_state0.compare("1") == 0){
        schedule_state0 = CCMenuItemImage::create("schedule_do_button_off.png","schedule_do_button_on.png",this,menu_selector(ScheduleScene::schedule_do_layer));
        schedule_state0->setScale(winSize.width/3200*2);
        schedule_state0->setPosition(ccp(winSize.width/1.15, winSize.height/1.6));
    }
    else if(s_state0.compare("2") == 0){
        schedule_state0 = CCMenuItemImage::create("schedule_done.png","schedule_done.png",this,NULL);
        schedule_state0->setScale(winSize.width/3200*2.6);
        schedule_state0->setPosition(ccp(winSize.width/1.15, winSize.height/1.6));
    }
    else{
        schedule_state0 = CCMenuItemImage::create("schedule_fail.png","schedule_fail.png",this,NULL);
        schedule_state0->setPosition(ccp(winSize.width/1.15, winSize.height/1.6));
    }
    
    
    // 2번 스케쥴 부분
    
    if(s_state1.compare("1") == 0){
        schedule_state1 = CCMenuItemImage::create("schedule_do_button_off.png","schedule_do_button_on.png",this,menu_selector(ScheduleScene::schedule_do_layer));
        schedule_state1->setScale(winSize.width/3200*2);
        schedule_state1->setPosition(ccp(winSize.width/1.15, winSize.height/1.97));
    }
    else if(s_state1.compare("2") == 0){
        schedule_state1 = CCMenuItemImage::create("schedule_done.png","schedule_done.png",this,NULL);
        schedule_state1->setScale(winSize.width/3200*2.6);
        schedule_state1->setPosition(ccp(winSize.width/1.15, winSize.height/1.97));
    }
    else{
        schedule_state1 = CCMenuItemImage::create("schedule_fail.png","schedule_fail.png",this,NULL);
        schedule_state1->setPosition(ccp(winSize.width/1.15, winSize.height/1.97));
    }
    
    sMenu0 = CCMenu::create(schedule_state0,NULL);
    sMenu0->alignItemsHorizontally();
    sMenu0->setPosition(ccp(winSize.width/1.15, winSize.height/1.6));
    
    sMenu1 = CCMenu::create(schedule_state1, NULL);
    sMenu1->alignItemsHorizontally();
    sMenu1->setPosition(ccp(winSize.width/1.15, winSize.height/1.97));
    
//    sMenu1 = CCMenu::create(schedule_state1, NULL);

//    
//    s_layer->addChild(schedule_state0);
    s_layer->addChild(sMenu0);
    s_layer->addChild(sMenu1);
    
  
    
        
    
    Schedulebglayer->addChild(s_layer);
}


// 수행하기 레이어 세팅
void ScheduleScene::schedule_do_set(){
    //팝업레이어
    SchedulePopupLayer = CCLayerColor::create(ccc4(0,0,0,0));
    //화면 2^4로 나눈 위치에 위치시킴
    CCLOG("POPUP Layer Position : ( %f, %f )", winSize.width/16, winSize.height/16);
       
    SchedulePopupLayer->setContentSize(CCSizeMake(winSize.width,winSize.height));
    SchedulePopupLayer->setPosition(ccp(0,0));
//    SchedulePopupLayer->setOpacity(180);
    
    //팝업 배경레이어
    CCSprite *schedule_popup_bg = CCSprite::create("schedule_popup_quiz_bg.png");
    schedule_popup_bg->setScale(winSize.width/3200*2.6);
    schedule_popup_bg->setPosition(ccp(winSize.width/2,(winSize.height)/2));
    SchedulePopupLayer->addChild(schedule_popup_bg);
    
    //퀴즈영역
    string quiz_str = "Quiz.";
    string quiz_str2 = "130814 주간아이돌에서 EXO 루한이 춘 걸그룹댄스의 그룹명은?";
    CCLabelTTF* quiz_label = CCLabelTTF::create(quiz_str.c_str(),"Thonburi", 24);
    CCLabelTTF* quiz_label2 = CCLabelTTF::create(quiz_str2.c_str(),"Thonburi",16,CCSize(winSize.width/2,winSize.height/3),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
    quiz_label->setPosition(ccp(winSize.width/3.8, winSize.height/1.6));
    quiz_label2->setPosition(ccp(winSize.width/1.75, winSize.height/1.73));
    
    quiz_label->setColor(ccc3(0,0,0));
    quiz_label2->setColor(ccc3(0,0,0));
    
    SchedulePopupLayer->addChild(quiz_label);
    SchedulePopupLayer->addChild(quiz_label2);
    
        
    //제출버튼
    CCMenuItemImage* submit_btn = CCMenuItemImage::create("schedule_submit_button_off.png","schedule_submit_button_on.png",this, menu_selector(ScheduleScene::schedule_submit));
    submit_btn->setScale(winSize.width/3200*2.6);
    CCMenu *submit_menu = CCMenu::create(submit_btn,NULL);
    submit_menu->alignItemsHorizontally();

    submit_menu->setPosition(winSize.width/2, winSize.height/3.7);
    
    SchedulePopupLayer->addChild(submit_menu);
    Schedulebglayer->addChild(SchedulePopupLayer);
    SchedulePopupLayer->setVisible(false); // 스케쥴 씬 처음 로드시엔 보이지 않도록 설정.
    

}

void ScheduleScene::schedule_submit(){
    //수행 후 제출하기 레이어
    ScheduleSubmitLayer = CCLayerColor::create(ccc4(0,0,0,0));
    ScheduleSubmitLayer->setContentSize(CCSizeMake(winSize.width,winSize.height));
    ScheduleSubmitLayer->setPosition(ccp(0,0));
    
    
    //제출하기 배경레이어
    CCSprite *submit_bg = CCSprite::create("schedule_popup_result_bg.png");
    submit_bg->setScale(winSize.width/3200*2.6);
    submit_bg->setPosition(ccp(winSize.width/2,winSize.height/2));
    ScheduleSubmitLayer->addChild(submit_bg);
//    submit_bg->setOpacity(0);

    //확인버튼
    CCMenuItemImage* ok_btn = CCMenuItemImage::create("schedule_ok_button_off.png","schedule_ok_button_on.png",this, menu_selector(ScheduleScene::schedule_submit_ok));
    
    ok_btn->setScale(winSize.width/3200*2.6);
    CCMenu *ok_menu = CCMenu::create(ok_btn,NULL);
    ok_menu->alignItemsHorizontally();
    ok_menu->setPosition(winSize.width/2, winSize.height/3.7);
    
    ScheduleSubmitLayer->addChild(ok_menu);
    Schedulebglayer->addChild(ScheduleSubmitLayer,2);
        
}

// 수행하기 레이어
void ScheduleScene::schedule_do_layer(){
    //    scheduleMenu->setVisible(false); // 수행하기버튼
    s_layer->setVisible(false);
    SchedulePopupLayer->setVisible(true);
    
}

void ScheduleScene::schedule_submit_ok(){
    Schedulebglayer->removeChild(ScheduleSubmitLayer,true);
}
void ScheduleScene::schedule_done_layer(){
    
}
void ScheduleScene::schedule_fail_layer(){
    
}


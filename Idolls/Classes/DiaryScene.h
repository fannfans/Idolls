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


class DiaryScene : public cocos2d::CCLayerColor,public CCTableViewDataSource,
public CCTableViewDelegate
{
    
private:
    CCArray* datalist;
    void addDataFive();
    void addDatalist(int num);
    int count;
    
public:
    ~DiaryScene();
    virtual bool init();
    static cocos2d::CCScene* scene();
    
    void menuCloseCallback(CCObject* pSender);
    CREATE_FUNC(DiaryScene);
    
    //tableview
    virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell);
    virtual void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell);
    virtual void scrollViewDidScroll(CCScrollView* view) {};
    virtual void scrollViewDidZoom(CCScrollView* view) {}
    
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    
    virtual void goBack();
    virtual void message();
    virtual void freinds();
    virtual void community();
    
    
};
#endif /* defined(__Idolls__DiaryScene__) */

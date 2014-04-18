#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Hero.h"
#include "enemy.h"
USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;

class FightScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(FightScene);

	void tbPlatePushDownCallback(CCObject *psender,TouchEventType type);
	void tbAtkCallback(CCObject *pSender,TouchEventType type);
	Hero* hero;
	Enemy* enemy;

	CC_SYNTHESIZE(CCPoint,_direction,KeyDir);
	CC_SYNTHESIZE(CCRect,_movearea,Movearea);
	void update(float delta);
	void enemyUpdate();
	void HeroUpdate();
	CCPoint getDir(UIButton* pbut,TouchEventType type);
	float getDis(UIButton* pbut,TouchEventType type);
};

#endif // __HELLOWORLD_SCENE_H__

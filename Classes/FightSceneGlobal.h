#ifndef __FIGHTSCENE_H
#define __FIGHTSCENE_H
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;
#include "Singleton.h"

class FightSceneGlobal:public Singleton<FightSceneGlobal>
{
	CC_SYNTHESIZE_READONLY(CCNode*,_fightScene,FightScene);
	CC_SYNTHESIZE_READONLY(CCArmature*,_heroArmature,HeroArmature);
	CC_SYNTHESIZE_READONLY(CCArmature*,_enemyArmature,EnemyArmature);
	CC_SYNTHESIZE_READONLY(UIButton*,_ubPlate,UbPlate);
	CC_SYNTHESIZE_READONLY(UIButton*,_ubAtk,UbAtk);
	CC_SYNTHESIZE_READONLY(ImageView*,_ball,Ball);
	CC_SYNTHESIZE_READONLY(Layout*,_uiLayer,UiLayer);
public:
	FightSceneGlobal();
	~FightSceneGlobal(void);

};

#define g_FightScene FightSceneGlobal::instance()

#endif
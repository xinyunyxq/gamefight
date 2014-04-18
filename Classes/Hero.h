#ifndef __HERO_H
#define __HERO_H
#include "cocos2d.h"
#include "cocos-ext.h"
#include "FightSceneGlobal.h"
#include "GameConstants.h"
USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;


class Hero
{
	CC_SYNTHESIZE(HeroState,_heroState,heroState);
	CC_SYNTHESIZE(int,_heroSpeed,heroSpeed);
	CC_SYNTHESIZE(bool,_isleft,isleft);
	CC_SYNTHESIZE(int,_hpValue,HpValue);
	CC_SYNTHESIZE(int,_hpValueMax,HpValueMax);
	CC_SYNTHESIZE(int,_atkValue,AtkValue);
	CC_SYNTHESIZE_READONLY(LoadingBar*,_hpBar,HpBar);
	CC_SYNTHESIZE_READONLY(LoadingBar*,_mpBar,mpBar);
public:
	Hero();
	~Hero(void);
	void PlayState(HeroState state);
	CCRect getHeroArea(CCPoint heroPosition);
};
#endif
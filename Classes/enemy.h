#ifndef __ENEMY_H
#define __ENEMY_H
#include "cocos2d.h"
#include "cocos-ext.h"
#include "FightSceneGlobal.h"
#include "GameConstants.h"
USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;


class Enemy
{
	CC_SYNTHESIZE(EnemyState,_enemyState,enemyState);
	CC_SYNTHESIZE(int,_enemySpeed,enemySpeed);
	CC_SYNTHESIZE(bool,_isleft,isleft);
	CC_SYNTHESIZE(int,_hpValue,HpValue);
	CC_SYNTHESIZE(int,_hpValueMax,HpValueMax);
	CC_SYNTHESIZE(int,_atkValue,AtkValue);
	CC_SYNTHESIZE_READONLY(LoadingBar*,_hpBar,HpBar);
	CC_SYNTHESIZE_READONLY(LoadingBar*,_mpBar,mpBar);
	CCDrawNode* front;
public:
	Enemy();
	~Enemy(void);
	void PlayState(EnemyState state);
	CCRect getEnemyArea(CCPoint enemyPosition);
	bool inAtkRange();

private:

};
#endif
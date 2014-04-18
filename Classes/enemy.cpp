#include "enemy.h"

//DECLARE_SINGLETON_MEMBER(Enemy);

Enemy::Enemy()
{
	FightSceneGlobal::instance()->getEnemyArmature()->getAnimation()->play("loading");
	this->setenemyState(enemyLoading);
	this->setenemySpeed(3);
	this->setisleft(false);
	this->setHpValue(100);
	this->setHpValueMax(100);
	this->setAtkValue(20);
	_hpBar = dynamic_cast<ui::LoadingBar*>(ui::UIHelper::seekWidgetByName(FightSceneGlobal::instance()->getUiLayer(),"hp02_LoadingBar"));
	_mpBar = dynamic_cast<ui::LoadingBar*>(ui::UIHelper::seekWidgetByName(FightSceneGlobal::instance()->getUiLayer(),"mp02_LoadingBar"));
}

Enemy::~Enemy(void)
{

}

void Enemy::PlayState(EnemyState state)
{
	switch (state)
	{
	case enemyLoading:
		if (this->getenemyState() != enemyLoading)
		{
			FightSceneGlobal::instance()->getEnemyArmature()->getAnimation()->play("loading");
			this->setenemyState(enemyLoading);
		}
		break;
	case enemyRun:
		if (this->getenemyState() != enemyRun)
		{
			FightSceneGlobal::instance()->getEnemyArmature()->getAnimation()->play("run");
			this->setenemyState(enemyRun);
		}
		break;
	case enemyAtk:
		if (this->getenemyState() != enemyAtk)
		{
			FightSceneGlobal::instance()->getEnemyArmature()->getAnimation()->play("attack");
			this->setenemyState(enemyAtk);
		}
		break;
	case enemySmitten:
		if (this->getenemyState() != enemySmitten)
		{
			FightSceneGlobal::instance()->getEnemyArmature()->getAnimation()->play("smitten");
			this->setenemyState(enemySmitten);
		}
		break;
	}



}

CCRect Enemy::getEnemyArea(CCPoint enemyPosition)
{
	return CCRectMake(enemyPosition.x - 25,enemyPosition.y - 10,50,20);
}
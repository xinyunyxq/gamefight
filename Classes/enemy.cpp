#include "enemy.h"

//DECLARE_SINGLETON_MEMBER(Enemy);

Enemy::Enemy()
{
	this->setenemySpeed(3);
	this->setisleft(false);
	this->setHpValue(100);
	this->setHpValueMax(100);
	this->setAtkValue(20);
	_hpBar = dynamic_cast<ui::LoadingBar*>(ui::UIHelper::seekWidgetByName(FightSceneGlobal::instance()->getUiLayer(),"hp02_LoadingBar"));
	_mpBar = dynamic_cast<ui::LoadingBar*>(ui::UIHelper::seekWidgetByName(FightSceneGlobal::instance()->getUiLayer(),"mp02_LoadingBar"));
	
	front=CCDrawNode::create();
	CCPoint rect[4]={ccp(-25,10),ccp(25,10),ccp(25,-10),ccp(-25,-10)};
	ccColor4F yellow = {1, 1, 0, 1};
	front->drawPolygon(rect, 4, yellow, 0, yellow);
	front->setPosition(FightSceneGlobal::instance()->getEnemyArmature()->getParent()->getPosition());
	FightSceneGlobal::instance()->getFightScene()->addChild(front,10);
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
	case enemyDeath:
		if (this->getenemyState() != enemyDeath)
		{
			FightSceneGlobal::instance()->getEnemyArmature()->getAnimation()->play("death");
			this->setenemyState(enemyDeath);
		}
		break;
	}



}

CCRect Enemy::getEnemyArea(CCPoint enemyPosition)
{	
	front->setPosition(enemyPosition);
	return CCRectMake(enemyPosition.x - 25,enemyPosition.y - 10,50,20);
}

bool Enemy::inAtkRange()
{
	CCPoint heroPosition = FightSceneGlobal::instance()->getHeroArmature()->getParent()->getPosition();
	CCPoint enemyPosition = FightSceneGlobal::instance()->getEnemyArmature()->getParent()->getPosition();
	CCPoint position = enemyPosition - heroPosition;
	if(position.x <= 150 && position.x >= -150 && position.y <= 15 && position.y >= -15)
	{
		return true;
	}
	else
	{
		return false;
	}

}

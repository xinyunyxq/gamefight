#include "Hero.h"

//DECLARE_SINGLETON_MEMBER(Hero);
Hero::Hero()
{
	FightSceneGlobal::instance()->getHeroArmature()->getAnimation()->play("loading");
	this->setheroState(heroLoading);
	this->setheroSpeed(3);
	this->setisleft(false);
	this->setHpValue(100);
	this->setHpValueMax(100);
	this->setAtkValue(20);
	_hpBar = dynamic_cast<ui::LoadingBar*>(ui::UIHelper::seekWidgetByName(FightSceneGlobal::instance()->getUiLayer(),"hp01_LoadingBar"));
	_mpBar = dynamic_cast<ui::LoadingBar*>(ui::UIHelper::seekWidgetByName(FightSceneGlobal::instance()->getUiLayer(),"mp01_LoadingBar"));

	front=CCDrawNode::create();
	CCPoint rect[4]={ccp(-25,10),ccp(25,10),ccp(25,-10),ccp(-25,-10)};
	ccColor4F yellow = {1, 1, 0, 1};
	front->drawPolygon(rect, 4, yellow, 0, yellow);
	front->setPosition(FightSceneGlobal::instance()->getHeroArmature()->getParent()->getPosition());
	FightSceneGlobal::instance()->getFightScene()->addChild(front,10);
}

Hero::~Hero(void)
{

}

void Hero::PlayState(HeroState state)
{
	switch (state)
	{
	case heroLoading:
		if (this->getheroState() != heroLoading)
		{
			FightSceneGlobal::instance()->getHeroArmature()->getAnimation()->play("loading");
			this->setheroState(heroLoading);
		}
		break;
	case heroRun:
		if (this->getheroState() != heroRun)
		{
			FightSceneGlobal::instance()->getHeroArmature()->getAnimation()->play("run");
			this->setheroState(heroRun);
		}
		break;
	case heroAtk:
		if (this->getheroState() != heroAtk)
		{
			FightSceneGlobal::instance()->getHeroArmature()->getAnimation()->play("attack");
			this->setheroState(heroAtk);
		}
		break;
	case heroSmitten:
		if (this->getheroState() != heroSmitten)
		{
			FightSceneGlobal::instance()->getHeroArmature()->getAnimation()->play("smitten");
			this->setheroState(heroSmitten);
		}
		break;
	case heroDeath:
		if (this->getheroState() != heroDeath)
		{
			FightSceneGlobal::instance()->getHeroArmature()->getAnimation()->play("death");
			this->setheroState(heroDeath);
		}
		break;
	}



}

CCRect Hero::getHeroArea(CCPoint heroPosition)
{
	front->setPosition(heroPosition);
	return CCRectMake(heroPosition.x - 25,heroPosition.y - 10,50,20);
}


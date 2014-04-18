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
	}



}

CCRect Hero::getHeroArea(CCPoint heroPosition)
{
	return CCRectMake(heroPosition.x - 25,heroPosition.y - 10,50,20);
}


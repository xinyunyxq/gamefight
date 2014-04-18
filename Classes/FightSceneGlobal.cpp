#include "FightSceneGlobal.h"

DECLARE_SINGLETON_MEMBER(FightSceneGlobal);

FightSceneGlobal::FightSceneGlobal()
{
	_fightScene = SceneReader::sharedSceneReader()->createNodeWithSceneFile("publish\\FightScene.json");

	CCComRender* Render10005 = (CCComRender*)(this->getFightScene()->getChildByTag(10005)->getComponent("CCArmature"));
	_heroArmature = (CCArmature*)(Render10005->getNode());

	CCComRender* Render10006 = (CCComRender*)(this->getFightScene()->getChildByTag(10006)->getComponent("CCArmature"));
	_enemyArmature = (CCArmature*)(Render10006->getNode());

	CCComRender* Render10007 = (CCComRender*)(this->getFightScene()->getChildByTag(10007)->getComponent("GUIComponent"));
	_uiLayer = (ui::Layout *)(Render10007->getNode());

	

	CCComRender* Render10011 = (CCComRender*)(this->getFightScene()->getChildByTag(10011)->getComponent("GUIComponent"));
	ui::Layout * pControlLayer = (ui::Layout *)(Render10011->getNode());

	_ubPlate= dynamic_cast<ui::UIButton*>(ui::UIHelper::seekWidgetByName(pControlLayer, "Plate"));
	_ubAtk = dynamic_cast<ui::UIButton*>(ui::UIHelper::seekWidgetByName(pControlLayer, "Atk"));
	_ball= dynamic_cast<ui::ImageView*>(ui::UIHelper::seekWidgetByName(pControlLayer, "Ball"));
}

FightSceneGlobal::~FightSceneGlobal(void)
{

}
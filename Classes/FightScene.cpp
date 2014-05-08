#include "FightScene.h"
#include "FightSceneGlobal.h"

CCScene* FightScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    FightScene *layer = FightScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool FightScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(FightScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...
	
	this->addChild(FightSceneGlobal::instance()->getFightScene(), 0);
	hero = new Hero();
	enemy = new Enemy();
	this->setMovearea(CCRectMake(0,180,960,90));
	inOrder = false;

	FightSceneGlobal::instance()->getUbPlate()->addTouchEventListener(this, toucheventselector(FightScene::tbPlatePushDownCallback));
	FightSceneGlobal::instance()->getUbAtk()->addTouchEventListener(this, toucheventselector(FightScene::tbAtkCallback));

	//schedule(schedule_selector(FightScene::HeroUpdate));
	scheduleUpdate();
    
	/*CCDrawNode* front=CCDrawNode::create();
	ccColor4F yellow = {1, 1, 0, 1};
	CCPoint rect[4]={ccp(-30,30),ccp(30,30),ccp(30,-30),ccp(-30,-30)};
	front->drawPolygon(rect, 4, yellow, 0, yellow);
	front->setPosition(ccp(100, 100));
	this->addChild(front);*/

	
    return true;
}


void FightScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void FightScene::tbPlatePushDownCallback(CCObject *psender, TouchEventType type)
{
	ui::UIButton* pbut = (ui::UIButton*)psender;
	ImageView* ball = FightSceneGlobal::instance()->getBall();
	static bool isTouchBeginInPlate = false;
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		{
			float radius = getDis(pbut,type);
			CCPoint dir = getDir(pbut,type);
			if (radius < pbut->getContentSize().width * pbut->getScaleX()/2)
			{
				isTouchBeginInPlate = true;
				ball->setPosition(pbut->getTouchStartPos());
				if(radius > pbut->getContentSize().width * pbut->getScaleX()/8)
				{
					hero->PlayState(heroRun);
				}
				else
				{
					hero->PlayState(heroLoading);
				}
			}
			else
			{
				isTouchBeginInPlate = false;
			}
		}
		break;
	case TOUCH_EVENT_MOVED:
		{
			if (isTouchBeginInPlate == true)
			{
				float radius = getDis(pbut,type);
				CCPoint dir = getDir(pbut,type);
				if (radius < pbut->getContentSize().width * pbut->getScaleX()/2)
				{
					ball->setPosition(pbut->getTouchMovePos());
					if(radius > pbut->getContentSize().width * pbut->getScaleX()/8)
					{
						hero->PlayState(heroRun);
					}
					else 
					{
						hero->PlayState(heroLoading);
					}
				}
				else
				{
					CCPoint currentPos = pbut->getPosition() + dir * pbut->getContentSize().width * pbut->getScaleX()/2;
					ball->setPosition(currentPos);
				}
			}
		}
		break;
	case TOUCH_EVENT_ENDED:
		ball->setPosition(pbut->getPosition());
		hero->PlayState(heroLoading);
		break;

	case TOUCH_EVENT_CANCELED:
		ball->setPosition(pbut->getPosition());
		hero->PlayState(heroLoading);
		break;
	default:
		break;
	}
}

CCPoint FightScene::getDir(ui::UIButton* pbut,TouchEventType type)
{
	CCPoint PlatePos = pbut->getPosition();
	CCPoint startPos = pbut->getTouchStartPos();
	CCPoint movePos = pbut->getTouchMovePos();
	CCPoint Direction;

	switch(type)
	{
		case TOUCH_EVENT_BEGAN:
			Direction = (startPos - PlatePos).normalize();
			break;
		case TOUCH_EVENT_MOVED:
			Direction = (movePos - PlatePos).normalize();
			break;
		case TOUCH_EVENT_ENDED:
			break;
	}
	this->setKeyDir(Direction);
	CCLog("DirPos:%f %f",Direction.x,Direction.y);
	return Direction;
}

float FightScene::getDis(UIButton* pbut,TouchEventType type)
{
	CCPoint PlatePos = pbut->getPosition();
	CCPoint startPos = pbut->getTouchStartPos();
	CCPoint movePos = pbut->getTouchMovePos();
	float Distance;

	switch(type)
	{
	case TOUCH_EVENT_BEGAN:
		Distance = startPos.getDistance(PlatePos);
		break;
	case TOUCH_EVENT_MOVED:
		Distance = movePos.getDistance(PlatePos);
		break;
	case TOUCH_EVENT_ENDED:
		break;
	}

	return Distance;
}

void FightScene::tbAtkCallback(cocos2d::CCObject *pSender,TouchEventType type)
{
	switch(type)
	{
	case TOUCH_EVENT_BEGAN:
		//hero->PlayState(heroAtk);
		//CCLog("ATK happen");
		break;
	case TOUCH_EVENT_MOVED:
		break;
	case TOUCH_EVENT_ENDED:
		hero->PlayState(heroAtk);
		CCLog("ATK happen");
		break;
	case TOUCH_EVENT_CANCELED:
		break;
	}
}

void FightScene::update(float delta)
{
	enemyAI();
	HeroUpdate();
	enemyUpdate();
}

void FightScene::enemyAI()
{
	int runChance;
	int loadingChance;
	if (inOrder == false)
	{
		if(enemy->inAtkRange())
		{
			runChance = 0;
			loadingChance = 1;
		}
		else
		{
			runChance = 7;
			loadingChance = 9;
		}
		int randomChoice = random_range(0, 10);
		if(randomChoice < runChance)
		{
			enemy->PlayState(enemyRun);
			inOrder = true;
		}
		else if (randomChoice < loadingChance)
		{
			enemy->PlayState(enemyLoading);
			inOrder = true;
		}
		else
		{
			enemy->PlayState(enemyAtk);
			inOrder = true;
		}
	}
}

void FightScene::enemyUpdate()
{
	CCPoint heroPosition = FightSceneGlobal::instance()->getHeroArmature()->getParent()->getPosition();
	CCPoint enemyPosition = FightSceneGlobal::instance()->getEnemyArmature()->getParent()->getPosition();
	CCPoint position = enemyPosition - heroPosition;
	
	switch(enemy->getenemyState())
	{
	case enemyRun:
		{
			static int runOrderLast = 0;
			if((runOrderLast > 80 && inOrder == true)||enemy->inAtkRange())
			{
				runOrderLast = 0;
				inOrder = false;
			}
			else
			{
				runOrderLast ++;
				CCPoint nextPosition = enemyPosition;
				if(position.x > 150)
				{
					nextPosition.x = enemyPosition.x - 0.5 * enemy->getenemySpeed();
					if(enemy->getisleft() == false)
					{
						enemy->setisleft(true);
						FightSceneGlobal::instance()->getEnemyArmature()->setScaleX(1.0f);
					}
				}
				if (position.x < -150)
				{
					nextPosition.x = enemyPosition.x + 0.5 * enemy->getenemySpeed();
					if(enemy->getisleft() == true)
					{
						enemy->setisleft(false);
						FightSceneGlobal::instance()->getEnemyArmature()->setScaleX(-1.0f);
					}
				}
				if(position.y > 15)
				{
					nextPosition.y = enemyPosition.y - 0.5 * enemy->getenemySpeed();
				}
				if (position.y < -15)
				{
					nextPosition.y = enemyPosition.y + 0.5 * enemy->getenemySpeed();
				}
				if(enemy->getEnemyArea(nextPosition).intersectsRect(hero->getHeroArea(heroPosition)))
				{

				}
				else
				{
					enemyPosition = nextPosition;
				}
				FightSceneGlobal::instance()->getEnemyArmature()->getParent()->setPosition(enemyPosition);
			}
		}
		break;
	case enemyAtk:
		{
			static bool check_once = true;
			if(FightSceneGlobal::instance()->getEnemyArmature()->getAnimation()->getCurrentFrameIndex() == 10 && check_once == true)
			{
				check_once = false;
				CCLog("ATK in 10 frame");
				if(abs(heroPosition.y - enemyPosition.y) < 20 && abs(heroPosition.x-enemyPosition.x) < 220)
				{
					if ((enemyPosition.x > heroPosition.x && enemy->getisleft() == true)||(enemyPosition.x < heroPosition.x && enemy->getisleft() == false))
					{
						hero->PlayState(heroSmitten);
						if (hero->getHpValue()-enemy->getAtkValue() < 0)
						{
							hero->setHpValue(0);
						}
						else
						{
							hero->setHpValue(hero->getHpValue()-enemy->getAtkValue());
						}
						hero->getHpBar()->setPercent(hero->getHpValue()*100/hero->getHpValueMax());
					}

				}
			}
			if (FightSceneGlobal::instance()->getEnemyArmature()->getAnimation()->getIsComplete())
			{
				check_once = true;
				inOrder = false;
				//enemy->PlayState(heroLoading);
			}
		}
		break;
	case enemySmitten:
		if (FightSceneGlobal::instance()->getEnemyArmature()->getAnimation()->getIsComplete())
		{
			if (enemy->getHpValue() <=0 )
			{
				enemy->PlayState(enemyDeath);
			}
			else
			{
				enemy->PlayState(enemyLoading);
			}
		}
		break;
	case enemyLoading:
		static int loadingOrderLast = 0;
		if(loadingOrderLast > 40 && inOrder == true)
		{
			loadingOrderLast = 0;
			inOrder = false;
		}
		else
		{
			loadingOrderLast ++;
		}
		break;
	}
}

void FightScene::HeroUpdate()
{
	CCPoint heroPosition = FightSceneGlobal::instance()->getHeroArmature()->getParent()->getPosition();
	CCPoint enemyPosition = FightSceneGlobal::instance()->getEnemyArmature()->getParent()->getPosition();
	switch(hero->getheroState())
	{
	case heroRun:
		{
			CCPoint nextPosition;
			nextPosition.x = heroPosition.x + this->getKeyDir().x * hero->getheroSpeed();
			nextPosition.y = heroPosition.y + this->getKeyDir().y * hero->getheroSpeed();
			if(hero->getHeroArea(nextPosition).intersectsRect(enemy->getEnemyArea(enemyPosition)))
			{

			}
			else
			{
				if(nextPosition.x < this->getMovearea().getMinX() || nextPosition.x > this->getMovearea().getMaxX())
				{
					nextPosition.x = heroPosition.x;
				}
				if(nextPosition.y < this->getMovearea().getMinY() || nextPosition.y > this->getMovearea().getMaxY())
				{
					nextPosition.y = heroPosition.y;
				}
				heroPosition = nextPosition;
			}
			if(heroPosition.y >enemyPosition.y)
			{
				FightSceneGlobal::instance()->getHeroArmature()->getParent()->setZOrder(1);
				FightSceneGlobal::instance()->getEnemyArmature()->getParent()->setZOrder(2);
			}
			else
			{
				FightSceneGlobal::instance()->getHeroArmature()->getParent()->setZOrder(2);
				FightSceneGlobal::instance()->getEnemyArmature()->getParent()->setZOrder(1);
			}
			if(this->getKeyDir().x > 0 && hero->getisleft() == true)
			{
				hero->setisleft(false);
				FightSceneGlobal::instance()->getHeroArmature()->setScaleX(1.0f);
			}
			else if(this->getKeyDir().x < 0 && hero->getisleft() == false)
			{
				hero->setisleft(true);
				FightSceneGlobal::instance()->getHeroArmature()->setScaleX(-1.0f);
			}
			FightSceneGlobal::instance()->getHeroArmature()->getParent()->setPosition(heroPosition);
		}
	break;
	case heroAtk:
		{
			static bool check_once = true;
			if(FightSceneGlobal::instance()->getHeroArmature()->getAnimation()->getCurrentFrameIndex() == 10 && check_once == true)
			{
				check_once = false;
				CCLog("ATK in 10 frame");
				if(abs(heroPosition.y - enemyPosition.y) < 20 && abs(heroPosition.x-enemyPosition.x) < 220)
				{
					if ((heroPosition.x > enemyPosition.x && hero->getisleft() == true)||(heroPosition.x < enemyPosition.x && hero->getisleft() == false))
					{
						enemy->PlayState(enemySmitten);
						if (enemy->getHpValue()-hero->getAtkValue() < 0)
						{
							enemy->setHpValue(0);
						}
						else
						{
							enemy->setHpValue(enemy->getHpValue()-hero->getAtkValue());
						}
						enemy->getHpBar()->setPercent(enemy->getHpValue()*100/enemy->getHpValueMax());
					}

				}
			}
			if (FightSceneGlobal::instance()->getHeroArmature()->getAnimation()->getIsComplete())
			{
				check_once = true;
				hero->PlayState(heroLoading);
			}
		}
		
	break;
	case heroSmitten:
		if (FightSceneGlobal::instance()->getHeroArmature()->getAnimation()->getIsComplete())
		{
			if (hero->getHpValue() <=0 )
			{
				hero->PlayState(heroDeath);
			}
			else
			{
				hero->PlayState(heroLoading);
			}
		}
		break;
	}
}

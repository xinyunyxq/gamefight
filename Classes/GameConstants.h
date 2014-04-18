#ifndef __GAME_CONSTANTS_H__
#define __GAME_CONSTANTS_H__

typedef enum
{
	heroLoading = 0,
	heroRun,
	heroAtk,
	heroSmitten,
}HeroState;

typedef enum
{
	enemyLoading = 0,
	enemyRun,
	enemyAtk,
	enemySmitten,
}EnemyState;

#endif
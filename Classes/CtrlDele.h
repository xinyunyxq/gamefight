#ifndef __CTRLDELE_H
#define __CTRLDELE_H
#include "cocos2d.h"

USING_NS_CC;

class CtrlDele
{
public:
	virtual void onMove(CCPoint Dir) = 0;
	virtual void onAtk(void) = 0;
};

#endif
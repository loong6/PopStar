#ifndef _SPECIAL_EFFECT_H_
#define _SPECIAL_EFFECT_H_


#include "cocos2d.h"
#include "Star.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

// 星星爆炸的粒子特效
void starSpecialEffect(Star* sta,Point position,Node* node,int staNum);
Color4F getColor4F(int imgIndex);

// combo图片效果
void comboEffect(int num,Node* node);



#endif

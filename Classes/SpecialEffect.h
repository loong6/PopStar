#ifndef _SPECIAL_EFFECT_H_
#define _SPECIAL_EFFECT_H_


#include "cocos2d.h"
#include "Star.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

// ���Ǳ�ը��������Ч
void starSpecialEffect(Star* sta,Point position,Node* node,int staNum);
Color4F getColor4F(int imgIndex);

// comboͼƬЧ��
void comboEffect(int num,Node* node);



#endif

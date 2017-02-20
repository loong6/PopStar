
#include "SpecialEffect.h"


void starSpecialEffect(Star* sta,Point position,Node* node,int staNum)
{
	// ������ը����Ч������������Ϊ staNum ��
	ParticleExplosion* effect = ParticleExplosion::createWithTotalParticles(staNum);
	// ���ô�������Ч������ͼƬ
    effect->setTexture(Director::getInstance()->getTextureCache()->addImage("star.png"));
	// ���ÿ�ʼʱ���������ɫ
	effect->setStartColor(getColor4F(sta->getImgIndex()));
	effect->setStartColorVar(Color4F(0,0,0,1));
    effect->setEndColor(getColor4F(sta->getImgIndex()));
    effect->setEndColorVar(Color4F(0,0,0,1));
	// ���ÿ�ʼʱ�����Ӵ�С
    effect->setStartSize(20.0f);
    effect->setGravity(Point(0,-300));
	// ����������������
    effect->setLife(2.0f);
	// ���������ٶ�
    effect->setSpeed(200);
    effect->setSpeedVar(10);
	// ��������λ��
    effect->setPosition(position);
    node->addChild(effect,2);
}
 
Color4F getColor4F(int imgIndex)
{
	switch(imgIndex){
	case 0:
		//red
		return Color4F::RED;
    case 1:
		//blue
		return Color4F::BLUE;
    case 2:
		//green
		return Color4F::GREEN;
    case 3:
		//purple
		return Color4F(128.0f,0,128.0f,1.0f);
    case 4:
		//yellow
		return Color4F::YELLOW;
    }
    return Color4F(1,1,1,0);
}

void comboEffect(int num,Node* node){
	
	if( num < 5 )
		return;

	Sprite* comboSprite;
	if( num >= 10 ){
		comboSprite = Sprite::create("combo_3.png");
	}else if( num >= 7 ){
		comboSprite = Sprite::create("combo_2.png");
	}else{
		comboSprite = Sprite::create("combo_1.png");
	}

	comboSprite->setPosition(Vec2(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2));
	node->addChild(comboSprite,4);

	Blink* blink = Blink::create(1.0f,5);
	CallFunc* remove = CallFunc::create([=](){comboSprite->removeFromParentAndCleanup(true);});
	Sequence* action = Sequence::create(blink,remove,nullptr);
	comboSprite->runAction(action);
}
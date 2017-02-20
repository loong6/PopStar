
#include "SpecialEffect.h"


void starSpecialEffect(Star* sta,Point position,Node* node,int staNum)
{
	// 创建爆炸粒子效果，粒子数量为 staNum 个
	ParticleExplosion* effect = ParticleExplosion::createWithTotalParticles(staNum);
	// 设置此粒子特效的纹理图片
    effect->setTexture(Director::getInstance()->getTextureCache()->addImage("star.png"));
	// 设置开始时候的粒子颜色
	effect->setStartColor(getColor4F(sta->getImgIndex()));
	effect->setStartColorVar(Color4F(0,0,0,1));
    effect->setEndColor(getColor4F(sta->getImgIndex()));
    effect->setEndColorVar(Color4F(0,0,0,1));
	// 设置开始时的粒子大小
    effect->setStartSize(20.0f);
    effect->setGravity(Point(0,-300));
	// 设置粒子生命周期
    effect->setLife(2.0f);
	// 设置粒子速度
    effect->setSpeed(200);
    effect->setSpeedVar(10);
	// 设置粒子位置
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
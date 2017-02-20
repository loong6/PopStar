
#include "FloatWord.h"

FloatWord* FloatWord::create( const std::string& word,const int fontSize,Vec2 begin )
{
	FloatWord* fw = new FloatWord();
	if( !fw->init(word,fontSize,begin) )	{
		return NULL;
	}
	
	fw->autorelease();
	return fw;
}

bool FloatWord::init( const std::string& word,const int fontSize,Vec2 begin )
{
	if( !Node::init() )	{
		return false;
	}
	this->fw_fontSize = fontSize;
	this->fw_begin = begin;

	this->fw_label = Label::create(word,"Marker Felt",fontSize);
	fw_label->setPosition(begin);
	this->addChild(fw_label);

	return true;
}

void FloatWord::floatInOut(const float speed,const float delayTime,std::function<void()> callback){
	
	MoveTo* moveIn = MoveTo::create(speed,Vec2(GAME_SCREEN_WIDTH/2,fw_begin.y));
	MoveTo* moveOut = MoveTo::create(speed,Vec2(-fw_label->getContentSize().width,fw_begin.y));

	CallFunc* call = CallFunc::create(callback);

	Sequence* action = Sequence::create(moveIn,DelayTime::create(delayTime),moveOut,call,NULL);
	fw_label->runAction(action);
}

void FloatWord::floatIn(const float speed){
	
	MoveTo* moveIn = MoveTo::create(speed,Vec2(GAME_SCREEN_WIDTH/2,fw_begin.y));

	Sequence* action = Sequence::create(moveIn,NULL);
	fw_label->runAction(action);
}

void FloatWord::floatOut(const float speed,const float delayTime){
	
	MoveTo* moveOut = MoveTo::create(speed,Vec2(-fw_label->getContentSize().width,fw_begin.y));

	Sequence* action = Sequence::create(DelayTime::create(delayTime),moveOut,NULL);
	fw_label->runAction(action);
}
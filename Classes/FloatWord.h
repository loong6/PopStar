#ifndef __FLOATWORD_H__
#define __FLOATWORD_H__

#include "cocos2d.h"
#include "GameDefine.h"

USING_NS_CC;

class FloatWord : public Node
{
public:
	/*********** ��ʼ�� ���� ���� ***********/
	static FloatWord* create(const std::string& word,const int fontSize,Vec2 begin);
	virtual bool init(const std::string& word,const int fontSize,Vec2 begin);

	/*********** Ч�� ***********/
	void floatIn(const float speed);
	void floatOut(const float speed,const float delayTime);
	void floatInOut(const float speed,const float delayTime,std::function<void()> callback);

private:
	int fw_fontSize;
	Point fw_begin;
	Label* fw_label;
};


#endif
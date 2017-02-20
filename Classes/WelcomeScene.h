#ifndef __WLECOME_SCENE_H__
#define __WLECOME_SCENE_H__

#include "cocos2d.h"
#include "GameDefine.h"


USING_NS_CC;

class WelcomeScene : public Layer
{
public:
	/*********** ��ʼ�� ���� ���� ***********/
	WelcomeScene();
	static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(WelcomeScene);

	/*********** ��ť�ص����� ***********/
	void menuStartCallback(Ref *pSender);
	void menuMusicCallback( Ref *pSender );
	void menuContinueCallback(Ref *pSender);
	void menuCloseCallback( Ref *pSender );

	/*********** ���� ***********/
	virtual void onEnterTransitionDidFinish();
	virtual void cleanup();

	// �������� ������Ϸ �Ĺ���
	CC_SYNTHESIZE(bool, _isCon, IsCon);

};

#endif
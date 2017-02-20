#ifndef __WLECOME_SCENE_H__
#define __WLECOME_SCENE_H__

#include "cocos2d.h"
#include "GameDefine.h"


USING_NS_CC;

class WelcomeScene : public Layer
{
public:
	/*********** 初始化 创建 结束 ***********/
	WelcomeScene();
	static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(WelcomeScene);

	/*********** 按钮回调函数 ***********/
	void menuStartCallback(Ref *pSender);
	void menuMusicCallback( Ref *pSender );
	void menuContinueCallback(Ref *pSender);
	void menuCloseCallback( Ref *pSender );

	/*********** 音乐 ***********/
	virtual void onEnterTransitionDidFinish();
	virtual void cleanup();

	// 便于设置 继续游戏 的功能
	CC_SYNTHESIZE(bool, _isCon, IsCon);

};

#endif
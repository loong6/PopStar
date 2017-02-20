#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameDefine.h"
#include "Star.h"

USING_NS_CC;

class Star;

class GameScene : public Layer
{
public:
	/*********** 初始化 创建 结束 ***********/
	GameScene();
	static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
	void initMap();
	void createStar( int row , int col );
	// 关卡结束
	void levelOver( float dt );
	//游戏结束
	void gameOver( float dt );

	/*********** 关于星星的函数 ***********/
	// 返回剩余星星的个数
	int totalStarNum( void );
	// 扩展等待消除的星星
	int waitPop(int row , int col);
	// 消除星星
	void deleteStar( void );
	// 整合星星
	void adjustStar(void);
	// 是否没有可消除的星星
	bool isFinish(void);
	// 消除最后的星星
	void popFinishStar(int n);

	/*********** 触摸事件 与 更新 ***********/
	bool onTouchBegan(Touch *touch, Event *unused);
	void update(float dt);

	/*********** 工具函数 ***********/
	// 根据触摸点，判断地图上的星星位置
	Star* starOfPoint(Point *point);
	// 根据行列值，返回地图上的位置
	Point positionOfItem(int row , int col);
	
	/*********** 声音相关 ***********/
	// 场景加载完毕
	virtual void onEnterTransitionDidFinish();
	// 场景释放时，清空背景音乐
	virtual void cleanup();
	// combo 音效
	void playCombo( int num );

	/*********** 按钮回调函数 ***********/
	void menuBackCallback(Ref *pSender);
private:
	/*********** 全局 主要变量 ***********/
	// 绘制一批图片
	Sprite* starSheet;
	// 地图二维数组
	Star* map[ROWS][COLS];

	/*********** 工具变量 ***********/
	// 绘图的最下角坐标位置
	float mapLBX,mapLBY;
	// 标记数组
	bool mapR[ROWS][COLS];
	// 每次等待消除星星数量
	int waitDelNum;
	// 关卡
	int _level;
	// 当前分数
	int _score;
	// 是否过关图片标志
	bool isWin;

	/*********** 处理关卡结束时的变量 ***********/
	// flag——当前关卡结束
	bool isLevelFinish;
	// 记录消除的时间
	float deleteTime;
	// 需要一个个消除的星星数量
	int needDelOneByOne;

};


/* 
	关于 GameScene 的层次问题  
0: 背景图
1: 星星矩阵
2: 粒子特效
3: 漂浮字体
4: combo特效
5: 过关标志
8: 界面各种Label
*/
#endif
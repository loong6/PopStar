#ifndef __GAME_DEFINE_H__
#define __GAME_DEFINE_H__



/*********** UI 尺寸 相关 ***********/
// 定义屏幕宽高，这与所做的图片有关
#define GAME_SCREEN_WIDTH 480
#define GAME_SCREEN_HEIGHT 800

// 定义每个精灵大小与边框大小
#define STAR_WIDTH 48
#define BOADER_WIDTH 0.5



/*********** 工具设定 ***********/
// 行列值
#define ROWS 10
#define COLS 10

// 当星星一个个消除时，间隔的时间
#define DELSTAR_ONEBYONE_TIME 0.4

// 分数存储
#define userDefault CCUserDefault::sharedUserDefault()



/*********** 星星相关 ***********/
// 星星总数
#define TOTAL_STAR 5
// 星星的模式，NORMAL 普通状态，HEART 高亮状态
enum DisplayMode{
    DISPLAY_MODE_NORMAL = 0,
    DISPLAY_MODE_HEART
};
// 普通状态
static const char *starNormal[TOTAL_STAR] = {
	"red.png",
	"blue.png",
	"green.png",
	"purple.png",
	"yellow.png"
};

// 高亮状态
static const char *starHeart[TOTAL_STAR] = {
	"red_heart.png",
	"blue_heart.png",
	"green_heart.png",
	"purple_heart.png",
	"yellow_heart.png"
};

// 剩余星星所奖励的分数
static const int rewardScore[11] = {
	2000,
	1980,
	1920,
	1820,
	1680,
	1500,
	1280,
	1020,
	720,
	380,
	0
};

#endif
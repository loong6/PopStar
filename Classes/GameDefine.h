#ifndef __GAME_DEFINE_H__
#define __GAME_DEFINE_H__



/*********** UI �ߴ� ��� ***********/
// ������Ļ��ߣ�����������ͼƬ�й�
#define GAME_SCREEN_WIDTH 480
#define GAME_SCREEN_HEIGHT 800

// ����ÿ�������С��߿��С
#define STAR_WIDTH 48
#define BOADER_WIDTH 0.5



/*********** �����趨 ***********/
// ����ֵ
#define ROWS 10
#define COLS 10

// ������һ��������ʱ�������ʱ��
#define DELSTAR_ONEBYONE_TIME 0.4

// �����洢
#define userDefault CCUserDefault::sharedUserDefault()



/*********** ������� ***********/
// ��������
#define TOTAL_STAR 5
// ���ǵ�ģʽ��NORMAL ��ͨ״̬��HEART ����״̬
enum DisplayMode{
    DISPLAY_MODE_NORMAL = 0,
    DISPLAY_MODE_HEART
};
// ��ͨ״̬
static const char *starNormal[TOTAL_STAR] = {
	"red.png",
	"blue.png",
	"green.png",
	"purple.png",
	"yellow.png"
};

// ����״̬
static const char *starHeart[TOTAL_STAR] = {
	"red_heart.png",
	"blue_heart.png",
	"green_heart.png",
	"purple_heart.png",
	"yellow_heart.png"
};

// ʣ�������������ķ���
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
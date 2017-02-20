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
	/*********** ��ʼ�� ���� ���� ***********/
	GameScene();
	static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
	void initMap();
	void createStar( int row , int col );
	// �ؿ�����
	void levelOver( float dt );
	//��Ϸ����
	void gameOver( float dt );

	/*********** �������ǵĺ��� ***********/
	// ����ʣ�����ǵĸ���
	int totalStarNum( void );
	// ��չ�ȴ�����������
	int waitPop(int row , int col);
	// ��������
	void deleteStar( void );
	// ��������
	void adjustStar(void);
	// �Ƿ�û�п�����������
	bool isFinish(void);
	// ������������
	void popFinishStar(int n);

	/*********** �����¼� �� ���� ***********/
	bool onTouchBegan(Touch *touch, Event *unused);
	void update(float dt);

	/*********** ���ߺ��� ***********/
	// ���ݴ����㣬�жϵ�ͼ�ϵ�����λ��
	Star* starOfPoint(Point *point);
	// ��������ֵ�����ص�ͼ�ϵ�λ��
	Point positionOfItem(int row , int col);
	
	/*********** ������� ***********/
	// �����������
	virtual void onEnterTransitionDidFinish();
	// �����ͷ�ʱ����ձ�������
	virtual void cleanup();
	// combo ��Ч
	void playCombo( int num );

	/*********** ��ť�ص����� ***********/
	void menuBackCallback(Ref *pSender);
private:
	/*********** ȫ�� ��Ҫ���� ***********/
	// ����һ��ͼƬ
	Sprite* starSheet;
	// ��ͼ��ά����
	Star* map[ROWS][COLS];

	/*********** ���߱��� ***********/
	// ��ͼ�����½�����λ��
	float mapLBX,mapLBY;
	// �������
	bool mapR[ROWS][COLS];
	// ÿ�εȴ�������������
	int waitDelNum;
	// �ؿ�
	int _level;
	// ��ǰ����
	int _score;
	// �Ƿ����ͼƬ��־
	bool isWin;

	/*********** ����ؿ�����ʱ�ı��� ***********/
	// flag������ǰ�ؿ�����
	bool isLevelFinish;
	// ��¼������ʱ��
	float deleteTime;
	// ��Ҫһ������������������
	int needDelOneByOne;

};


/* 
	���� GameScene �Ĳ������  
0: ����ͼ
1: ���Ǿ���
2: ������Ч
3: Ư������
4: combo��Ч
5: ���ر�־
8: �������Label
*/
#endif
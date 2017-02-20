#ifndef __STAR_H__
#define __STAR_H__

#include "cocos2d.h"
#include "GameDefine.h"

USING_NS_CC;

class Star : public Sprite
{
public:
	/*********** 初始化 创建 结束 ***********/
	Star();
	static Star* create( int row , int col );

	// 设定星星显示状态
	void setDisplayMode(DisplayMode mode);

	/*********** 设定函数 ***********/
	CC_SYNTHESIZE(int, m_row, Row);
    CC_SYNTHESIZE(int, m_col, Col);
	CC_SYNTHESIZE(int, m_imgIndex, ImgIndex);
    CC_SYNTHESIZE_READONLY(DisplayMode, m_displayMode, DisplayMode);


};


#endif

#include "Star.h"

Star::Star()
: m_col(0)
, m_row(0)
, m_imgIndex(0)
, m_displayMode(DISPLAY_MODE_NORMAL)
{
}

Star *Star::create( int row , int col )
{
	Star *spr = new Star();
	spr->m_row = row;
	spr->m_col = col;
    spr->m_imgIndex = rand() % TOTAL_STAR;
    spr->initWithSpriteFrameName(starNormal[spr->m_imgIndex]);
	spr->autorelease();
	return spr;
}

void Star::setDisplayMode(DisplayMode mode)
{
	m_displayMode = mode;
    
    SpriteFrame *frame;
    switch (mode) {
        case DISPLAY_MODE_NORMAL:
            frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(starNormal[m_imgIndex]);
            break;
        case DISPLAY_MODE_HEART:
            frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(starHeart[m_imgIndex]);
            break;
        default:
            return;
    }
    setDisplayFrame(frame);
}
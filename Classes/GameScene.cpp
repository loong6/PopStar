
#include "string.h"
#include "FloatWord.h"
#include "GameScene.h"
#include "WelcomeScene.h"
#include "SpecialEffect.h"
#include "SimpleAudioEngine.h"
	
using namespace CocosDenshion;

GameScene::GameScene()	
: starSheet(NULL)
,mapLBX ( 0 )
,mapLBY ( 0 )
,_level( 1 )
,_score( 0 )
,isLevelFinish( false )
,deleteTime( 0 )
,isWin( false )
{
	// 初始化 mapR 数组(string.h 头文件)
	memset(mapR,false,sizeof(mapR));
}

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
	auto layer = GameScene::create();
    scene->addChild(layer);

    return scene;
}

bool GameScene::init()
{
	if( !Layer::init() )	{
		return false;
	}

	// 加载plist和png
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("stars.plist");
    starSheet = Sprite::create();
	starSheet->setAnchorPoint(Vec2::ZERO);
    this->addChild(starSheet,1);

	// 背景图片
    auto sprite = Sprite::create("bg_gamescene.jpg");
	sprite->setPosition(Vec2(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2));
    this->addChild(sprite, 0);

	// 预加载音乐
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/music.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/readygo.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/pop.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/clear.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/select.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_1.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_2.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_3.ogg");

	/*********** 界面显示文字 ***********/
	// 最高分
	if(!userDefault->getIntegerForKey("HightScore")){
		 userDefault->setIntegerForKey("HightScore",0);
	}
	// 最高分
	auto labelHScore = Label::create(StringUtils::format("Highest: %d ",userDefault->getIntegerForKey("HightScore")),"Marker Felt",26);
	labelHScore -> setPosition(Vec2( GAME_SCREEN_WIDTH/2 , GAME_SCREEN_HEIGHT - labelHScore->getContentSize().height ));
	this->addChild(labelHScore,8);
	// 当前关卡
	auto labelLevel = Label::create(StringUtils::format("Level: %d ",_level),"Marker Felt",26);
	labelLevel -> setPosition(Vec2(labelLevel->getContentSize().width,GAME_SCREEN_HEIGHT-labelLevel->getContentSize().height*2.5));
	labelLevel -> setTag(2);
	this->addChild(labelLevel,8);
	// 目标分数
	auto labelAimScore = Label::create(StringUtils::format("Aim: %d ",(_level-1)*2000+1000),"Marker Felt",26);
	labelAimScore -> setPosition(Vec2(labelLevel->getContentSize().width*3,GAME_SCREEN_HEIGHT-labelLevel->getContentSize().height*2.5));
	labelAimScore -> setTag(4);
	this->addChild(labelAimScore,8);
	// 当前分数
	auto labelScore = Label::create(StringUtils::format("Score: %d ",_score),"Marker Felt",36);
	labelScore -> setPosition(Vec2(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT-labelLevel->getContentSize().height*4));
	labelScore -> setTag(6);
	this->addChild(labelScore,8);
	// 提示信息
	auto labelTip = Label::create("","Marker Felt",26);
	labelTip -> setPosition(Vec2(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT-labelLevel->getContentSize().height*6));
	labelTip -> setTag(8);
	this->addChild(labelTip,8);

	/************* 漂浮文字效果 *************/
	// 关卡
	FloatWord* fwLevel = FloatWord::create(StringUtils::format("Level : %d",_level),36,Vec2(GAME_SCREEN_WIDTH*1.2,GAME_SCREEN_HEIGHT/10*6));
	fwLevel->floatInOut(0.5f,2.0f,CC_CALLBACK_0(GameScene::initMap,this));
	this->addChild(fwLevel,3);
	// 目标分数
	FloatWord* fwScore = FloatWord::create(StringUtils::format("Aim : %d",(_level-1)*2000+1000),36,Vec2(GAME_SCREEN_WIDTH*1.2,GAME_SCREEN_HEIGHT/10*5));
	fwScore->floatIn(0.5f);
	fwScore->floatOut(0.5f,2.5f);
	this->addChild(fwScore,3);

	// 返回主界面
	auto backItem = MenuItemImage::create(
                                           "pic_back.png",
                                           "pic_back.png",
										   CC_CALLBACK_1(GameScene::menuBackCallback, this));
    
	backItem->setPosition(Vec2(GAME_SCREEN_WIDTH-labelLevel->getContentSize().width/4,GAME_SCREEN_HEIGHT-labelLevel->getContentSize().height*5.5));

	auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Vec2::ZERO);
	this -> addChild( menu );

	// 开始音乐
	if( userDefault->getBoolForKey("MusicKey") )	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/readygo.ogg",false);
	}

	/************* 触摸事件处理 *************/
    auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	
	/************* 实时更新 *************/
	scheduleUpdate();

	return true;
}

void GameScene::update( float dt )
{
	// 分数变化
	Label *labelScore = (Label *)this -> getChildByTag(6);
	labelScore -> setString( StringUtils::format("Score: %d ",_score));

	// 如果当前关卡结束  星星一个个消除的实现
	if( isLevelFinish )	{

		deleteTime += dt;
		if( deleteTime > DELSTAR_ONEBYONE_TIME )	{
			popFinishStar(needDelOneByOne);
			needDelOneByOne--;
			deleteTime = 0;
		}
	}
}

// 初始化地图
void GameScene::initMap( )	{
	
	for( int r = 0 ; r < ROWS ; ++r ){
		for( int c = 0 ; c < COLS ; ++c ){
			createStar(r,c);
		}
	}
}

// 创建星星
void GameScene::createStar( int row , int col )	
{
	Star* spr = Star::create(row, col);
	
	Point pos = positionOfItem(row, col);
    spr->setPosition(pos);
    starSheet -> addChild(spr,1);

	// 填充数组相应位置
    map[row][col] = spr;
}

// 触摸事件
bool GameScene::onTouchBegan(Touch *touch, Event *unused)	{
	
	auto location = touch->getLocation();
	Star* sta;
	sta = starOfPoint(&location);
	
	// 当前对象不为空
	if( sta )	{
		// 看该 星星 处于什么状态
		if( sta->getDisplayMode() == DISPLAY_MODE_NORMAL )	{

			// 初始化记忆地图mapR+恢复普通状态
			for( int i = 0 ; i < ROWS ; i++ )	{
				for( int j = 0 ; j <COLS ; j++ )	{
					mapR[i][j] = false;
					if( map[i][j]!=NULL )
						map[i][j]->setDisplayMode(DISPLAY_MODE_NORMAL);
				}
			}

			// 如果只有当前一个星星这个颜色，不要让它处于高亮状态
			waitDelNum = waitPop(sta->getRow(),sta->getCol());
			if( waitDelNum == 1 )	{
				mapR[sta->getRow()][sta->getCol()]=false;
				sta->setDisplayMode(DISPLAY_MODE_NORMAL);
			}
			else
			{
				if( userDefault->getBoolForKey("MusicKey") )	{
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/select.ogg",false);
				}
			}	
		}
		else
		{
			deleteStar( );
			if( userDefault->getBoolForKey("MusicKey") )	{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/pop.ogg",false);
			}
			// 分数增加
			_score += waitDelNum*5+waitDelNum*(waitDelNum-1)*10/2;
			// 是否过关
			if( _score >= (_level-1)*2000+1000 && !isWin )	{
				isWin = true;
				auto sprite = Sprite::create("pic_win.png");
				sprite->setPosition(Vec2(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2));
				sprite -> setTag( 12 );
				this->addChild(sprite,5);

				Spawn* spa = Spawn::create(ScaleTo::create(1.0f,0.5),MoveTo::create(1.0f,Vec2(GAME_SCREEN_WIDTH-sprite->getContentSize().width/4,GAME_SCREEN_HEIGHT-sprite->getContentSize().height/4)),NULL);
				Sequence* action = Sequence::create(Blink::create(1.0f,3),spa,NULL);
				sprite->runAction(action);

			}


			// combo效果
			comboEffect(waitDelNum,this);
			playCombo(waitDelNum);
			// 提示效果
			Label *labelTip = (Label *)this -> getChildByTag(8);
			labelTip -> setString( StringUtils::format("delete %d stars,score: %d ",waitDelNum,waitDelNum*5+waitDelNum*(waitDelNum-1)*10/2));

			waitDelNum = 0;
			if( isFinish() )	{
				isLevelFinish = true;
				int temp = totalStarNum();

				Label *labelTip = (Label *)this -> getChildByTag(8);
				if( temp <= 10 )	{
					needDelOneByOne = temp;
					labelTip -> setString( StringUtils::format("left %d stars,score: %d ",needDelOneByOne,rewardScore[needDelOneByOne]));
					
					_score += rewardScore[needDelOneByOne];
					if( _score >= (_level-1)*2000+1000 && !isWin )	{
						isWin = true;

						auto sprite = Sprite::create("pic_win.png");
						sprite->setPosition(Vec2(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2));
						sprite -> setTag( 12 );
						this->addChild(sprite,5);

						Spawn* spa = Spawn::create(ScaleTo::create(1.0f,0.5),MoveTo::create(1.0f,Vec2(GAME_SCREEN_WIDTH-sprite->getContentSize().width/2,GAME_SCREEN_HEIGHT-sprite->getContentSize().height/2)),NULL);
						Sequence* action = Sequence::create(Blink::create(1.0f,3),spa,NULL);
						sprite->runAction(action);

					}
				}
				else
				{
					needDelOneByOne = 10;
					labelTip -> setString( StringUtils::format("left %d stars,score: 0 ",temp));
				}
			}
		}
		
	}

	return true;
}

// 根据行列，获取坐标值
Point GameScene::positionOfItem(int row , int col)
{
	float x = mapLBX + (STAR_WIDTH + BOADER_WIDTH) * col + STAR_WIDTH / 2;
    float y = mapLBY + (STAR_WIDTH + BOADER_WIDTH) * row + STAR_WIDTH / 2;
    return Point(x, y);
}

// 根据触摸点，判断地图上的星星位置
Star* GameScene::starOfPoint(Point *point)
{
    Star *sta = NULL;
    Rect rect = Rect(0, 0, 0, 0);
	Size sz;
	sz.height=STAR_WIDTH;
	sz.width=STAR_WIDTH;

	for( int r = 0 ; r < ROWS ; ++r )	{
		for( int c = 0 ; c < COLS ; ++c )	{
			sta = map[r][c];
			if( sta )	{
				rect.origin.x = sta->getPositionX() - ( STAR_WIDTH / 2);
				rect.origin.y = sta->getPositionY() - ( STAR_WIDTH / 2);

				rect.size = sz;
				if (rect.containsPoint(*point)) {
					return sta;
				}
			}
		}
	}
    
    return NULL;
}

int GameScene::waitPop(int row , int col)
{
	int i,r,c,tol;
	// 四个方向 
	int search[4][2]={-1,0,1,0,0,1,0,-1};

	tol = 1;
	map[row][col]->setDisplayMode(DISPLAY_MODE_HEART);
	mapR[row][col] = true;

	// 四个方向遍历
	for( i = 0 ; i < 4 ; i++ )	{
		r = row + search[i][0];
		c = col + search[i][1];
		if( r >= 0 && r < ROWS && c >= 0 && c < COLS && map[r][c]!=NULL )	{
			if( map[row][col]->getImgIndex() == map[r][c]->getImgIndex() && !mapR[r][c] )	{
				mapR[r][c] = true;
				tol += waitPop(r,c);
			}
		}
	}

	return tol;
}

void GameScene::deleteStar(  )
{
	int r,c;
	for( r = 0 ; r < ROWS ; r++ )	{
		for( c = 0 ;c < COLS ; c++ )	{
			if( mapR[r][c] == true )	{	

				Star* sta = map[r][c];
				starSpecialEffect(sta,sta->getPosition(),this,waitDelNum*2);
				
				map[r][c]=NULL;
				sta->removeFromParentAndCleanup(true);
			}
		}
	}

	adjustStar();
}

void GameScene::adjustStar( )
{
	int r,c;
	// 向下归拢
	for( c = 0 ; c < COLS ; c++ )	{
		for( r = 0 ; r < ROWS-1 ; r++ )	{
			if( map[r][c] == NULL )	{
				for( int newR = r+1 ; newR < ROWS ; newR++ )	{
					Star* sta = map[newR][c];
					if( sta != NULL )	{

						map[r][c] = sta;
						map[newR][c] = NULL;

						Point startPosition = sta->getPosition();
						Point endPosition = positionOfItem(r, c);
						float speed = (startPosition.y - endPosition.y) / GAME_SCREEN_HEIGHT*2;
						sta->stopAllActions();
						sta->runAction(MoveTo::create(speed, endPosition));
						sta->setRow(r);

						break;
					}
				}
			}
		}
	}

	// 向左归拢
	for( c = 0 ; c < COLS-1 ; c++ )	
		if( map[0][c] == NULL )	{
			for( int newC=c+1; newC < COLS ; newC++ )	{
				if( map[0][newC] != NULL )	{
					for( int moveR = 0 ; moveR < ROWS ; moveR++ )	{
						Star* sta = map[moveR][newC];
						
						if( sta!=NULL )	{
							map[moveR][c] = sta;
							map[moveR][newC] = NULL;

							Point startPosition = sta->getPosition();
							Point endPosition = positionOfItem(moveR,c);
							float speed = (startPosition.x - endPosition.x) / GAME_SCREEN_WIDTH*2;
							sta->stopAllActions();
							sta->runAction(MoveTo::create(speed, endPosition));
							sta->setCol(c);
						}
					}
					break;
				}
			}
		}
}

bool GameScene::isFinish( )
{
	int i,r,c;
	// 四个方向 
	int search[4][2]={-1,0,1,0,0,1,0,-1};

	for( r = 0 ; r < ROWS ; r++ )	{
		for( c = 0 ; c < COLS ; c++ )	{
			if( !map[r][c] )	continue;

			for( i = 0 ; i < 4 ; i++ )	{
				int nr = r + search[i][0];
				int nc = c + search[i][1];

				if( nr>=0 && nr<ROWS && nc>=0 && nc<COLS )	{
					if( map[nr][nc]!=NULL )	{
						if( map[r][c]->getImgIndex() == map[nr][nc]->getImgIndex() )
							return false;
					}
				}
			}
		}
	}

	return true;
}

void GameScene::popFinishStar( int n )
{
	int r,c;
	Star* sta;

	for( r = ROWS-1 ; r >= 0 ; r-- )	{
		for( c = 0 ; c < COLS ; c++ )	{
			sta = map[r][c];
			if( sta )	{
				if( n )	{
					if( userDefault->getBoolForKey("MusicKey") )	{
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/pop.ogg",false);
					}

					starSpecialEffect(sta,sta->getPosition(),this,5);
					map[r][c]=NULL;
					sta->removeFromParentAndCleanup(true);
					return;
				}
				else
				{
					if( userDefault->getBoolForKey("MusicKey") )	{
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/clear.ogg",false);
					}
					starSpecialEffect(sta,sta->getPosition(),this,totalStarNum()*4);
					map[r][c]=NULL;
					sta->removeFromParentAndCleanup(true);
				}
			}
		}
	}
	
	

	Label *labelTip = (Label *)this -> getChildByTag(8);
	labelTip->setString("");


	isLevelFinish = false;
	scheduleOnce(schedule_selector(GameScene::levelOver),2.0f);
}

void GameScene::levelOver( float dt )
{
	if( isWin )	{
		isWin = false;
		Sprite* spr = (Sprite *)this -> getChildByTag(12);
		this->removeChild(spr);
	}

	if( _score < (_level-1)*2000+1000 )	{
		auto sprite = Sprite::create("pic_gameover.png");
		sprite->setPosition(Vec2(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2));
		this->addChild(sprite,3);

		scheduleOnce(schedule_selector(GameScene::gameOver),2.0f);
	}
	else
	{
		_level++;
		/******************** 漂浮文字 效果 **********************/
		// 关卡
		FloatWord* fwLevel = FloatWord::create(StringUtils::format("Level : %d",_level),36,Vec2(GAME_SCREEN_WIDTH*1.2,GAME_SCREEN_HEIGHT/10*6));
		fwLevel->floatInOut(0.5f,2.0f,CC_CALLBACK_0(GameScene::initMap,this));
		this->addChild(fwLevel,3);
		// 目标分数
		FloatWord* fwScore = FloatWord::create(StringUtils::format("Aim : %d",(_level-1)*2000+1000),36,Vec2(GAME_SCREEN_WIDTH*1.2,GAME_SCREEN_HEIGHT/10*5));
		fwScore->floatIn(0.5f);
		fwScore->floatOut(0.5f,2.5f);
		this->addChild(fwScore,3);
		// 下一关音乐
		if( userDefault->getBoolForKey("MusicKey") )	{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/NextGameRound.ogg",false);
		}

		// 关卡变化
		Label *labelLevel = (Label *)this -> getChildByTag(2);
		labelLevel -> setString( StringUtils::format("Level: %d ",_level));
		// 目标分数变化
		Label *labelAimScore = (Label *)this -> getChildByTag(4);
		labelAimScore -> setString( StringUtils::format("Aim: %d ",(_level-1)*2000+1000));

	}

	
}

// 返回剩余星星的个数
int GameScene::totalStarNum( void )
{
	int sum = 0;
	for( int r = 0 ; r < ROWS ; r++ )
		for( int c = 0 ; c < COLS ; c++ )
			if( map[r][c]!=NULL )
				sum++;
	return sum;
}

void GameScene::playCombo(int size){
	
	if( userDefault->getBoolForKey("MusicKey") )	{
		if(size < 5)
			return;
		if(size >= 10){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/combo_3.ogg",false);
		}else if(size >= 7){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/combo_2.ogg",false);
		}else {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/combo_1.ogg",false);
		}
	}
}

// 游戏结束函数
void GameScene::gameOver(float dt)
{
	if( userDefault->getIntegerForKey("HightScore") < _score )
		userDefault->setIntegerForKey("HightScore",_score);

	auto scene = WelcomeScene::createScene();
	CCDirector::sharedDirector()->replaceScene(scene);
}

void GameScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();  
	if ( userDefault->getBoolForKey("MusicKey") ) {                      
        SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/music.ogg", true);  
    } 
}
void GameScene::cleanup()
{
	Layer::cleanup();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void GameScene::menuBackCallback(Ref *pSender)
{
	auto scene = Scene::create();
	auto layer = WelcomeScene::create();
	layer->setIsCon(true);
    scene->addChild(layer);

	CCDirector::sharedDirector()->pushScene(scene);
}

#include "GameScene.h"
#include "WelcomeScene.h"
#include "SpecialEffect.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

WelcomeScene::WelcomeScene()
	: _isCon( false )
{
}

Scene* WelcomeScene::createScene()
{
    auto scene = Scene::create();
	auto layer = WelcomeScene::create();
    scene->addChild(layer);

    return scene;
}

bool WelcomeScene::init()
{
	if( !Layer::init() )	{
		return false;
	}

	auto sprite = Sprite::create("bg_wlecomescene.jpg");
	sprite->setPosition(Vec2(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2));
    this->addChild(sprite, 0);
	
	// 添加开始按钮
	auto startItem = MenuItemImage::create(
                                           "btn_start.png",
                                           "btn_start.png",
										   CC_CALLBACK_1(WelcomeScene::menuStartCallback, this));
    
	startItem->setPosition(Vec2(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2));

	// 继续按钮
	auto continueItem = MenuItemImage::create(
                                           "btn_continue.png",
                                           "btn_continue.png",
										   CC_CALLBACK_1(WelcomeScene::menuContinueCallback, this));
	continueItem->setTag(14);
	continueItem->setPosition(Vec2(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2 - startItem->getContentSize().height*1.5 ));

	// 退出游戏
	auto closeItem = MenuItemImage::create(
                                           "btn_close.png",
                                           "btn_close.png",
										   CC_CALLBACK_1(WelcomeScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(GAME_SCREEN_WIDTH - closeItem->getContentSize().width/2*1.5,closeItem->getContentSize().height/2*1.5));

	// 音乐 音效 开关
	MenuItemToggle *musicItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(WelcomeScene::menuMusicCallback, this),
		MenuItemImage::create("menu_sound_on.png","menu_sound_on.png"),MenuItemImage::create("menu_sound_off.png","menu_sound_off.png"), NULL);       
	musicItem->setPosition(Vec2(musicItem->getContentSize().width/2,musicItem->getContentSize().height/2));  

	auto menu = Menu::create(startItem,musicItem,continueItem,closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
	this -> addChild( menu );

	if( !userDefault->getBoolForKey("MusicKey") ){
		 musicItem->setSelectedIndex(1);
	}
	else{
		musicItem->setSelectedIndex(0);
	}

	return true;
}

void WelcomeScene::menuStartCallback(Ref *pSender)
{
	auto scene = GameScene::createScene();
	CCDirector::sharedDirector()->replaceScene(scene);
}

void WelcomeScene::menuContinueCallback(Ref *pSender)
{
	if( this->getIsCon() )	{
		CCDirector::sharedDirector()->popScene();
	}
}

void WelcomeScene::menuCloseCallback(Ref *pSender)
{
	 Director::getInstance()->end();
}

void WelcomeScene::menuMusicCallback( Ref *pSender )
{
	if ( userDefault->getBoolForKey("MusicKey") ) {                                      
        userDefault->setBoolForKey("MusicKey", false);  
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();  
    } 
	else {  
        userDefault->setBoolForKey("MusicKey", true);
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/music.ogg",true);  
    }
}

void WelcomeScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();  
	if ( userDefault->getBoolForKey("MusicKey") ) {                      
        SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/music.ogg", true);  
    } 
	
}
void WelcomeScene::cleanup()
{
	Layer::cleanup();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
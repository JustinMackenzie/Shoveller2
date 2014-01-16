#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "HelpScene.h"
#include "GameScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *background = CCSprite::create("MainMenuBackground.png");
    background->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.5f));
    this->addChild(background);
    
    CCMenuItemImage *playButton = CCMenuItemImage::create("PlayButton.png", "PlayButton.png", this, menu_selector(HelloWorld::PlayPressed));
    
    CCMenuItemImage *helpButton = CCMenuItemImage::create("HelpButton.png", "HelpButton.png", this, menu_selector(HelloWorld::HelpPressed));
    
    CCMenu *mainMenu = CCMenu::create(playButton, helpButton, NULL);
    mainMenu->alignItemsVerticallyWithPadding(screenSize.height * 0.03f);
    mainMenu->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.3f));
    
    this->addChild(mainMenu);
    
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mainMenuMusic.mp3", true);
    
    return true;
}

void HelloWorld::PlayPressed()
{
    CCDirector::sharedDirector()->replaceScene(GameScene::scene());
}

void HelloWorld::HelpPressed()
{
    CCDirector::sharedDirector()->replaceScene(HelpScene::scene());
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

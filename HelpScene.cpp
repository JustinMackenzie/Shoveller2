//
//  HelpScene.cpp
//  Shoveller2
//
//  Created by Justin Mackenzie on 13-04-09.
//
//

#include "HelpScene.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

CCScene* HelpScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelpScene *layer = HelpScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

void HelpScene::BackPressed()
{
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

// on "init" you need to initialize your instance
bool HelpScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *background = CCSprite::create("title_help.png");
    background->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.5f));
    this->addChild(background);
    
    CCMenuItemImage *backButton = CCMenuItemImage::create("back_button.png", "back_button.png", this, menu_selector(HelpScene::BackPressed));
    
    CCMenu *mainMenu = CCMenu::create(backButton, NULL);
    mainMenu->alignItemsVerticallyWithPadding(screenSize.height * 0.03f);
    mainMenu->setPosition(ccp(screenSize.width * 0.75f, screenSize.height * 0.1f));
    
    this->addChild(mainMenu);
    
    return true;
}

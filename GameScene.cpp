//
//  GameScene.cpp
//  Shoveller2
//
//  Created by Justin Mackenzie on 13-04-09.
//
//

#include "GameScene.h"
#include "HelloWorldScene.h"
#include "Character.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

void GameScene::PausePressed()
{
    _paused = true;
    CCDirector::sharedDirector()->getActionManager()->pauseAllRunningActions();
    this->addChild(createPauseLayer(), 5, 1);
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    _paused = false;
    _score = 0;
    _timeSinceAnimalSpawn = 0;
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *background = CCSprite::create("game_screen.png");
    background->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.5f));
    this->addChild(background, 0);
    
    CCMenuItemImage *pauseButton = CCMenuItemImage::create("pause_button.png", "pause_button.png", this, menu_selector(GameScene::PausePressed));
    pauseButton->setPosition(screenSize.width * 0.13f, screenSize.height * 0.9f);
    
    CCMenu *gameMenu = CCMenu::create(pauseButton, NULL);
    gameMenu->setPosition(ccp(0, 0));
    
    this->addChild(gameMenu, 10);
    
    //////////
    
    _character = CCSprite::create("left_kenny.png");
    _character->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.5f));
    this->addChild(_character, 4);
    
    _character->retain();
    
    //////////
    
    _snowTiles = CCArray::create();
    _snowTiles->retain();
    int columns = 7;
    int rows = 8;
    
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            CCSprite *snow = CCSprite::create("snow.png");
            snow->setPosition(ccp(j * 50 + 25, i * 50 + 25));
            this->addChild(snow, 3);
            _snowTiles->addObject(snow);
        }
    }
    
    ///////////
    
    _animals = CCArray::create();
    _animals->retain();
    
    _scoreLabel = CCLabelTTF::create(CCString::createWithFormat("Score : %i", _score)->getCString(), "Helvitca", 18);
    
    _scoreLabel->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.05));
    _scoreLabel->setColor(ccc3(0, 0, 255));
    this->addChild(_scoreLabel, 10);
    
    this->setTouchEnabled(true);
    
    this->scheduleUpdate();
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("liveToWin.mp3", true);
    
    return true;
}

void GameScene::QuitPressed()
{
    
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

void GameScene::ResumePressed()
{
    this->removeChildByTag(1, true);
    CCDirector::sharedDirector()->getActionManager()->resumeTarget(_character);
    
    CCObject *object;
    
    CCARRAY_FOREACH(_animals, object)
    {
        CCDirector::sharedDirector()->getActionManager()->resumeTarget(object);
    }
    
    _paused = false;
}

CCLayer* GameScene::createPauseLayer()
{
    CCLayer *pauseLayer = CCLayer::create();
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *background = CCSprite::create("pause.png");
    background->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.5f));
    pauseLayer->addChild(background);
    
    CCMenuItemImage *resumeButton = CCMenuItemImage::create("resume_button.png", "resume_button.png", this, menu_selector(GameScene::ResumePressed));
    CCMenuItemImage *quitButton = CCMenuItemImage::create("quit_button.png", "quit_button.png", this, menu_selector(GameScene::QuitPressed));
    
    CCMenu *mainMenu = CCMenu::create(resumeButton, quitButton, NULL);
    mainMenu->alignItemsVerticallyWithPadding(screenSize.height * 0.03f);
    mainMenu->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.5f));
    
    pauseLayer->addChild(mainMenu);
    
    return pauseLayer;
}

void GameScene::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    if(_paused)
    {
        return;
    }
    
    CCTouch* touch = (CCTouch*)( touches->anyObject() );
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    float dx = _character->getPosition().x - location.x;
    
    if(dx < 0)
    {
        _character->setTexture(CCTextureCache::sharedTextureCache()->addImage("right_kenny.png"));
    }
    else
    {
        _character->setTexture(CCTextureCache::sharedTextureCache()->addImage("left_kenny.png"));
    }
    
    _character->runAction(CCSequence::create(CCMoveTo::create(2.0, location), NULL));
    
    
}

void GameScene::update(float dt)
{
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    
    if(_paused)
    {
        return;
    }
    
    if(_character->getPosition().x < 0)
    {
        _character->setPosition(ccp(0, _character->getPosition().y));
    }
    else if(_character->getPosition().x > screenSize.width)
    {
        _character->setPosition(ccp(screenSize.width, _character->getPosition().y));
    }
    
    if(_character->getPosition().y < 0)
    {
        _character->setPosition(ccp(_character->getPosition().x, 0));
    }
    else if(_character->getPosition().y > screenSize.height * 0.81f)
    {
        _character->setPosition(ccp(_character->getPosition().x, screenSize.height * 0.81f));
    }
    
    CCRect characterBoundingBox = CCRectMake(_character->getPosition().x - _character->getContentSize().width * 0.5f, _character->getPosition().y - _character->getContentSize().height * 0.5f, _character->getContentSize().width, _character->getContentSize().height);
    
    CCObject *object;
    CCObject *objectToDelete;
    CCArray *objectsToDelete = CCArray::create();
    
    CCARRAY_FOREACH(_snowTiles, object)
    {
        CCSprite *snow = dynamic_cast<CCSprite *>(object);
        
        CCRect snowBoundingBox = CCRectMake(snow->getPosition().x - snow->getContentSize().width * 0.5f, snow->getPosition().y - snow->getContentSize().height * 0.5f, snow->getContentSize().width, snow->getContentSize().height);
        
        if(characterBoundingBox.intersectsRect(snowBoundingBox))
        {
            objectsToDelete->addObject(snow);
            _score += 500;
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("slide-1.mp3");
        }
    }
    
    CCARRAY_FOREACH(objectsToDelete, objectToDelete)
    {
        CCSprite *sprite = dynamic_cast<CCSprite *>(objectToDelete);
        
        _snowTiles->removeObject(sprite);
        this->removeChild(sprite, true);
    }
    
    if(_snowTiles->count() <= 0)
    {
        GameOver();
    }
    
    object = NULL;
    objectsToDelete->removeAllObjects();
    
    CCARRAY_FOREACH(_animals, object)
    {
        CCSprite *animal = dynamic_cast<CCSprite *>(object);
        
        CCRect animalBoundingBox = CCRectMake(animal->getPosition().x - animal->getContentSize().width * 0.5f, animal->getPosition().y - animal->getContentSize().height * 0.5f, animal->getContentSize().width, animal->getContentSize().height);
        
        if(characterBoundingBox.intersectsRect(animalBoundingBox))
        {
            objectsToDelete->addObject(animal);
            _score -= 500;
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("squirrell.mp3");
        }
    }
    
    CCARRAY_FOREACH(objectsToDelete, objectToDelete)
    {
        CCSprite *sprite = dynamic_cast<CCSprite *>(objectToDelete);
        
        _animals->removeObject(sprite);
        this->removeChild(sprite, true);
    }
    
    _timeSinceAnimalSpawn += dt;
    SpawnAnimals();
    objectsToDelete->removeAllObjects();
    
    _scoreLabel->setString(CCString::createWithFormat("Score : %i", _score)->getCString());
}

void GameScene::GameOver()
{
    CCDirector::sharedDirector()->getActionManager()->pauseAllRunningActions();
    this->addChild(createGameOverLayer(), 12);
}

CCLayer* GameScene::createGameOverLayer()
{
    CCLayer *gameOverLayer = CCLayer::create();
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *background = CCSprite::create("game_over.png");
    background->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.5f));
    gameOverLayer->addChild(background);
    
    CCMenuItemImage *tryAgainButton = CCMenuItemImage::create("try_button.png", "try_button.png", this, menu_selector(GameScene::TryAgainPressed));
    
    CCMenuItemImage *mainMenuButton = CCMenuItemImage::create("gameover_button.png", "gameover_button.png", this, menu_selector(GameScene::QuitPressed));
    
    CCMenu *mainMenu = CCMenu::create(tryAgainButton, mainMenuButton, NULL);
    mainMenu->alignItemsVerticallyWithPadding(screenSize.height * 0.03f);
    mainMenu->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.3f));
    
    CCLabelTTF *scoreLabel = CCLabelTTF::create(CCString::createWithFormat("Score : %i", _score)->getCString(), "Helvetica", 18);
    
    scoreLabel->setPosition(ccp(screenSize.width * 0.5f, screenSize.height * 0.5f));
    scoreLabel->setColor(ccc3(0, 0, 0));
    gameOverLayer->addChild(scoreLabel);
    
    gameOverLayer->addChild(mainMenu);
    
    return gameOverLayer;
}

void GameScene::TryAgainPressed()
{
    CCDirector::sharedDirector()->replaceScene(GameScene::scene());
}

void GameScene::SpawnAnimals()
{
    float prob = (_timeSinceAnimalSpawn * 20) / (_animals->count());
    int r = rand() % 100 + 1;
    
    if (r < prob)
    {
        CCSprite *animal;
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        r = rand() % 2;
        if(r == 0)
        {
            animal = CCSprite::create("right_chipmunk.png");
            animal->setPosition(ccp(0, rand() % (int)(screenSize.height * 0.5f) + screenSize.height * 0.3f));
            
            animal->runAction(CCMoveTo::create(2.0f, ccp(screenSize.width + animal->getContentSize().width * 0.5f, rand() % (int)(screenSize.height * 0.5f) + screenSize.height * 0.3f)));
        }
        else
        {
            animal = CCSprite::create("left_chipmunk.png");
            animal->setPosition(ccp(screenSize.width, rand() % (int)(screenSize.height * 0.5f) + screenSize.height * 0.3f));
            animal->runAction(CCMoveTo::create(2.0f, ccp(0 - animal->getContentSize().width * 0.5f, rand() % (int)(screenSize.height * 0.5f) + screenSize.height * 0.3f)));
        }
        
        _animals->addObject(animal);
        this->addChild(animal, 5);
        _timeSinceAnimalSpawn = 0;
    }
}

GameScene::~GameScene()
{
    if(_snowTiles)
    {
        _snowTiles->release();
        _snowTiles = NULL;
    }
    if(_character)
    {
        _character->release();
        _character = NULL;
    }
    if(_animals)
    {
        _animals->release();
        _animals = NULL;
    }
}



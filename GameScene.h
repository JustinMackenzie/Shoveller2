//
//  GameScene.h
//  Shoveller2
//
//  Created by Justin Mackenzie on 13-04-09.
//
//

#ifndef __Shoveller2__GameScene__
#define __Shoveller2__GameScene__

#include <iostream>
#include "cocos2d.h"

class Character;

class GameScene : public cocos2d::CCLayer
{
    bool _paused;
    int _score;
    float _timeSinceAnimalSpawn;
    
    cocos2d::CCSprite *_character;
    
    cocos2d::CCArray *_snowTiles;
    cocos2d::CCArray *_animals;
    cocos2d::CCLabelTTF *_scoreLabel;
    
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    void PausePressed();
    void QuitPressed();
    void ResumePressed();
    void GameOver();
    void SpawnAnimals();
    void TryAgainPressed();
    
    void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
    void update(float dt);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameScene);
    
    cocos2d::CCLayer *createPauseLayer();
    cocos2d::CCLayer *createGameOverLayer();
    
    ~GameScene();
};

#endif /* defined(__Shoveller2__GameScene__) */

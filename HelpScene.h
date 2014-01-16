//
//  HelpScene.h
//  Shoveller2
//
//  Created by Justin Mackenzie on 13-04-09.
//
//

#ifndef __Shoveller2__HelpScene__
#define __Shoveller2__HelpScene__

#include <iostream>
#include "cocos2d.h"

class HelpScene : public cocos2d::CCLayer
{
    
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    void BackPressed();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelpScene);
};

#endif /* defined(__Shoveller2__HelpScene__) */

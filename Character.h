/*
 * Character.h
 *
 *  Created on: 9 avr. 2013
 *      Author: TimHP
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "CCSprite.h"

using namespace cocos2d;

class Character : public CCSprite
{

	//Functions
	public:
    static Character* create();
	//void onCollision();
	//void move(CCPoint position);
	//void useWeapon(Weapon w);
    
    void update(float dt);

	//Attributes
	private:
	//Weapon w;

};

#endif /* CHARACTER_H_ */

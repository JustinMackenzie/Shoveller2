//============================================================================
// Name        : Character.cpp
// Author      : Tim
// Version     :
// Description : Character class
//============================================================================

#include "Character.h"

using namespace std;

Character::Character(const char* image)
{
    
}

bool Character::init()
{
    
}

void Character::onCollision(){

}

void Character::move(CCPoint position){

}

/*void Character::useWeapon(Weapon w){

}*/

bool Character::isAlive(){
	return (health>0);
}



#ifndef FIREWORK_H
#define FIREWORK_H
#include"Enemy.h"

//Probably one of the most lazy classes ever created.
//Used to show the explosion animation of a dead enemy
//Because fireworks without sacrifice would be boring
class Firework : public Enemy
{
private:

public:
	Firework(Texture* fireworkTexture);
	virtual ~Firework();

	Firework* clone() const;

	virtual void updateMoreSpecific(float dt, BulletContainer& bc);

};


#endif
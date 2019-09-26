#ifndef SPEEDER_H
#define SPEEDER_H
#include"Enemy.h"

//A faster enemy. Likes
//to stay at the top of the
//screen
class Speeder : public Enemy
{
private:
	int firingTime;
	int firingCounter;
	int fireCooldown;
	int fireCooldownCounter;
	int directionCounter;
	int shotsFired;
public:
	Speeder(Texture* texture, Texture* expl, Texture* healthbar, Texture* background);
	virtual ~Speeder();

	Speeder* clone() const;
	void updateMoreSpecific(float dt, BulletContainer& bc);
};
#endif
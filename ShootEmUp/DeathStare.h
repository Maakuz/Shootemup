#ifndef DEATHSTARE_H
#define DEATHSTARE_H
#include"Enemy.h"
#include<cmath>

//The first (and probably only) boss
class DeathStare : public Enemy
{
private:
	int directionCounter;
	bool isShooting;
	int shotCounter;
	int shotXPos;
	int shotYPos;
	int patternCounter;
	int cooldown;
	int whatPattern;

	//Used for the recursive function that I made because I could.
	int nrOfShots;
	float shotSlowing;
	
	void pattern2Shoot(BulletContainer& bc, int times);

	void shootPattern1(float dt, BulletContainer& bc);
	void shootPattern2(float dt, BulletContainer& bc);
	void shootPattern3(float dt, BulletContainer& bc);
public:
	DeathStare(Texture* texture, Texture* explTexture, Texture* healthbar, Texture* background);
	virtual ~DeathStare();


	DeathStare* clone() const;

	void updateMoreSpecific(float dt, BulletContainer& bc);
};

#endif
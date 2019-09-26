#ifndef FIGHTER_H
#define FIGHTER_H
#include"Enemy.h"

//The standardest of enemies.
//It sets the standard
class Fighter : public Enemy
{
private:

public:
	Fighter(Texture* texture, Texture* expl, Texture* healthbar, Texture* background);
	virtual ~Fighter();

	Fighter* clone() const;
	virtual void updateMoreSpecific(float dt, BulletContainer& bc);

};

#endif
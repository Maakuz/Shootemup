#ifndef BOMBER_H
#define BOMBER_H
#include "Enemy.h"

//A heavier unit that shoots 2 bullets in an arc
class Bomber : public Enemy
{
private:

public:
	Bomber(Texture* texture, Texture* expl, Texture* healthbar, Texture* background);
	virtual ~Bomber();

	Bomber* clone() const;
	virtual void updateMoreSpecific(float dt, BulletContainer& bc);
};

#endif
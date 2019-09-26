#ifndef STDBULLET_H
#define STDBULLET_H
#include"Bullet.h"

//The most standard of bullets
class StandardBullet : public Bullet
{
private:

public:
	StandardBullet(bool isFriendly, int damage, Texture* texture);
	virtual ~StandardBullet();

	StandardBullet* clone() const;

	void updateSpecific(float dt);
};


#endif
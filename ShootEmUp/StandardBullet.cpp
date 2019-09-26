#include "standardBullet.h"

StandardBullet::StandardBullet(bool isFriendly, int damage, Texture* texture)
	:Bullet(isFriendly, damage, texture)
{
	setFrameSize(32, 32);
	setSheetSize(2, 1);
}

StandardBullet::~StandardBullet()
{
}

StandardBullet* StandardBullet::clone() const
{
	return new StandardBullet(*this);
}

void StandardBullet::updateSpecific(float dt)
{
}

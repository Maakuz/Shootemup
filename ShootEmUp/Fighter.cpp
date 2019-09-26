#include"Fighter.h"

Fighter::Fighter(Texture* texture, Texture* expl, Texture* healthbar, Texture* background)
	:Enemy(texture, expl)
{
	setAttackSpeed(4000);
	setMaxHealth(30);
	setDamage(50);
	setValue(50);
	setIsFriendly(false);
	setFrameSize(40, 57);
	setSheetSize(4, 1);
	setRect(36, 50, 2, 0);
	setAcceleration(0, 0.04);
	setDecceleration(0, 0);
	setIsAnimating(true);
	initializeHealthBar(healthbar, background);
}

Fighter::~Fighter()
{
	
}

Fighter* Fighter::clone() const
{
	return new Fighter(*this);
}

void Fighter::updateMoreSpecific(float dt, BulletContainer& bc)
{
	if (getAttackCounter() >= getAttackSpeed())
	{
		shoot(bc, Vector2f(0, 3), 0, 20);
	}
}

#include"Bomber.h"

Bomber::Bomber(Texture* texture, Texture* expl, Texture* healthbar, Texture* background)
	:Enemy(texture, expl)
{
	setAttackSpeed(7000);
	setMaxHealth(100);
	setDamage(100);
	setValue(200);
	setIsFriendly(false);
	setFrameSize(94, 100);
	setSheetSize(4, 1);
	setRect(94, 100, 0, 0);
	setAcceleration(0, 0.025);
	setDecceleration(0, 0);
	setIsAnimating(true);
	initializeHealthBar(healthbar, background);
}

Bomber::~Bomber()
{}

Bomber* Bomber::clone() const
{
	return new Bomber(*this);
}

void Bomber::updateMoreSpecific(float dt, BulletContainer& bc)
{
	if (getAttackCounter() >= getAttackSpeed())
	{
		shoot(bc, Vector2f(1, 3), 0, 20);
		shoot(bc, Vector2f(-1, 3), 0, 20);
	}
}
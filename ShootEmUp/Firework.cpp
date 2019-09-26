#include "Firework.h"

Firework::Firework(Texture* fireworkTexture)
	:Enemy(fireworkTexture, fireworkTexture)
{
	setAcceleration(0, 0);
	setIsAnimating(true);
	initializeHealthBar(fireworkTexture, fireworkTexture);
	setIsDying(true);
	setExplAnimSpeed(25);
	
}

Firework::~Firework()
{
}

Firework* Firework::clone() const
{
	return new Firework(*this);
}

void Firework::updateMoreSpecific(float dt, BulletContainer & bc)
{
	//Maybe I'll find a use for this...
}

#include"Speeder.h"

Speeder::Speeder(Texture * texture, Texture * expl, Texture * healthbar, Texture * background)
	:Enemy(texture, expl)
{
	setAttackSpeed(10000);
	setMaxHealth(50);
	setDamage(10);
	setValue(500);
	setIsFriendly(false);
	setFrameSize(94, 57);
	setSheetSize(4, 1);
	setRect(90, 30, 2, 8);
	setAcceleration(0, 0.15);
	setDecceleration(0, 0);
	setIsAnimating(true);
	initializeHealthBar(healthbar, background);

	this->firingTime = 100;
	this->firingCounter = 0;
	this->fireCooldown = 2000;
	this->fireCooldownCounter = 2000;
	this->directionCounter = 0;
	this->shotsFired = 0;
}

Speeder::~Speeder()
{
}

Speeder* Speeder::clone() const
{
	return new Speeder(*this);
}

void Speeder::updateMoreSpecific(float dt, BulletContainer& bc)
{
	if (getPos().y > 70)
	{	
		this->directionCounter += dt;
		if (this->directionCounter >= 600)
		{
			if (rand() % 100 < 50)
				setAcceleration(0.15, 0);

			else
				setAcceleration(-0.15, 0);

			this->directionCounter = 0;
		}

		this->fireCooldownCounter += dt;
		if (this->fireCooldown <= this->fireCooldownCounter)
		{
			setAcceleration(0, 0);
			this->firingCounter += dt;
			if (this->firingCounter >= this->firingTime)
			{
				this->firingCounter = 0;
				this->fireCooldownCounter = 0;
				this->shotsFired = 0;
			}

			if (this->firingCounter > this->shotsFired * 20)
			{
				shoot(bc, Vector2f((-5 + this->shotsFired++ * 2), 2), 0, 20);
			}

		}
	}

	if (getPos().x < 0)
		setPos(0, getPos().y);

	if (getPos().x > 1280 - getFrameSize().x)
		setPos(1280 - getFrameSize().x, getPos().y);
}
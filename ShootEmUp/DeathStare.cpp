#include "DeathStare.h"

DeathStare::DeathStare(Texture* texture, Texture* explTexture, Texture* healthbar, Texture* background)
	:Enemy(texture, explTexture)
{
	setAttackSpeed(4000);
	setMaxHealth(30000);
	setDamage(30);
	setValue(5000);
	setIsFriendly(false);
	setFrameSize(216, 217);
	setSheetSize(1, 1);
	setRect(200, 200, 8, 2);
	setAcceleration(0, 0.04);
	setDecceleration(0, 0);
	setIsAnimating(false);
	initializeHealthBar(healthbar, background);

	this->directionCounter = 600;
	this->isShooting = false;
	this->shotCounter = 0;

	this->shotXPos = 0;
	this->shotYPos = 120;

	this->patternCounter = 0;

	this->cooldown = 0;
	this->whatPattern = 0;
	this->nrOfShots = 0;
	this->shotSlowing = 0;
}

DeathStare::~DeathStare()
{
}

void DeathStare::pattern2Shoot(BulletContainer& bc, int times)
{

	if (times > 1)
	{
		pattern2Shoot(bc, times - 1);
		shoot(bc, Vector2f((-times + 1) * this->shotSlowing, (this->nrOfShots - times) * this->shotSlowing), -70, 0);
		shoot(bc, Vector2f((times - 1) * this->shotSlowing, (this->nrOfShots - times) * this->shotSlowing), 70, 0);
	}

}

void DeathStare::shootPattern1(float dt, BulletContainer& bc)
{
	setAcceleration(0, 0);

	this->patternCounter += dt;
	if (this->patternCounter >= 40)
	{
		this->patternCounter = 0;
		shoot(bc, Vector2f(((this->shotCounter % 21) - 10) / 2.0, 5 - (abs((this->shotCounter % 21) - 10) / 2.0)), 0, 0, Vector2f(0.997, 0.997));
		this->shotCounter += 2;

		if (this->shotCounter >= 294)
		{
			this->isShooting = false;
			this->cooldown = -1500;
			this->shotCounter = 0;
		}
	}
	
}

void DeathStare::shootPattern2(float dt, BulletContainer& bc)
{
	this->patternCounter += dt;

	if (this->patternCounter >= 150)
	{
		this->patternCounter = 0;
		this->shotCounter++;

		if (this->nrOfShots < 25 && this->shotCounter < 25)
		{
			this->nrOfShots++;
			this->shotSlowing = 3.0 / this->nrOfShots;
		}

		if (this->shotCounter >= 25)
		{
			this->nrOfShots--;
			this->shotSlowing = 3.0 / this->nrOfShots;
		}

		pattern2Shoot(bc, this->nrOfShots);

		//Exit
		if (this->shotCounter >= 50 && this->nrOfShots <= 0)
		{
			this->isShooting = false;
			this->cooldown = -500;
			this->shotCounter = 0;
			this->nrOfShots = 0;
		}

	}
}

void DeathStare::shootPattern3(float dt, BulletContainer& bc)
{
	setAcceleration(0, 0);

	this->patternCounter += dt;
	if (this->patternCounter >= 40)
	{
		this->patternCounter = 0;
		shoot(bc, Vector2f(0, 10), 40, 0);
		shoot(bc, Vector2f(0, 10), -40, 0);
		this->shotCounter++;

		if (this->shotCounter >= 50)
		{
			this->isShooting = false;
			this->cooldown = 0;
			this->shotCounter = 0;
		}
	}
}

DeathStare* DeathStare::clone() const
{
	return new DeathStare(*this);
}

void DeathStare::updateMoreSpecific(float dt, BulletContainer& bc)
{
	if (getPos().y >= 0)
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

		this->cooldown += dt;
		if (this->cooldown >= 1000 && !this->isShooting)
		{
			this->isShooting = true;

			//A chance it does not shoot at all
			this->whatPattern = rand() % 4 + 1;
		}

		if (this->isShooting)
		{ 
			switch (this->whatPattern)
			{
			case 1:
				shootPattern1(dt, bc);
				break;

			case 2:
				shootPattern2(dt, bc);
				break;

			case 3:
				shootPattern3(dt, bc);
				break;

			default:
				this->isShooting = false;
				this->cooldown = 0;
				break;
			}
		}
	}

	if (getPos().x < 0)
		setPos(0, getPos().y);

	if (getPos().x > 1280 - getFrameSize().x)
		setPos(1280 - getFrameSize().x, getPos().y);
}

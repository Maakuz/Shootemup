#include"Character.h"

Character::Character(Texture* texture, Texture* expl)
{
	this->texture = texture;
	this->explTexture = expl;
	this->sprite.setTexture(*texture);
	this->explSprite.setTexture(*expl);

	this->explSprite.setOrigin(128, 128);

	this->isAnimated = false;
	this->currentFrame = Vector2i(0, 0);
	this->animCounter = 0;
	this->animSpeed = 100;

	this->currentExpFrame = Vector2i(0, 0);
	this->frameExpSize = Vector2i(256, 256);
	this->sheetExpSize = Vector2i(8, 6);
	this->animExpSpeed = 10;

	this->speed = Vector2f(0, 0);
	this->acceleration = Vector2f(0, 0);
	this->deceleration = Vector2f(0, 0);

	this->attackSpeed = 100;
	this->attackCounter = this->attackSpeed;
	this->isFriendly = false;
	this->isAlive = true;
	this->explodingStarted = false;
}

Character::~Character()
{}

void Character::animate(float dt)
{
	this->animCounter += dt;
	if (this->animCounter >= this->animSpeed)
	{
		this->currentFrame.x++;
		this->animCounter = 0;
	}

	if (this->currentFrame.x == this->sheetSize.x)
	{
		this->currentFrame.x = 0;
		this->currentFrame.y++;
		if (this->currentFrame.y == this->sheetSize.y)
		{
			this->currentFrame.y = 0;
		}
	}
	this->sprite.setTextureRect(IntRect(currentFrame.x * frameSize.x, currentFrame.y * frameSize.y, frameSize.x, frameSize.y));
}

void Character::animateExp(float dt)
{
	this->animCounter += dt;
	if (this->animCounter >= this->animExpSpeed)
	{
		this->currentExpFrame.x++;
		this->animCounter = 0;
	}

	if (this->currentExpFrame.x == this->sheetExpSize.x)
	{
		this->currentExpFrame.x = 0;
		this->currentExpFrame.y++;
		if (this->currentExpFrame.y == this->sheetExpSize.y)
		{
			this->currentExpFrame.y = 0;
		}
	}
	this->explSprite.setTextureRect(IntRect(currentExpFrame.x * frameExpSize.x, currentExpFrame.y * frameExpSize.y, frameExpSize.x, frameExpSize.y));
}

void Character::move(float dt)
{
	this->sprite.move(this->speed);
	this->speed.x *= this->deceleration.x;
	this->speed.y *= this->deceleration.y;
}

void Character::initialize(float x, float y)
{
	this->sprite.setPosition(x, y);
	this->health = this->maxHealth;
	this->isAlive = true;
	this->isDying = false;
	this->explodingStarted = false;
	this->collisionRect.setFriendly(this->isFriendly);
	this->healthBar.setHealthBar(this->maxHealth, this->health);
}

void Character::initializeHealthBar(Texture* healthbar, Texture* background)
{
	this->healthBar.setTextures(background, healthbar);
	this->healthBar.setOffset(this->frameSize.x / 2 - background->getSize().x / 2, this->frameSize.y + 5);
}

void Character::explode(float dt)
{
	if (!this->explodingStarted)
	{
		this->isDying = true;
		this->explodingStarted = true;
		this->animCounter = 0;
		this->explSprite.setPosition(this->sprite.getPosition().x + (this->frameSize.x / 2), this->sprite.getPosition().y + (this->frameSize.y / 2));
		this->explSprite.setRotation(rand() % 360);
	}

	animateExp(dt);

	if (currentExpFrame.y == 5 && currentExpFrame.x == 7)
		this->isAlive = false;
}

bool Character::checkCollision(BulletContainer& bc)
{
	bool collided = false;

	for (int i = 0; i < bc.getNrOfBullets(); i++)
	{
		if (bc.checkCollision(this->collisionRect, i))
		{
			this->health -= bc[i]->getDamage();
			bc.removeBullet(i);
			updateHealthBar();
			collided = true;
		}
	}

	return collided;
}

void Character::shoot(BulletContainer& bc, Vector2f accel, float x, float y, Vector2f deccel)
{
	Vector2f startPos = Vector2f(this->sprite.getPosition().x + (this->frameSize.x / 2) + x, this->sprite.getPosition().y + (this->frameSize.y / 2) + y);

	bc.addBullet(startPos, accel, this->isFriendly, this->damage, deccel);
	this->attackCounter = 0;

}

//Kanske inte hinner detta...
//void Character::shootBeam(BulletContainer& bc, Vector2f accel, int duration)
//{
//	Vector2f startPos = Vector2f(this->sprite.getPosition().x + (this->frameSize.x / 2), this->sprite.getPosition().y - 5);
//
//	if (!isFriendly)
//		startPos = Vector2f(this->sprite.getPosition().x + (this->frameSize.x / 2), this->sprite.getPosition().y + this->frameSize.y - 3);
//
//	bc.addBeam(startPos, accel, this->isFriendly, duration);
//	attackCounter = 0;
//}

void Character::update(float dt, BulletContainer& bc, AudioHandler& ah)
{
	if (!this->isDying)
	{
		if (this->isAnimated)
			animate(dt);

		this->collisionRect.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y);

		this->attackCounter += dt;

		if (checkCollision(bc) && this->isFriendly)
		{
			ah.playHitSound();
		}

		updateSpecific(dt, bc, ah);

		move(dt);
	}
	if (this->health <= 0)
		explode(dt);


}

void Character::draw(RenderWindow &window)
{
	if (!explodingStarted)
	{
		if (this->health != this->maxHealth && !this->isFriendly)
			this->healthBar.draw(window);

		else if (this->isFriendly)
			this->healthBar.draw(window);

		window.draw(this->sprite);
	}

	else
		window.draw(this->explSprite);
}

void Character::drawHitBox(RenderWindow & window)
{
	this->collisionRect.draw(window);
}

void Character::setIsAnimating(bool value)
{
	this->isAnimated = value;
}

void Character::setCurrentFrame(int x, int y)
{
	this->currentFrame = Vector2i(x, y);
}

void Character::setFrameSize(int x, int y)
{
	this->frameSize = Vector2i(x, y);
}

Vector2i Character::getFrameSize() const
{
	return this->frameSize;
}

void Character::setSheetSize(int x, int y)
{
	this->sheetSize = Vector2i(x, y);
}

void Character::setRect(int width, int heigth, int xOffset, int yOffset)
{
	this->collisionRect.setSize(width, heigth);
	this->collisionRect.setOffset(xOffset, yOffset);
}

HitBox Character::getRect() const
{
	return this->collisionRect;
}

void Character::setIsFriendly(bool value)
{
	this->isFriendly = value;
}

bool Character::getFriendly() const
{
	return this->isFriendly;
}

void Character::setIsAlive(bool value)
{
	this->isAlive = value;
}

bool Character::getIsAlive() const
{
	return this->isAlive;
}

void Character::setIsDying(bool value)
{
	this->isDying = value;
}

bool Character::getIsDying() const
{
	return this->isDying;
}

float Character::getAttackCounter() const
{
	return this->attackCounter;
}

void Character::setAttackSpeed(float value)
{
	this->attackSpeed = value;
}

float Character::getAttackSpeed() const
{
	return this->attackSpeed;
}

void Character::setDamage(int value)
{
	this->damage = value;
}

int Character::getDamage() const
{
	return this->damage;
}

void Character::setMaxHealth(int value)
{
	this->maxHealth = value;
}

int Character::getMaxHealth() const
{
	return this->maxHealth;
}

void Character::setHealth(int value)
{
	this->health = value;
}

int Character::getHealth() const
{
	return this->health;
}

void Character::setAnimationSpeed(float value)
{
	this->animSpeed = value;
}

void Character::setExplAnimSpeed(float value)
{
	this->animExpSpeed = value;
}

void Character::setAcceleration(float x, float y)
{
	this->acceleration = Vector2f(x, y);
}

Vector2f Character::getAcceleration() const
{
	return this->acceleration;
}

void Character::setDecceleration(float x, float y)
{
	this->deceleration = Vector2f(x, y);
}

void Character::setXSpeed(float x)
{
	this->speed.x = x;
}

void Character::setYSpeed( float y)
{
	this->speed.y = y;
}

Vector2f Character::getSpeed() const
{
	return this->speed;
}

void Character::setHealthBarScale(float x, float y)
{
	this->healthBar.setScale(x, y);
}

void Character::setHealthBarPos()
{
	healthBar.setPosOnChar(this->sprite.getPosition().x, this->sprite.getPosition().y);
}

void Character::setHealthBarPos(float x, float y)
{
	this->healthBar.setPosition(x, y);
}

void Character::setPos(float x, float y)
{
	this->sprite.setPosition(x, y);
}

Vector2f Character::getPos() const
{
	return this->sprite.getPosition();
}

void Character::updateHealthBar()
{
	this->healthBar.setHealthBar(this->maxHealth, this->health);
}
#include"Bullet.h"

Bullet::Bullet(const bool isFriendly, int damage, Texture* texture)
{
	this->isFriendly = isFriendly;
	this->texture = texture;
	this->sprite.setTexture(*texture);
	this->damage = damage;
	
	this->animCounter = 0;
	this->animSpeed = 200;

	this->decayTimer = 0;
	this->isDecayed = false;
}

Bullet::Bullet()
{
	this->isFriendly = false;
	this->texture = nullptr;
	this->damage = -1;

	this->animCounter = -1;
	this->animSpeed = -1;

	this->decayTimer = -1;
	this->isDecayed = false;
}

Bullet::~Bullet()
{}

void Bullet::animate(float dt)
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
}

void Bullet::initialize(Vector2f accel, Vector2f deccel, Vector2f pos)
{
	accel.x /= 10;
	accel.y /= 10;
	this->acceleration = accel;
	this->decceleration = deccel;

	if (this->isFriendly)
		this->acceleration = Vector2f(this->acceleration.x, this->acceleration.y * -1);
	
	this->sprite.setPosition(pos.x - (this->frameSize.x / 2), pos.y);

	this->rect = HitBox(this->frameSize, pos, this->isFriendly);
}

void Bullet::update(float dt)
{
	this->speed = this->acceleration * dt;
	this->acceleration.x *= this->decceleration.x;
	this->acceleration.y *= this->decceleration.y;

	sprite.move(speed);

	updateSpecific(dt);

	animate(dt);

	this->decayTimer += dt;
	if (this->decayTimer >= 5000)
		this->isDecayed = true;

	this->sprite.setTextureRect(IntRect(currentFrame.x * frameSize.x, currentFrame.y * frameSize.y, frameSize.x, frameSize.y));
	this->rect.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y);
}

void Bullet::draw(RenderWindow& window)
{
	window.draw(this->sprite);
}

void Bullet::drawHitBox(RenderWindow& window)
{
	this->rect.draw(window);
}

void Bullet::setFrameSize(int x, int y)
{
	this->frameSize = Vector2i(x, y);
}

Vector2i Bullet::getFrameSize() const
{
	return this->frameSize;
}

void Bullet::setSheetSize(int x, int y)
{
	this->sheetSize = Vector2i(x, y);
}

Vector2i Bullet::getSheetSize() const
{
	return this->sheetSize;
}

Vector2i Bullet::getCurrentFrame() const
{
	return this->currentFrame;
}

Vector2f Bullet::getPos() const
{
	return this->sprite.getPosition();
}

bool Bullet::getDecayed() const
{
	return this->isDecayed;
}

void Bullet::setDamage(int value)
{
	this->damage = value;
}

int Bullet::getDamage() const
{
	return this->damage;
}

void Bullet::setRect(int width, int heigth, int xOffset, int yOffset)
{
	this->rect.setSize(width, heigth);
	this->rect.setOffset(xOffset, yOffset);
}

HitBox Bullet::getRect() const
{
	return this->rect;
}

void Bullet::setFriendly(bool value)
{
	this->isFriendly = value;
}

bool Bullet::getFriendly() const
{
	return this->isFriendly;
}


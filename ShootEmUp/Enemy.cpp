#include"Enemy.h"

Enemy::Enemy(Texture* texture, Texture* expl)
	:Character(texture, expl)
{}

Enemy::~Enemy()
{}

void Enemy::setValue(int value)
{
	this->value = value;
}

int Enemy::getValue() const
{
	return this->value;
}

void Enemy::updateSpecific(float dt, BulletContainer& bc, AudioHandler& ah)
{
	setYSpeed(getAcceleration().y * dt);
	setXSpeed(getAcceleration().x * dt);
	
	if (getHealth() != getMaxHealth())
		setHealthBarPos();

	updateMoreSpecific(dt, bc);
}
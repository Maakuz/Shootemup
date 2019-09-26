#include"Player.h"

Player::Player(Texture* texture, Texture* expl, Texture* healthbar, Texture* background)
	:Character(texture, expl)
{
	setIsFriendly(true);
	setAttackSpeed(500);
	setDamage(20);
	setMaxHealth(100);
	setFrameSize(54, 90);
	setSheetSize(4, 1);
	setRect(40, 55, 7, 25);
	setAcceleration(0.07, 0.07);
	setDecceleration(0.85, 0.85);
	setIsAnimating(true);
	initializeHealthBar(healthbar, background);
	setHealthBarScale(3, 2);
	setHealthBarPos(0, 700);
}

Player::~Player()
{}

void Player::handleInputs(float dt, BulletContainer& bc, AudioHandler& ah)
{
	if (Keyboard::isKeyPressed(Keyboard::D))
		setXSpeed(getSpeed().x + getAcceleration().x * dt);

	if (Keyboard::isKeyPressed(Keyboard::A))
		setXSpeed(getSpeed().x - getAcceleration().x * dt);

	if (Keyboard::isKeyPressed(Keyboard::W))
		setYSpeed(getSpeed().y - getAcceleration().y * dt);

	if (Keyboard::isKeyPressed(Keyboard::S))
		setYSpeed(getSpeed().y + getAcceleration().y * dt);

	if (Keyboard::isKeyPressed(Keyboard::Space) && getAttackCounter() >= getAttackSpeed())
	{
		ah.playShootSound();
		shoot(bc, Vector2f(getSpeed().x - (getSpeed().x / 2), 5), 0, -70);
	}
}

void Player::keepOnScreen()
{
	if (getPos().x < 0)
		setPos(0, getPos().y);

	if (getPos().x > 1280 - getFrameSize().x)
		setPos(1280 - getFrameSize().x, getPos().y);

	if (getPos().y < 0)
		setPos(getPos().x, 0);

	if (getPos().y > 720 - getFrameSize().y)
		setPos(getPos().x, 720 - getFrameSize().y);
}

void Player::updateSpecific(float dt, BulletContainer& bc, AudioHandler& ah)
{	
	handleInputs(dt, bc, ah);

	keepOnScreen();
}
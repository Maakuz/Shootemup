#include"HealthBar.h"

HealthBar::HealthBar(Texture* background, Texture* healthBar)
{
	this->healthTexture = healthBar;
	this->backgroundTexture = background;
	this->offset = Vector2f((background->getSize().x / 2) - (background->getSize().x / 2), background->getSize().x);

	this->background.setTexture(*backgroundTexture);
	this->health.setTexture(*healthTexture);

	this->scaleXIncrease = 1;
	this->scaleYIncrease = 1;
}

HealthBar::HealthBar()
{
	this->healthTexture = nullptr;
	this->healthTexture = nullptr;

	this->offset = Vector2f(-1, -1);
	this->scaleXIncrease = 1;
	this->scaleYIncrease = 1;
}

HealthBar::~HealthBar()
{}

void HealthBar::draw(RenderWindow& window)
{
	window.draw(this->background);
	window.draw(this->health);
}

void HealthBar::setTextures(Texture* background, Texture* health)
{
	this->healthTexture = health;
	this->backgroundTexture = background;
	this->offset = Vector2f((background->getSize().x / 2) - (background->getSize().x / 2), background->getSize().x + 10);

	this->background.setTexture(*backgroundTexture);
	this->health.setTexture(*healthTexture);
}

void HealthBar::setOffset(float x, float y)
{
	this->offset = Vector2f(x, y);
}

void HealthBar::setPosOnChar(float x, float y)
{
	this->background.setPosition(x + this->offset.x, y + this->offset.y);
	this->health.setPosition(x + this->offset.x + this->scaleXIncrease, y + this->offset.y + this->scaleYIncrease);
}

void HealthBar::setPosition(float x, float y)
{
	this->background.setPosition(x, y);
	this->health.setPosition(x + this->scaleXIncrease, y + this->scaleYIncrease);
}

void HealthBar::setHealthBar(int maxHealth, int currentHealth)
{
	double percentage = currentHealth / static_cast<double>(maxHealth);

	this->health.setTextureRect(IntRect(0, 0, this->healthTexture->getSize().x * percentage, this->healthTexture->getSize().y));
}

void HealthBar::setScale(int x, int y)
{
	this->health.setScale(x, y);
	this->background.setScale(x, y);
	this->scaleXIncrease = x;
	this->scaleYIncrease = y;
}
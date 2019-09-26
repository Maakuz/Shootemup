#include"HitBox.h"

HitBox::HitBox(Vector2i size, Vector2f position, bool isFriendly)
{
	this->sprite.setTexture(this->texture);
	this->sprite.setColor(Color::Green);
	this->rect.width = size.x;
	this->rect.height = size.y;
	this->rect.left = position.x;
	this->rect.top = position.y;
	this->offset = Vector2i(0, 0);
	this->sprite.setTextureRect(this->rect);
	this->sprite.setPosition(Vector2f(position.x + this->offset.x, position.y + this->offset.y));
	this->isFriendly = isFriendly;
}

HitBox::HitBox()
{
	this->sprite.setTexture(this->texture);
	this->sprite.setColor(Color::Green);
	this->rect.width = this->texture.getSize().x;
	this->rect.height = this->texture.getSize().y;
	this->offset = Vector2i(0, 0);
	this->sprite.setTextureRect(this->rect);
}

HitBox::~HitBox()
{
}

void HitBox::setSize(int width, int heigth)
{
	this->rect.width = width;
	this->rect.height = heigth;
	this->sprite.setTextureRect(this->rect);
}

Vector2i HitBox::getSize() const
{
	return Vector2i(this->rect.width, this->rect.height);
}

void HitBox::setPosition(float x, float y)
{
	this->rect.left = x + this->offset.x;
	this->rect.top = y + this->offset.y;
	this->sprite.setPosition(x + this->offset.x, y + this->offset.y);
}

Vector2f HitBox::getPosition() const
{
	return Vector2f(this->rect.left, this->rect.top);
}

void HitBox::setOffset(int x, int y)
{
	this->offset = Vector2i(x, y);
}

Vector2i HitBox::getOffset() const
{
	return this->offset;
}

void HitBox::setFriendly(bool value)
{
	this->isFriendly = value;
}

bool HitBox::getFriendly() const
{
	return this->isFriendly;
}

bool HitBox::operator==(const HitBox & compObj) const
{
	bool result = false;

	if (this->rect.intersects(compObj.rect))
		result = true;

	return result;
}

void HitBox::draw(RenderWindow& window)
{
	window.draw(this->sprite, RenderStates());
}
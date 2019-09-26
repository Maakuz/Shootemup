#include "Beam.h"

Beam::Beam(bool isFriendly, int duration, Texture* texture)
	:Bullet(isFriendly, 1, texture)
{
	setFrameSize(134, 118);
	setSheetSize(7, 1);
	this->duration = duration;
	this->expired = false;
}

Beam::~Beam()
{
}

bool Beam::getExprired() const
{
	return this->expired;
}

void Beam::updateSpecific(float dt)
{
	this->duration -= dt;



	if (duration <= 0)
		expired = true;
}

#ifndef BEAM_H
#define BEAM_H
#include"Bullet.h"

//I had a thought with this
//but times is a thing and I
//had none
class Beam : public Bullet
{
private:
	int duration;
	int startup;
	bool expired;
public:
	Beam(bool isFriendly, int duration, Texture* texture);
	virtual ~Beam();

	bool getExprired() const;

	void updateSpecific(float dt);
};

#endif
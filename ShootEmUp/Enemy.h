#ifndef ENEMY_H
#define ENEMY_H
#include"Character.h"

//All enemies will be inheriting from this
//class that inherits from the Character class
class Enemy : public Character
{
private:
	int value;
public:
	Enemy(Texture* texture, Texture* expl);
	virtual ~Enemy();

	void setValue(int value);
	int getValue() const;

	virtual Enemy* clone() const = 0;
	void updateSpecific(float dt, BulletContainer& bc, AudioHandler& ah);
	virtual void updateMoreSpecific(float dt, BulletContainer& bc) = 0;
};

#endif
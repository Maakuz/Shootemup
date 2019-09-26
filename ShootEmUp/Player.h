#ifndef PLAYER_H
#define PLAYER_H
#include"Character.h"

//The player. This is you.
class Player : public Character
{
private:
	void handleInputs(float dt, BulletContainer& bc, AudioHandler& ah);
public:
	Player(Texture* texture, Texture* expl, Texture* healthbar, Texture* background);
	virtual ~Player();

	void keepOnScreen();

	void updateSpecific(float dt, BulletContainer& bc, AudioHandler& ah);
};

#endif
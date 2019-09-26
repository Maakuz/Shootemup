#ifndef HEALTHBAR_H
#define HEALTHBAR_H
#include"SFML/Graphics.hpp"
using namespace sf;

//A bar for displaying health
class HealthBar
{
private:
	Texture* backgroundTexture;
	Texture* healthTexture;
	Sprite background;
	Sprite health;
	Vector2f offset;
	int scaleXIncrease;
	int scaleYIncrease;
public:
	HealthBar(Texture* background, Texture* healthBar);
	HealthBar();
	virtual ~HealthBar();

	void draw(RenderWindow& window);

	void setTextures(Texture* background, Texture* healthBar);
	void setOffset(float x, float y);
	void setPosOnChar(float x, float y);
	void setPosition(float x, float y);
	void setHealthBar(int maxHealth, int currentHealth);
	void setScale(int x, int y);


};

#endif
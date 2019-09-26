#ifndef BULLET_H
#define BULLET_H
#include"HitBox.h"
class Bullet
{
private:
	Texture* texture;
	Sprite sprite;

	Vector2f acceleration;
	Vector2f decceleration;
	Vector2f speed;

	HitBox rect;

	int damage;
	int decayTimer;
	bool isDecayed;
	bool isFriendly;

	//Animation
	int animCounter;
	int animSpeed;
	Vector2i currentFrame;
	Vector2i sheetSize;
	Vector2i frameSize;

	void animate(float dt);
public:
	Bullet(const bool isFriendly, int damage, Texture* texture);
	Bullet();
	virtual ~Bullet();

	void initialize(Vector2f accel, Vector2f deccel, Vector2f pos);
	virtual Bullet* clone() const = 0;

	void update(float dt);
	virtual void updateSpecific(float dt) = 0;
	virtual void draw(RenderWindow& window);
	void drawHitBox(RenderWindow& window);

	void setFrameSize(int x, int y);
	Vector2i getFrameSize() const;

	void setSheetSize(int x, int y);
	Vector2i getSheetSize() const;

	Vector2i getCurrentFrame() const;

	Vector2f getPos() const;

	bool getDecayed() const;

	void setDamage(int value);
	int getDamage() const;

	void setRect(int width, int heigth, int xOffset, int yOffset);
	HitBox getRect() const;

	void setFriendly(bool value);
	bool getFriendly() const;
};

#endif
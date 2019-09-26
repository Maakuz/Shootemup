#ifndef CHARACTER_H
#define CHARACTER_H
#include"HealthBar.h"
#include"BulletContainer.h"
#include"AudioHandler.h"

//All diffenent types of enemies and the player
//inherit from this class
class Character
{
private:
	Texture* texture;
	Texture* explTexture;
	Sprite sprite;
	Sprite explSprite;
	
	bool explodingStarted;
	bool isAnimated;
	Vector2i currentFrame;
	Vector2i frameSize;
	Vector2i sheetSize;
	float animCounter;
	float animSpeed;

	Vector2i currentExpFrame;
	Vector2i frameExpSize;
	Vector2i sheetExpSize;
	float animExpSpeed;

	HitBox collisionRect;
	HealthBar healthBar;

	Vector2f speed;
	Vector2f acceleration;
	Vector2f deceleration;

	int maxHealth;
	int health;
	int damage;
	float attackSpeed;
	int attackCounter;
	bool isFriendly;
	bool isAlive;
	bool isDying;

	void animate(float dt);
	void animateExp(float dt);
	void move(float dt);
public:
	Character(Texture* texture = nullptr, Texture* expl = nullptr);
	virtual ~Character();


	void initialize(float x, float y);
	void initializeHealthBar(Texture* healthbar, Texture* background);

	virtual void explode(float dt);

	bool checkCollision(BulletContainer& bc);

	void shoot(BulletContainer& bc, Vector2f accel, float xPos = 0, float yPos = 0, Vector2f deccel = Vector2f(1, 1));
	//void shootBeam(BulletContainer& bc, Vector2f accel, int duration);

	void update(float dt, BulletContainer& bc, AudioHandler& ah);

	virtual void updateSpecific(float dt, BulletContainer& bc, AudioHandler& ah) = 0;
	void draw(RenderWindow& window);
	void drawHitBox(RenderWindow& window);

	void setIsAnimating(bool value);
	
	void setCurrentFrame(int x, int y);

	void setSheetSize(int x, int y);

	void setFrameSize(int x, int y);
	Vector2i getFrameSize() const;

	void setRect(int width, int height, int xOffset, int yOffset);
	HitBox getRect() const;

	void setIsFriendly(bool value);
	bool getFriendly() const;

	void setIsAlive(bool value);
	bool getIsAlive() const;
	
	void setIsDying(bool value);
	bool getIsDying() const;

	float getAttackCounter() const;

	void setAttackSpeed(float value);
	float getAttackSpeed() const;
	
	void setDamage(int value);
	int getDamage() const;

	void setMaxHealth(int value);
	int getMaxHealth() const;

	void setHealth(int value);
	int getHealth() const;

	//standard is 1
	void setAnimationSpeed(float value);

	void setExplAnimSpeed(float value);
	
	void setAcceleration(float x, float y);
	Vector2f getAcceleration() const;
	
	void setDecceleration(float x, float y);
	
	void setXSpeed(float x);
	void setYSpeed(float y);
	Vector2f getSpeed() const;
	
	void setPos(float x, float y);
	Vector2f getPos() const;

	void setHealthBarScale(float x, float y);
	void setHealthBarPos();
	void setHealthBarPos(float x, float y);
	void updateHealthBar();
};

#endif
#ifndef BULLETCONTAINER_H
#define BULLETCONTAINER_H
#include"standardBullet.h"

//Handles all the bullets fried
class BulletContainer
{
private:
	Texture* bulletTexture;
	Bullet* *bullets;
	int nrOfBullets;
	int cap;

	void freeMemory();
	void initialize(int from = 0);
	void copy(const BulletContainer& originalObj);
	void expandArr();
	void checkOutOfBounds();
public:
	BulletContainer(int startCap = 30);
	BulletContainer(const BulletContainer& originalObj);
	virtual ~BulletContainer();
	
	void initializeBullets();

	void removeBullet(int index);
	bool checkCollision(HitBox const& target, int index);
	
	void addBullet(Vector2f startPos, Vector2f accel, bool friendly, int damage, Vector2f deccel);
	
	void update(float dt);
	void draw(RenderWindow& window);
	void drawHitboxes(RenderWindow& window);
	
	int getNrOfBullets() const;
	void setTexture(Texture* bullet);

	void operator=(const BulletContainer& originalObj);
	Bullet* operator[](int index) const;
};

#endif
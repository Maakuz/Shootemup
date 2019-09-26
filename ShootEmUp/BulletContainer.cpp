#include"BulletContainer.h"

BulletContainer::BulletContainer(int startCap)
{
	this->bulletTexture = nullptr;
	this->nrOfBullets = 0;
	this->cap = startCap;

	this->bullets = new Bullet*[startCap];
	initialize();
}

BulletContainer::BulletContainer(const BulletContainer& originalObj)
{
	copy(originalObj);
}

BulletContainer::~BulletContainer()
{
	freeMemory();
}

void BulletContainer::freeMemory()
{
	for (int i = 0; i < this->nrOfBullets; i++)
	{
		delete this->bullets[i];
	}

	delete[] this->bullets;
}

void BulletContainer::initialize(int from)
{
	for (int i = from; i < this->cap; i++)
	{
		this->bullets[i] = nullptr;
	}
}

void BulletContainer::copy(const BulletContainer& originalObj)
{
	this->cap = originalObj.cap;
	this->nrOfBullets = originalObj.nrOfBullets;
	this->bulletTexture = originalObj.bulletTexture;
	this->bullets = new Bullet*[originalObj.cap];
	for (int i = 0; i < originalObj.nrOfBullets; i++)
	{
		this->bullets[i] = originalObj.bullets[i]->clone();
	}

	initialize(originalObj.nrOfBullets);
}

void BulletContainer::expandArr()
{
	this->cap += 30;
	Bullet* *temp = new Bullet*[this->cap];

	for (int i = 0; i < this->nrOfBullets; i++)
	{
		temp[i] = this->bullets[i];
	}
	delete[] this->bullets;
	this->bullets = temp;
	initialize(this->nrOfBullets);
}

void BulletContainer::checkOutOfBounds()
{
	for (int i = 0; i < this->nrOfBullets; i++)
	{
		if (this->bullets[i]->getPos().y > 720 || this->bullets[i]->getPos().y < 0 - 32)
		{
			removeBullet(i);
		}
	}
}

void BulletContainer::initializeBullets()
{
	freeMemory();
	this->bullets = new Bullet*[this->cap];
	this->nrOfBullets = 0;
	initialize();
}

void BulletContainer::removeBullet(int index)
{
	delete this->bullets[index];
	this->bullets[index] = this->bullets[--this->nrOfBullets];
}

bool BulletContainer::checkCollision(HitBox const& target, int index)
{
	bool connected = false;
	if (this->bullets[index]->getRect() == target)
	{
		if (this->bullets[index]->getFriendly() && !target.getFriendly())
		{
			connected = true;
		}

		else if (!this->bullets[index]->getFriendly() && target.getFriendly())
		{
			connected = true;
		}
	}

	return connected;
}

void BulletContainer::addBullet(Vector2f startPos, Vector2f accel, bool friendly, int damage, Vector2f deccel)
{
	if (this->nrOfBullets >= this->cap)
		expandArr();

	this->bullets[this->nrOfBullets] = new StandardBullet(friendly, damage, this->bulletTexture);
	this->bullets[this->nrOfBullets]->initialize(accel, deccel, startPos);
	this->bullets[this->nrOfBullets]->setRect(24, 24, 4, 4);
	this->nrOfBullets++;
}

void BulletContainer::update(float dt)
{
	for (int i = 0; i < this->nrOfBullets; i++)
	{
		this->bullets[i]->update(dt);

		if (bullets[i]->getDecayed())
			removeBullet(i);
	}

	checkOutOfBounds();
}

void BulletContainer::draw(RenderWindow& window)
{
	for (int i = 0; i < this->nrOfBullets; i++)
	{
		this->bullets[i]->draw(window);
	}
}

void BulletContainer::drawHitboxes(RenderWindow& window)
{
	for (int i = 0; i < this->nrOfBullets; i++)
	{
		this->bullets[i]->drawHitBox(window);
	}
}

int BulletContainer::getNrOfBullets() const
{
	return this->nrOfBullets;
}

void BulletContainer::setTexture(Texture* texture)
{
	this->bulletTexture = texture;
}

void BulletContainer::operator=(const BulletContainer& originalObj)
{
	if (this != &originalObj)
	{
		freeMemory();
		copy(originalObj);
	}
}

Bullet* BulletContainer::operator[](int index) const
{
	return this->bullets[index];
}

#include"EnemyHandler.h"

EnemyHandler::EnemyHandler(int startCap)
{
	this->deathStareTexture = nullptr;
	this->healthBackTexture = nullptr;
	this->healthBarTexture = nullptr;
	this->speederTexture = nullptr;
	this->fighterTexture = nullptr;
	this->bomberTexture = nullptr;
	this->explTexture = nullptr;
	
	this->cap = startCap;

	this->nrOfEnemies = 0;

	this->fighterSpawnCounter = 0;
	this->bomberSpawnCounter = 0;
	this->speederSpawnCounter = 0;

	this->fighterSpawnSpeed = 0.6;
	this->bomberSpawnSpeed = 0;
	this->speederSpawnSpeed = 0;

	this->isBossLevel = false;
	this->spawnDeathStare = false;

	this->spawnTimer = 500;
	this->enemiesPerLevel = 0;

	this->enemies = new Enemy*[startCap];

	initialize();
}

EnemyHandler::EnemyHandler(const EnemyHandler & originalObj)
{
	copy(originalObj);
	initialize(originalObj.nrOfEnemies);
}

EnemyHandler::~EnemyHandler()
{
	freeMemory();
}

void EnemyHandler::initialize(int from)
{
	for (int i = from; i < this->cap; i++)
	{
		this->enemies[i] = nullptr;
	}
}

void EnemyHandler::freeMemory()
{
	for (int i = 0; i < this->nrOfEnemies; i++)
	{
		delete this->enemies[i];
	}
	delete[] this->enemies;
}

void EnemyHandler::copy(const EnemyHandler& originalObj)
{
	this->cap = originalObj.cap;
	this->nrOfEnemies = originalObj.nrOfEnemies;
	this->fighterSpawnCounter = originalObj.fighterSpawnCounter;
	this->fighterSpawnSpeed = originalObj.fighterSpawnSpeed;
	this->spawnTimer = originalObj.spawnTimer;

	this->enemies = new Enemy*[originalObj.cap];
	for (int i = 0; i < originalObj.nrOfEnemies; i++)
	{
		this->enemies[i] = originalObj.enemies[i]->clone();
	}

	initialize(originalObj.nrOfEnemies);
}

void EnemyHandler::expandArr()
{
	this->cap += 30;
	Enemy* *temp = new Enemy*[cap];

	for (int i = 0; i < this->nrOfEnemies; i++)
	{
		temp[i] = this->enemies[i];
	}
	delete[] this->enemies;
	this->enemies = temp;
	initialize(this->nrOfEnemies);
}

void EnemyHandler::spawnEnemies(float dt)
{
	this->fighterSpawnCounter += this->fighterSpawnSpeed * dt;
	this->bomberSpawnCounter += this->bomberSpawnSpeed * dt;
	this->speederSpawnCounter += this->speederSpawnSpeed * dt;

	if (this->enemiesPerLevel > 0)
	{
		//Spawn fighters
		if (this->fighterSpawnCounter >= this->spawnTimer)
		{
			this->fighterSpawnCounter = 0;

			if (this->nrOfEnemies >= this->cap)
				expandArr();

			this->enemies[this->nrOfEnemies] = new Fighter(this->fighterTexture, this->explTexture, this->healthBarTexture, this->healthBackTexture);
			this->enemies[this->nrOfEnemies]->initialize(rand() % (1280 - 40) + 1, -60);
			this->nrOfEnemies++;
			this->enemiesPerLevel--;
		}

		//Spawn bombers
		if (this->bomberSpawnCounter >= this->spawnTimer)
		{
			this->bomberSpawnCounter = 0;

			if (this->nrOfEnemies >= this->cap)
				expandArr();

			this->enemies[this->nrOfEnemies] = new Bomber(this->bomberTexture, this->explTexture, this->healthBarTexture, this->healthBackTexture);
			this->enemies[this->nrOfEnemies]->initialize(rand() % (1280 - 94) + 1, -100);
			this->nrOfEnemies++;

			this->enemiesPerLevel--;
		}

		//Spawn speeders
		if (this->speederSpawnCounter >= this->spawnTimer)
		{
			this->speederSpawnCounter = 0;

			if (this->nrOfEnemies >= this->cap)
				expandArr();

			this->enemies[this->nrOfEnemies] = new Speeder(this->speederTexture, this->explTexture, this->healthBarTexture, this->healthBackTexture);
			this->enemies[this->nrOfEnemies]->initialize(rand() % (1280 - 217) + 1, -220);
			this->nrOfEnemies++;
			this->enemiesPerLevel--;
		}
	}

	//Spawn DeathStare (BOSS)
	if (this->enemiesPerLevel <= 0 && this->nrOfEnemies <= 10 && this->isBossLevel && this->spawnDeathStare)
	{
		if (this->nrOfEnemies >= this->cap)
			expandArr();

		this->enemies[this->nrOfEnemies] = new DeathStare(this->deathStareTexture, this->explTexture, this->healthBarTexture, this->healthBackTexture);
		this->enemies[this->nrOfEnemies]->initialize(1280/2, -220);
		this->nrOfEnemies++;

		this->spawnDeathStare = false;
	}
}

void EnemyHandler::despawnEnemy(int index)
{
	delete this->enemies[index];
	this->enemies[index] = this->enemies[--this->nrOfEnemies];
}

void EnemyHandler::initializeEnemies(int enemyLevel)
{
	freeMemory();
	this->cap = 20;
	this->enemies = new Enemy*[this->cap];
	this->nrOfEnemies = 0;
	this->enemiesPerLevel = 25 + (25 * enemyLevel);
	
	this->bomberSpawnSpeed = enemyLevel * 0.15;
	this->fighterSpawnSpeed = 0.6 + (0.15 * enemyLevel);
	
	if (enemyLevel >= 2)
		this->speederSpawnSpeed = enemyLevel * 0.05;

	if (enemyLevel == 4)
	{
		this->isBossLevel = true;
		this->spawnDeathStare = true;
	}

	initialize();
}

void EnemyHandler::checkCollisionPlayer(Player& player)
{

	for (int i = 0; i < this->nrOfEnemies; i++)
	{
		if (this->enemies[i]->getRect() == player.getRect())
		{

			player.setHealth(player.getHealth() - this->enemies[i]->getDamage());
			player.updateHealthBar();
			despawnEnemy(i);
		}
	}
}

void EnemyHandler::checkEnemyOutOfBounds()
{
	for (int i = 0; i < this->nrOfEnemies; i++)
	{
		if (this->enemies[i]->getPos().y >= 720)
		{
			despawnEnemy(i);
		}
	}
}

void EnemyHandler::fireworks(float dt)
{
	//Using the fighter variables because I'm lazy

	this->fighterSpawnCounter += dt * 2;
	if (this->fighterSpawnCounter >= this->spawnTimer)
	{
		this->fighterSpawnCounter = 0;

		if (this->nrOfEnemies >= this->cap)
			expandArr();

		this->enemies[this->nrOfEnemies] = new Firework(this->explTexture);
		this->enemies[this->nrOfEnemies]->initialize(rand() % (1280 - 40) + 1, rand() % (720 - 40) + 1);
		this->nrOfEnemies++;
	}
}

void EnemyHandler::update(float dt, Player& player, BulletContainer& bc, UpgradeHandler& uh, AudioHandler& ah)
{
	for (int i = 0; i < this->nrOfEnemies; i++)
		this->enemies[i]->update(dt, bc, ah);

	for (int i = 0; i < this->nrOfEnemies; i++)
	{
		if (!enemies[i]->getIsAlive())
		{
			uh.addMoney(this->enemies[i]->getValue());
			despawnEnemy(i);
		}
	}

	spawnEnemies(dt);

	checkEnemyOutOfBounds();
	checkCollisionPlayer(player);
}

void EnemyHandler::draw(RenderWindow& window)
{
	for (int i = 0; i < this->nrOfEnemies; i++)
	{
		this->enemies[i]->draw(window);
	}
}

void EnemyHandler::drawHitboxes(RenderWindow & window)
{
	for (int i = 0; i < this->nrOfEnemies; i++)
	{
		this->enemies[i]->drawHitBox(window);
	}
}

void EnemyHandler::setTextures(Texture* figterGfx, Texture* bomberGfx, Texture* speederTexture, Texture* deathStareTexture, Texture* explGfx, Texture* healthBack, Texture* healthBar)
{
	this->deathStareTexture = deathStareTexture;
	this->healthBackTexture = healthBack;
	this->healthBarTexture = healthBar;
	this->speederTexture = speederTexture;
	this->fighterTexture = figterGfx;
	this->bomberTexture = bomberGfx;
	this->explTexture = explGfx;
}

int EnemyHandler::getNrOfEnemies() const
{
	return this->nrOfEnemies;
}

int EnemyHandler::getEnemiesPerLevel() const
{
	return this->enemiesPerLevel;
}

void EnemyHandler::operator=(const EnemyHandler& originalObj)
{
	if (this != &originalObj)
	{
		freeMemory();
		copy(originalObj);
	}
}
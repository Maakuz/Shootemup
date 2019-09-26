#ifndef ENEMYHANDLER_H
#define ENEMYHANDLER_H
#include"Fighter.h"
#include"Bomber.h"
#include"Speeder.h"
#include"DeathStare.h"
#include"UpgradeHandler.h"
#include"Firework.h"

//Keeps track of what the enemies are up to
class EnemyHandler
{
private:
	Texture* deathStareTexture;
	Texture* healthBackTexture;
	Texture* healthBarTexture;
	Texture* fighterTexture;
	Texture* speederTexture;
	Texture* bomberTexture;
	Texture* explTexture;


	int nrOfEnemies;
	int enemiesPerLevel;
	int cap;
	Enemy* *enemies;

	float fighterSpawnCounter;
	float fighterSpawnSpeed;
	float bomberSpawnCounter;
	float bomberSpawnSpeed;
	float speederSpawnCounter;
	float speederSpawnSpeed;

	float spawnTimer;

	bool isBossLevel;
	bool spawnDeathStare;

	void initialize(int from = 0);
	void freeMemory();
	void copy(const EnemyHandler& originalObj);
	void expandArr();
	void spawnEnemies(float dt);
	void despawnEnemy(int index);
public:
	EnemyHandler(int startingCap = 30);
	EnemyHandler(const EnemyHandler& originalObj);
	virtual ~EnemyHandler();
	
	void initializeEnemies(int enemyLevel);
	void checkCollisionPlayer(Player& player);
	void checkEnemyOutOfBounds();
	
	void fireworks(float dt);

	void update(float dt, Player& player, BulletContainer& bc, UpgradeHandler& uh, AudioHandler& ah);
	void draw(RenderWindow& window);
	void drawHitboxes(RenderWindow& window);

	void setTextures(Texture* figterGfx, Texture* bomberGfx, Texture* speederTexture, Texture* deathStareTexture, Texture* explGfx, Texture* healthBack, Texture* healthBar);
	int getNrOfEnemies() const;
	int getEnemiesPerLevel() const;

	void operator=(const EnemyHandler& originalObj);
};

#endif
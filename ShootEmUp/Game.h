#ifndef GAME_H
#define GAME_H
#include"Player.h"
#include"EnemyHandler.h"
#include"BulletContainer.h"
#include"MainMenu.h"
#include"UpgradeHandler.h"
#include"AudioHandler.h"

//The main game class. Everything is controlled from here.
class Game 
{
private:
	Texture healthbarBackgroundTexture;
	Texture menuBackgroundTexture;
	Texture mainButtonsTexture;
	Texture backgroundTexture;
	Texture deathStareTexture;
	Texture healthbarTexture;
	Texture upgradeBGTexture;
	Texture fighterTexture;
	Texture speederTexture;
	Texture buttonTexture;
	Texture playerTexture;
	Texture bomberTexture;
	Texture bulletTexture;
	Texture pauseTexture;
	Texture explTexture;
	Texture fadeTexture;
	Texture boxTexture;
	Font textFont;

	Player* player;
	Sprite background;
	Sprite pauseBG;
	Sprite fade;

	Text pauseText[2];
	Text victoryText;
	float scrollSpeed;

	TextBox textBox;
	AudioHandler ah;
	UpgradeHandler uh;
	EnemyHandler eh;
	BulletContainer bc;
	MainMenu mm;

	bool showHitBoxes;
	bool isPaused;
	bool isInitialized;
	bool levelCompleted;

	bool wasCtrlPressed;
	bool isCtrlPressed;
	bool isEscapePressed;
	bool wasEscapePressed;

	bool fadingOut;
	bool fadeCompleted;
	int fadeInTimer;
	int fadeOutTimer;
	float fadeCounter;
	int alpha;

	int gameState;

	void loadTextures();
	void initializeSprites();
	void keyboardInputs();
	void initialize();
	void scrollBackground(float dt);
	void updateFireworkFestival(float dt);
	void transition(float dt);
	void handleMainGame(float dt);
	void handleUpgrades(float dt);
public:
	Game();
	virtual ~Game();

	enum gameStates { mainMenu = 1, mainGame = 2, exit = 3, upgrades = 4, victory = 5, endScreen = 6 };

	void update(float dt, RenderWindow& window);
	void draw(RenderWindow& window);
	void drawHitboxes(RenderWindow& window);
};

#endif
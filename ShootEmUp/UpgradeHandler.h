#ifndef UPGRADEHANDLER_H
#define UPGRADEHANDLER_H
#include"Player.h"
#include"TextBox.h"

//A menu that keeps track of upgrades
//purchased and the players' cash
class UpgradeHandler
{
private:
	Texture* buttonsTexture;
	Texture* upgradeBgTexture;
	Font* font;
	Text text;
	Vector2f mainGameTextPos;
	Vector2f upgradeMenuTextPos;
	Sprite upgradeBG;
	static const int NROFBUTTONS = 5;
	Sprite buttons[NROFBUTTONS];
	int upgradesPurchased[NROFBUTTONS];
	int maxLevels[NROFBUTTONS];
	IntRect buttonRects[NROFBUTTONS];
	int upgradeCost[NROFBUTTONS];
	int buttonSelected;
	int cash;

	bool wasPurchased;
	bool wasMaxed;

	bool wasAPressed;
	bool wasDPressed;
	bool wasEnterPressed;
	bool isAPressed;
	bool isDPressed;
	bool isEnterPressed;
	bool swapText;

	int gameState;

	void keyboardUpdate(AudioHandler& ah);
	void buttonUpdate();
public:
	UpgradeHandler();
	virtual ~UpgradeHandler();

	enum upgrades {damage = 0, level = 1, enemyLevel = 2, moveSpeed = 3, attackSpeed = 4};

	void initialize();
	void addMoney(int cash);
	void typeToolTip(TextBox& textBox, bool enemiesSlain);
	int updateMenu(Player& player, bool &levelCompleted, AudioHandler& ah, TextBox& textBox);
	void update();
	void drawMenu(RenderWindow& window);
	void draw(RenderWindow& window);

	int getEnemyLevel() const;
	int getTotalEnemyLevels() const;
	void setTextures(Texture* upgradeBG, Texture* buttons);
	void setFont(Font* font);
};

#endif
#ifndef MAINMENU_H
#define MAINMENU_H
#include"SFML/Graphics.hpp"
#include"TextBox.h"
#include"AudioHandler.h"
using namespace sf;

//The mainest of menues. Start game and quit resides here
class MainMenu
{
private:
	static const int NROFBUTTONS = 2;
	Texture* backgroundTexture;
	Texture* buttonTexture;
	Sprite backGround;
	Sprite buttons[NROFBUTTONS];
	IntRect buttonRects[NROFBUTTONS];
	int buttonSelected;
	bool isWPressed;
	bool wasWPressed;
	bool isSPressed;
	bool wasSPressed;
	bool enterPressed;

	int gameState;
	
	void changeGraphics();
	void keyboardInput();
	void switchButton(AudioHandler& ah);
public:
	MainMenu();
	virtual ~MainMenu();

	void initialize();

	int update(TextBox& textBox, AudioHandler& ah);
	void draw(RenderWindow& window);

	void setTextures(Texture* backgroundTexture, Texture* buttonTexture);
};


#endif
#include "MainMenu.h"

MainMenu::MainMenu()
{
	this->backgroundTexture = nullptr;
	this->buttonTexture = nullptr;

	this->isSPressed = false;
	this->isWPressed = false;
	this->wasSPressed = false;
	this->wasWPressed = false;
	this->enterPressed = false;

	this->buttonSelected = 0;
	this->gameState = 1;
}

MainMenu::~MainMenu()
{}

void MainMenu::initialize()
{
	this->gameState = 1;
}

void MainMenu::changeGraphics()
{
	for (int i = 0; i < this->NROFBUTTONS; i++)
	{
		if (this->buttonSelected == i)
			this->buttons[i].setTextureRect(IntRect(this->buttonRects[i].width, this->buttonRects[i].top, this->buttonRects[i].width, this->buttonRects[i].height));

		else
			this->buttons[i].setTextureRect(IntRect(0, this->buttonRects[i].top, this->buttonRects[i].width, this->buttonRects[i].height));
	}
}

void MainMenu::keyboardInput()
{
	this->wasWPressed = this->isWPressed;
	this->wasSPressed = this->isSPressed;
	this->isWPressed = Keyboard::isKeyPressed(Keyboard::W);
	this->isSPressed = Keyboard::isKeyPressed(Keyboard::S);
	this->enterPressed = Keyboard::isKeyPressed(Keyboard::Return);
}

void MainMenu::switchButton(AudioHandler& ah)
{
	if (this->isWPressed && !this->wasWPressed)
	{
		this->buttonSelected--;
		ah.playSelecetSound();
	}

	if (this->isSPressed && !this->wasSPressed)
	{
		this->buttonSelected++;
		ah.playSelecetSound();
	}

	if (this->buttonSelected >= this->NROFBUTTONS)
	{
		this->buttonSelected = 0;
	}

	if (this->buttonSelected < 0)
	{
		this->buttonSelected = this->NROFBUTTONS - 1;
	}
}

int MainMenu::update (TextBox& textBox, AudioHandler& ah)
{
	changeGraphics();
	keyboardInput();
	switchButton(ah);
	
	if (this->enterPressed)
	{
		switch (this->buttonSelected)
		{
		case 0:
			this->gameState = 4;
			break;

		case 1:
			this->gameState = 3;
			break;
		}
	}

	return this->gameState;
}

void MainMenu::draw(RenderWindow & window)
{
	window.draw(backGround);

	for (int i = 0; i < this->NROFBUTTONS; i++)
	{
		window.draw(this->buttons[i]);
	}
}

void MainMenu::setTextures(Texture* backgroundTexture, Texture* buttonTexture)
{
	this->buttonTexture = buttonTexture;
	this->backgroundTexture = backgroundTexture;

	this->backGround.setTexture(*backgroundTexture);
	for (int i = 0; i < this->NROFBUTTONS; i++)
	{
		this->buttons[i].setTexture(*buttonTexture);
		this->buttonRects[i] = IntRect(IntRect(0, i * (this->buttonTexture->getSize().y / this->NROFBUTTONS), this->buttonTexture->getSize().x / 2, this->buttonTexture->getSize().y / this->NROFBUTTONS));
		this->buttons[i].setTextureRect(this->buttonRects[i]);
		this->buttons[i].setPosition(Vector2f((1280 / 2) - (this->buttonTexture->getSize().x / 4), 100 + (i * 200)));
	}
}
#include"Game.h"

Game::Game()
{
	loadTextures();

	initializeSprites();

	this->scrollSpeed = 2;

	this->alpha = 0;
	this->fadeCounter = 0;
	this->fadeInTimer = 100;
	this->fadeOutTimer = 3000;

	this->fadingOut = true;
	this->fadeCompleted = true;
	this->isInitialized = false;

	this->showHitBoxes = false;
	this->isPaused = false;
	this->levelCompleted = false;

	this->wasCtrlPressed = true;
	this->isCtrlPressed = true;
	this->wasEscapePressed = true;
	this->isEscapePressed = true;

	this->gameState = gameStates::mainMenu;

	this->player = new Player(&this->playerTexture, &this->explTexture, &this->healthbarTexture, &this->healthbarBackgroundTexture);
}

Game::~Game()
{
	delete this->player;
}

void Game::loadTextures()
{
	//Characters
	this->deathStareTexture.loadFromFile("../Gfx/characters/deathStare.png");
	this->speederTexture.loadFromFile("../Gfx/characters/speeder.png");
	this->fighterTexture.loadFromFile("../Gfx/characters/fighter.png");
	this->playerTexture.loadFromFile("../Gfx/characters/player.png");
	this->bomberTexture.loadFromFile("../Gfx/characters/bomber.png");

	//UI
	this->healthbarBackgroundTexture.loadFromFile("../Gfx/UI/HPBack.png");
	this->menuBackgroundTexture.loadFromFile("../Gfx/UI/menuBack.png");
	this->upgradeBGTexture.loadFromFile("../Gfx/UI/upgradeBack.png");
	this->mainButtonsTexture.loadFromFile("../Gfx/UI/buttons.png");
	this->healthbarTexture.loadFromFile("../Gfx/UI/HPFront.png");
	this->buttonTexture.loadFromFile("../Gfx/UI/upgradeGfx.png");
	this->boxTexture.loadFromFile("../Gfx/UI/textBox.png");
	this->pauseTexture.loadFromFile("../Gfx/UI/pauseBG.png");


	//Other
	this->backgroundTexture.loadFromFile("../Gfx/sky.png");
	this->bulletTexture.loadFromFile("../Gfx/bullet.png");
	this->explTexture.loadFromFile("../Gfx/bam16.png");

	//Font
	this->textFont.loadFromFile("../Fonts/8bitoperator.ttf");

	//Setting thte pointers in the classes to these textures
	this->bc.setTexture(&this->bulletTexture);
	this->eh.setTextures(&this->fighterTexture, &this->bomberTexture, &this->speederTexture, &this->deathStareTexture, &this->explTexture, &this->healthbarBackgroundTexture, &this->healthbarTexture);
	this->mm.setTextures(&this->menuBackgroundTexture, &this->mainButtonsTexture);
	this->textBox.setBoxTexture(&this->boxTexture);
	this->textBox.setFont(&this->textFont);
	this->textBox.setPos(0, 720 - this->boxTexture.getSize().y);
	this->uh.setFont(&this->textFont);
	this->uh.setTextures(&this->upgradeBGTexture, &this->buttonTexture);
}

void Game::initializeSprites()
{
	this->fade.setColor(Color(0, 0, 0, 0));
	this->fade.setTexture(this->fadeTexture);
	this->fade.setTextureRect(IntRect(0, 0, 1280, 720));

	this->background.setTexture(backgroundTexture);
	this->background.setPosition(0, 1800);

	this->victoryText.setFont(textFont);
	this->victoryText.setCharacterSize(50);
	this->victoryText.setPosition(100, 300);
	this->victoryText.setString("Congratulations!");

	for (int i = 0; i < 2; i++)
	{
		this->pauseText[i].setFont(textFont);
		this->pauseText[i].setCharacterSize(100);
		this->pauseText[i].setString("Paused");
		this->pauseText[i].setPosition(Vector2f((1280 / 2) - 300, 200));
	}
	this->pauseBG.setTexture(this->pauseTexture);

	this->pauseText[0].move(Vector2f(5, 5));
	this->pauseText[0].setColor(Color::Black);
}

void Game::keyboardInputs()
{
	this->wasCtrlPressed = this->isCtrlPressed;
	this->wasEscapePressed = this->isEscapePressed;
	this->isCtrlPressed = Keyboard::isKeyPressed(Keyboard::LControl);
	this->isEscapePressed = Keyboard::isKeyPressed(Keyboard::Escape);

	if (this->isCtrlPressed && !this->wasCtrlPressed)
		this->showHitBoxes = !this->showHitBoxes;

	if (this->isEscapePressed && !this->wasEscapePressed)
		this->isPaused = !this->isPaused;
}

void Game::initialize()
{
	this->isEscapePressed = true;
	this->mm.initialize();
	this->uh.initialize();
	this->eh.initializeEnemies(this->uh.getEnemyLevel());
	this->bc.initializeBullets();
	this->player->initialize(400, 600);
	this->isInitialized = true;
}

void Game::scrollBackground(float dt)
{
	this->background.move(0, this->scrollSpeed * dt);

	if (this->background.getPosition().y > 0)
	{
		this->background.setPosition(0, -1800);
	}
}

void Game::updateFireworkFestival(float dt)
{
	keyboardInputs();
	scrollBackground(dt);

	this->player->setHealthBarPos(-400, -400);
	this->player->update(dt, this->bc, this->ah);
	this->eh.fireworks(dt);
	this->eh.update(dt, *this->player, this->bc, this->uh, this->ah);

	//This is mainly to time the music with background speedup or slowdown

	//First speedup
	if (this->ah.getVictoryPos() >= 33333 && this->ah.getVictoryPos() < 120800)
	{
		this->scrollSpeed += dt * 0.00013;

		if (this->scrollSpeed > 10)
			this->scrollSpeed = 10;

		this->victoryText.move(0, 0.5);
		if (this->victoryText.getPosition().y > 600)
			this->victoryText.setPosition(this->victoryText.getPosition().x, 600);
	}

	//Second slowdown
	else if (this->ah.getVictoryPos() >= 122000 && this->ah.getVictoryPos() < 122800)
	{
		this->scrollSpeed -= dt * 0.02;

		if (this->scrollSpeed < 0.05)
			this->scrollSpeed = 0.05;
	}

	//Second speedup
	else if (this->ah.getVictoryPos() >= 122800 && this->ah.getVictoryPos() < 153490)
	{
		this->scrollSpeed += dt * 0.007;

		if (this->scrollSpeed > 10)
			this->scrollSpeed = 10;
	}

	//third slowdown
	else if (this->ah.getVictoryPos() >= 153490 && this->ah.getVictoryPos() < 155460)
	{
		this->scrollSpeed -= dt * 0.007;

		if (this->scrollSpeed < 0.05)
			this->scrollSpeed = 0.05;
	}

	//Final speedup
	else if (this->ah.getVictoryPos() >= 155460 && this->ah.getVictoryPos() < 178000)
	{
		this->scrollSpeed += dt * 0.005;

		if (this->scrollSpeed > 10)
			this->scrollSpeed = 10;

		this->victoryText.setString("Pretty good song yeah?\nGoogle \"BKMJMBOX\"");
		this->victoryText.move(0, -1);
	}

	//Fourth slowdown
	else if (this->ah.getVictoryPos() >= 178000 && this->ah.getVictoryPos() < 180000)
	{
		this->scrollSpeed -= dt * 0.005;

		if (this->scrollSpeed < 2)
			this->scrollSpeed = 2;
	}

	//Final slowdown
	else if (this->ah.getVictoryPos() >= 180000)
	{
		this->scrollSpeed -= dt * 0.0003;

		if (this->scrollSpeed < 0.01)
			this->scrollSpeed = 0.01;

		this->fadeOutTimer = 15000;
		this->fadeInTimer = 10000;
		this->fadeCompleted = false;

		if (!this->fadingOut)
			this->gameState = gameStates::endScreen;
	}
	
	//First slowdown
	else
	{
		this->scrollSpeed -= 0.0003;

		if (this->scrollSpeed < 0.05)
			this->scrollSpeed = 0.05;
	}
}

void Game::transition(float dt)
{
	if (this->fadingOut)
	{
		this->fadeCounter += dt;
		this->alpha = (this->fadeCounter / this->fadeOutTimer) * 255;

		if (this->fadeCounter >= this->fadeOutTimer)
		{
			this->fadingOut = false;
			this->fadeCounter = this->fadeInTimer;

			if (this->alpha > 255)
				this->alpha = 255;
		}
	}

	else
	{
		this->fadeCounter -= dt;
		this->alpha = (this->fadeCounter / this->fadeInTimer) * 255;

		if (this->fadeCounter <= 0)
		{
			this->fadeCompleted = true;
			this->fadingOut = true;

			if (this->alpha < 0)
				this->alpha = 0;
		}
	}


	this->fade.setColor(Color(0, 0, 0, this->alpha));
}

void Game::handleMainGame(float dt)
{
	keyboardInputs();

	if (!this->isPaused)
	{
		this->player->update(dt, this->bc, this->ah);
		this->eh.update(dt, *this->player, this->bc, this->uh, this->ah);
		this->bc.update(dt);
		this->uh.update();
		scrollBackground(dt);

		if (!this->player->getIsAlive())
		{
			this->gameState = gameStates::mainMenu;
			this->isInitialized = false;
			this->ah.stopBgm();
		}

		if (this->eh.getNrOfEnemies() == 0 && this->eh.getEnemiesPerLevel() == 0)
		{
			this->levelCompleted = true;
			this->ah.stopBgm();

			//If it's the last level you should be taken to 
			//the victory screen instead of the main menu
			if (this->uh.getTotalEnemyLevels() == this->uh.getEnemyLevel())
			{
				this->ah.playVictory();
				this->scrollSpeed -= dt * 0.0006;
				
				if (this->scrollSpeed < 0.5)
					this->scrollSpeed = 0.5;
					
				this->fadeOutTimer = 5000;
				this->fadeInTimer = 10000;
				this->fadeCompleted = false;

				if (!this->fadingOut)
					this->gameState = gameStates::victory;
			}

			else
				this->gameState = gameStates::mainMenu;
		}
	}
}

void Game::handleUpgrades(float dt)
{
	this->textBox.update(dt);

	if (this->uh.updateMenu(*this->player, this->levelCompleted, this->ah, this->textBox) == gameStates::mainGame)
	{
		this->ah.startBgm();
		this->fadeCompleted = false;

		if (!this->fadingOut)
			this->gameState = gameStates::mainGame;
	}

	if (this->gameState != gameStates::upgrades)
	{
		initialize();
	}
}

void Game::update(float dt, RenderWindow& window)
{
	if (!this->fadeCompleted)
		transition(dt);

	this->ah.update();

	switch (this->gameState)
	{
	case gameStates::mainMenu:
		this->gameState = this->mm.update(this->textBox, this->ah);
		break;

	case gameStates::mainGame:
		handleMainGame(dt);
		break;

	case gameStates::upgrades:
		handleUpgrades(dt);
		break;

	case gameStates::exit:
		window.close();
		break;

	case gameStates::victory:
		updateFireworkFestival(dt);
		this->ah.playVictory();
		break;

	case gameStates::endScreen:
		this->victoryText.setPosition(450, 300);
		this->victoryText.setCharacterSize(70);
		this->victoryText.setString("THE END");
		scrollBackground(dt);
		break;
	}
}

void Game::draw(RenderWindow& window)
{

	switch (this->gameState)
	{
	case gameStates::mainMenu:
		this->mm.draw(window);
		break;

	case gameStates::mainGame:
		window.draw(this->background);

		this->player->draw(window);
		this->eh.draw(window);
		this->bc.draw(window);
		this->uh.draw(window);
		if (this->showHitBoxes)
			drawHitboxes(window);

		if (this->isPaused)
		{
			window.draw(this->pauseBG);
			for (int i = 0; i < 2; i++)
			{
				window.draw(this->pauseText[i]);
			}
		}
		break;

	case gameStates::upgrades:
		this->uh.drawMenu(window);
		this->textBox.draw(window);
		break;

	case gameStates::victory:
		window.draw(this->background);
		window.draw(this->victoryText);
		this->player->draw(window);
		this->eh.draw(window);
		break;

	case gameStates::endScreen:
		window.draw(this->background);
		window.draw(this->victoryText);
		break;
	}
	
	window.draw(this->fade);
}

void Game::drawHitboxes(RenderWindow& window)
{
	this->player->drawHitBox(window);
	this->eh.drawHitboxes(window);
	this->bc.drawHitboxes(window);
}

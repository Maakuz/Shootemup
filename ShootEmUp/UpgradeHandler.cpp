#include"UpgradeHandler.h"

UpgradeHandler::UpgradeHandler()
{
	this->upgradeBgTexture = nullptr;
	this->buttonsTexture = nullptr;
	this->font = nullptr;
	this->mainGameTextPos = Vector2f(10, 660);
	this->upgradeMenuTextPos = Vector2f(10, 500);
	this->text.setCharacterSize(20);

	for (int i = 0; i < this->NROFBUTTONS; i++)
	{
		this->upgradesPurchased[i] = 0;
	}

	this->gameState = 4;

	this->wasEnterPressed = true;

	this->swapText = true;
	this->wasPurchased = false;
	this->wasMaxed = false;

	this->buttonSelected = 0;
	this->cash = 100;

	this->maxLevels[0] = 5;
	this->maxLevels[1] = 5;
	this->maxLevels[2] = 4;
	this->maxLevels[3] = 5;
	this->maxLevels[4] = 5;

	this->upgradeCost[0] = 500;
	this->upgradeCost[1] = 400;
	this->upgradeCost[2] = 1000;
	this->upgradeCost[3] = 700;
	this->upgradeCost[4] = 900;
}

UpgradeHandler::~UpgradeHandler()
{}

void UpgradeHandler::keyboardUpdate(AudioHandler& ah)
{
	this->wasAPressed = this->isAPressed;
	this->wasDPressed = this->isDPressed;
	this->wasEnterPressed = this->isEnterPressed;
	this->isAPressed = Keyboard::isKeyPressed(Keyboard::A);
	this->isDPressed = Keyboard::isKeyPressed(Keyboard::D);
	this->isEnterPressed = Keyboard::isKeyPressed(Keyboard::Return);

	if (this->isAPressed && !this->wasAPressed)
	{
		this->buttonSelected--;
		this->swapText = true;
		ah.playSelecetSound();
	}

	if (this->isDPressed && !this->wasDPressed)
	{
		this->buttonSelected++;
		this->swapText = true;
		ah.playSelecetSound();
	}

	if (this->buttonSelected >= this->NROFBUTTONS)
		this->buttonSelected = 0;

	if (this->buttonSelected < 0)
		this->buttonSelected = this->NROFBUTTONS - 1;

	if (Keyboard::isKeyPressed(Keyboard::Escape))
		this->gameState = 2;
}

void UpgradeHandler::buttonUpdate()
{
	for (int i = 0; i < this->NROFBUTTONS; i++)
	{
		if (this->buttonSelected == i)
			this->buttons[i].setTextureRect(IntRect(this->buttonRects[i].width, this->buttonRects[i].top, this->buttonRects[i].width, this->buttonRects[i].height));

		else
			this->buttons[i].setTextureRect(IntRect(0, this->buttonRects[i].top, this->buttonRects[i].width, this->buttonRects[i].height));
	}
}

void UpgradeHandler::initialize()
{
	this->isEnterPressed = true;
	this->gameState = 4;
}

void UpgradeHandler::addMoney(int cash)
{
	this->cash += cash;
}

void UpgradeHandler::typeToolTip(TextBox& textBox, bool enemiesSlain)
{
	if (this->swapText)
	{
		string additionalText = "Current level: " + to_string(this->upgradesPurchased[this->buttonSelected]) + ". Upgrade cost: "+ to_string(this->upgradeCost[this->buttonSelected]) + "\n";
		textBox.readText("../Txts/upgrade" + to_string(this->buttonSelected) + ".txt", this->upgradesPurchased[this->buttonSelected], additionalText);
		this->swapText = false;
	}

	if (this->isEnterPressed && !this->wasEnterPressed)
	{
		if (this->wasPurchased)
			textBox.setText("Upgrade purchased!");

		else if (this->wasMaxed)
			textBox.setText("Maxed out!");

		else if (!enemiesSlain && this->cash >= this->upgradeCost[upgrades::enemyLevel] && this->buttonSelected == upgrades::enemyLevel)
			textBox.setText("Maybe we should show the enemies what we are capable of first.");

		else
			textBox.setText("Not enough cash!");
	}
}

int UpgradeHandler::updateMenu(Player& player, bool& levelComplete, AudioHandler& ah, TextBox& textBox)
{
	typeToolTip(textBox, levelComplete);

	if (this->gameState == 4)
	{
		buttonUpdate();
		keyboardUpdate(ah);
	}
	this->text.setString("Cash: " + to_string(this->cash));
	this->text.setPosition(this->upgradeMenuTextPos);

	if (this->isEnterPressed && !this->wasEnterPressed)
	{
		this->wasPurchased = false;
		this->wasMaxed = false;

		switch (this->buttonSelected)
		{
		case upgrades::damage:
			if (this->cash >= this->upgradeCost[upgrades::damage])
			{
				if (this->upgradesPurchased[upgrades::damage] >= this->maxLevels[upgrades::damage])
					this->wasMaxed = true;
				
				else
				{
					this->cash -= upgradeCost[upgrades::damage];
					this->upgradeCost[upgrades::damage] = static_cast<int>(this->upgradeCost[upgrades::damage] * 2.25);
					this->upgradesPurchased[upgrades::damage]++;
					player.setDamage(player.getDamage() + static_cast<int>((player.getDamage() * 0.3)));
					this->wasPurchased = true;
					ah.playBuySound();
				}
			}
			break;

		case upgrades::level:
			if (this->cash >= this->upgradeCost[upgrades::level])
			{
				if (this->upgradesPurchased[upgrades::level] >= this->maxLevels[upgrades::level])
					this->wasMaxed = true;

				else
				{
					this->cash -= this->upgradeCost[upgrades::level];
					this->upgradeCost[upgrades::level] = static_cast<int>(this->upgradeCost[upgrades::level] * 2.1);
					this->upgradesPurchased[upgrades::level]++;
					player.setMaxHealth(player.getMaxHealth() + static_cast<int>((player.getMaxHealth() * 0.4)));
					this->wasPurchased = true;
					ah.playBuySound();
				}
			}
			break;

		case upgrades::enemyLevel:
			if (this->cash >= this->upgradeCost[upgrades::enemyLevel] && levelComplete)
			{
				this->cash -= this->upgradeCost[upgrades::enemyLevel];
				this->upgradeCost[upgrades::enemyLevel] = static_cast<int>(upgradeCost[upgrades::enemyLevel] * 2.75);
				this->upgradesPurchased[upgrades::enemyLevel]++;
				levelComplete = false;
				this->wasPurchased = true;
				ah.playBuySound();
			}
			break;

		case upgrades::moveSpeed:
			if (this->cash >= this->upgradeCost[upgrades::moveSpeed])
			{
				if (this->upgradesPurchased[upgrades::moveSpeed] >= this->maxLevels[upgrades::moveSpeed])
					this->wasMaxed = true;

				else
				{
					this->cash -= this->upgradeCost[upgrades::moveSpeed];
					this->upgradeCost[upgrades::moveSpeed] = static_cast<int>(this->upgradeCost[upgrades::moveSpeed] * 2);
					this->upgradesPurchased[upgrades::moveSpeed]++;
					player.setAcceleration(player.getAcceleration().x + player.getAcceleration().x * 0.10f, player.getAcceleration().x + player.getAcceleration().y * 0.10f);
					this->wasPurchased = true;
					ah.playBuySound();
				}
			}
			break;

		case upgrades::attackSpeed:
			if (this->cash >= this->upgradeCost[upgrades::attackSpeed])
			{
				if (this->upgradesPurchased[upgrades::attackSpeed] >= this->maxLevels[upgrades::attackSpeed])
					this->wasMaxed = true;

				else
				{
					this->cash -= this->upgradeCost[upgrades::attackSpeed];
					this->upgradeCost[upgrades::attackSpeed] = static_cast<int>(this->upgradeCost[upgrades::attackSpeed] * 2.5);
					this->upgradesPurchased[upgrades::attackSpeed]++;
					player.setAttackSpeed(player.getAttackSpeed() - (player.getAttackSpeed() * 0.15f));
					this->wasPurchased = true;
					ah.playBuySound();
				}
			}
			break;
		}
	}

	return this->gameState;
}

void UpgradeHandler::update()
{
	this->text.setString("Cash: " + to_string(this->cash));
	this->text.setPosition(this->mainGameTextPos);
}

void UpgradeHandler::drawMenu(RenderWindow& window)
{
	window.draw(this->upgradeBG);

	for (int i = 0; i < this->NROFBUTTONS; i++)
	{
		window.draw(this->buttons[i]);
	}

	window.draw(this->text);
}

void UpgradeHandler::draw(RenderWindow& window)
{
	window.draw(this->text);
}

int UpgradeHandler::getEnemyLevel() const
{
	return this->upgradesPurchased[upgrades::enemyLevel];
}

int UpgradeHandler::getTotalEnemyLevels() const
{
	return this->maxLevels[upgrades::enemyLevel];
}

void UpgradeHandler::setTextures(Texture* upgradeBG, Texture* buttons)
{
	this->buttonsTexture = buttons;
	this->upgradeBgTexture = upgradeBG;

	this->upgradeBG.setTexture(*this->upgradeBgTexture);
	for (int i = 0; i < this->NROFBUTTONS; i++)
	{
		this->buttons[i].setTexture(*this->buttonsTexture);
		this->buttons[i].setPosition(static_cast<float>(65 + (i * ((this->buttonsTexture->getSize().x / 2) + 40))), 250);
		this->buttonRects[i] = IntRect(0, i * (this->buttonsTexture->getSize().y / this->NROFBUTTONS), this->buttonsTexture->getSize().x / 2, this->buttonsTexture->getSize().y / this->NROFBUTTONS);
		this->buttons[i].setTextureRect(this->buttonRects[i]);
	}
}

void UpgradeHandler::setFont(Font* font)
{
	this->font = font;
	this->text.setFont(*this->font);
}
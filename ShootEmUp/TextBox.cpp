#include"TextBox.h"

TextBox::TextBox()
{
	this->text.setCharacterSize(16);
	this->outlineSize = Vector2f(5, 7);
	this->timer = 15;
	this->counter = 0;
	this->letterNr = 0;
	this->textToWrite = "";
	this->thisText = "";
}

TextBox::~TextBox()
{}

void TextBox::readText(string filePath, int from, string startText)
{
	fstream readFile;
	string inText = "";
	string text = startText;
	int nrOfLines = 0;


	readFile.open(filePath);

	//In this case i want to read the first line as well.
	getline(readFile, inText);
	text += inText + "\n\n";
	//--------------------------------

	for (int i = 0; i < from; i++)
	{
		readFile >> nrOfLines;
		readFile.ignore();

		for (int i = 0; i < nrOfLines; i++)
		{
			getline(readFile, inText);
		}
	}


	readFile >> nrOfLines;
	readFile.ignore();

	for (int i = 0; i < nrOfLines; i++)
	{
		getline(readFile, inText);
		text += inText + "\n";
	}

	readFile.close();

	this->thisText = text;
	this->textToWrite = "";
	this->letterNr = 0;
}

void TextBox::update(float dt)
{
	this->counter += dt;

	if (this->counter >= this->timer && this->letterNr < this->thisText.length())
	{
		this->textToWrite += this->thisText[this->letterNr];
		this->counter = 0;

		if (this->thisText[this->letterNr] == '.')
			this->counter = -400;

		if (this->thisText[this->letterNr] == ',')
			this->counter = -200;

		this->letterNr++;

		this->text.setString(this->textToWrite);
	}

	this->boxSprite.setPosition(pos);
	this->text.setPosition(pos + outlineSize);
}

void TextBox::draw(RenderWindow& window)
{
	window.draw(this->boxSprite);
	window.draw(this->text);
}

void TextBox::setText(string text)
{
	this->thisText = text;
	this->textToWrite = "";
	this->letterNr = 0;
}

void TextBox::setFont(Font* font)
{
	this->font = font;
	this->text.setFont(*this->font);
}

void TextBox::setBoxTexture(Texture* texture)
{
	this->boxTexture = texture;
	this->boxSprite.setTexture(*this->boxTexture);
}

void TextBox::setPos(float x, float y)
{
	this->pos = Vector2f(x, y);
}
#ifndef TEXTBOX_H
#define TEXTBOX_H
#include"SFML/Graphics.hpp"
#include<string>
#include<fstream>
using namespace std;
using namespace sf;

//A textbox. Like in the old games. With scrolling text
class TextBox
{
private:
	Font* font;
	Text text;
	Texture* boxTexture;
	Sprite boxSprite;
	Vector2f pos;
	Vector2f outlineSize;
	int timer;
	int counter;
	int letterNr;
	string textToWrite;
	string thisText;

public:
	TextBox();
	virtual ~TextBox();

	void readText(string filePath, int from, string additionalStartText = "");
	void update(float dt);

	void draw(RenderWindow& window);

	void setText(string text);
	void setFont(Font* font);
	void setBoxTexture(Texture* texture);
	void setPos(float x, float y);
};


#endif
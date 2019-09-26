#ifndef HITBOX_H
#define HITBOX_H
#include"SFML/Graphics.hpp"
using namespace sf;

//Basically a glorified IntRect
//Can be drawn to see hitbox
class HitBox
{
private:
	Texture texture;
	Sprite sprite;

	Vector2i offset;
	IntRect rect;

	bool isFriendly;
public:
	HitBox(Vector2i size, Vector2f position, bool friendly);
	HitBox();
	virtual ~HitBox();
	
	void draw(RenderWindow& window);

	void setSize(int height, int width);
	Vector2i getSize() const;

	void setPosition(float x, float y);
	Vector2f getPosition() const;
	
	void setOffset(int x, int y);
	Vector2i getOffset() const;
	
	void setFriendly(bool value);
	bool getFriendly() const;

	bool operator==(const HitBox& compObj) const;
};

#endif
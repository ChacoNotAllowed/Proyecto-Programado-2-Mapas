#pragma once
#include "Resources.h"

class Buttons
{
private:

	Text text;
	Font font;
	Color normalColor;
	Color hoverColor;
	Color pressedColor;
	bool deleteButton = false;
	bool isPressed = false;

public:

	Buttons();

	virtual void render(RenderWindow& window) = 0;
	virtual void update(Vector2i& mousePos) = 0;
	
	bool isButtonPressed();
	void setPressed(bool is);
	void setDelete(bool borrar);
	bool getDelete();
	void setColors(Color normal, Color hover, Color pressed);
	Text& getText();
	Color getNormalColor();
	Color getHoverColor();
	Color getPressedColor();

};

class RectButton :public Buttons 
{
private:
	RectangleShape shape;
public:
	bool wasPressed = false;
	RectButton(float x,float y,float width,float height,string buttonText);
	RectButton(float x, float y, float width, float height, Color color);
	void render(RenderWindow& window)override;
	void update(Vector2i& mousePos)override;
	void setPosition(int x, int y);
	void setTextPosition(int x, int y);
	
};

class CircButton :public Buttons {
private:
	CircleShape circle;
	
public:
	CircButton(float x, float y, string circleText, Color color);
	void render(RenderWindow& window)override;
	void update(Vector2i& mousePos)override;
	
	

};
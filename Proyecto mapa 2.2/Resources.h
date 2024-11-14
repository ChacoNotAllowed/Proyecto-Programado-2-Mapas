#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
using namespace std;
using namespace sf;

class Resources
{
private:
	Texture mapTexture;
	Sprite mapSprite;
	Font font;
public:
	Resources();	
	Sprite getMapSprite();
	Font getFont();
};


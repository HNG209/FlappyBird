#pragma once
#include"SFML/Graphics.hpp"
class Background
{
private:
	sf::RenderWindow* window;
	const std::string BG_path = "Assets\\BG\\BGL.png";
	sf::Sprite BG;
	sf::Texture BG_texture;
public:
	Background(sf::RenderWindow*);
	void draw();
};


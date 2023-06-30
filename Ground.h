#pragma once
#include"SFML/Graphics.hpp"
#include"Collider.h"
class Ground : public Collider
{
private:
	const std::string path = "Assets\\Collider\\Ground.png";
	sf::Sprite ground;
	sf::Texture ground_texture;
	sf::RenderWindow* window;
public:
	Ground(sf::RenderWindow*);
	void draw();
	void show_hitbox();
};


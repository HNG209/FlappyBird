#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"Collider.h"
class Bird : public Collider
{
private:
	sf::RenderWindow* window;
	const std::string texture_path = "Assets\\Collider\\Bird.png";
	sf::Sprite bird;
	sf::Texture bird_texture;
	float dt;
	const float refresh_time = 0.2f;
	int i;
public:
	Bird(sf::RenderWindow*);
	void set_position(const sf::Vector2f&);
	void operator=(const sf::RectangleShape&);
	void update(float);
	void show_hitbox();
	void draw();
	inline float _map(float value, float value_min, float value_max, float rangeL, float rangeH) {
		return value * (rangeH - rangeL) / (value_max - value_min) + rangeL;
	}
};


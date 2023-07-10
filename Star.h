#pragma once
#include<SFML/Graphics.hpp>
#include"Collider.h"
#include<iostream>
#include<math.h>
#define PI 3.141592f
#define toRad(d) (float)d * (PI / 180) 
class Star : public Collider
{
private:
	const std::string path = "Assets\\Collider\\Star.png";
	sf::Texture Star_texture;
	sf::RenderWindow* window;
	sf::Sprite Star_sprite;
	float speed;
	float angle;
public:
	Star(sf::RenderWindow*);
	void set_postition(const sf::Vector2f&);
	void draw();
	void update(float);
	void set_speed(float);
	void animate();
#ifdef _DEBUG
	void log_position();
#endif // _DEBUG

};


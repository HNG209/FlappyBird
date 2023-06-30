#pragma once
#include"SFML/Graphics.hpp"
class Collider //all hittable objects will inherit from this class
{
public:
	sf::IntRect hitbox;//hitbox of the object
	Collider() = default;
	bool check_collision(const sf::IntRect&);
};


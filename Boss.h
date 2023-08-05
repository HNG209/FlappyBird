#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<random>
#include<time.h>
#include<iostream>
#include"Collider.h"
#define Rand(a, b) a + (rand() % b)

class Boss : public Collider
{
private:
	bool spawn = false;
	bool jmp = false;
	bool end = true;
	bool dir = false;//false: forward, true: backward
	const std::string boss_sprite_path = "Assets\\Collider\\bird.png";
	const float G = -981.f;
	const float base_vel = 650.f;
	const float movement_speed = 570.f;
	float vel = base_vel;
	float random_h;
	float dt;
	float timer;
	int index{};
	sf::Vector2f base_pos = { 2800.f, 500.f };
	sf::Texture boss_texture;
	sf::Sprite boss;
	sf::RenderWindow* window;
private:
	void jump();
	void appear(float);
	void disappear(float);
	void show_hitbox() {
		sf::RectangleShape r;
		r.setFillColor(sf::Color(0, 0, 255, 100));
		r.setSize(sf::Vector2f(hitbox.width, hitbox.height));
		r.setPosition(sf::Vector2f(hitbox.left, hitbox.top));
		window->draw(r);
	}
	inline float _map(float value, float value_min, float value_max, float rangeL, float rangeH) {
		return value * (rangeH - rangeL) / (value_max - value_min) + rangeL;
	}
	void attack(float, bool);
public:
	Boss(sf::RenderWindow*);
	bool boss_end() const;
	void draw();
	void reset();
	void update(float);
	void set_spawn(bool);
};


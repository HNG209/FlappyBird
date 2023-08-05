#pragma once
#include<SFML/Graphics.hpp>
#include<deque>
#include"Collider.h"
#include<iostream>
#include<ctime>
#include<random>
#include"Star.h"

#define Rand(a, b) a + (rand() % b)
struct _Pipe {
	std::pair<sf::Sprite, sf::Sprite> pipe; 
	std::pair<sf::IntRect, sf::IntRect> hitbox;
#if _DEBUG
	void show_hitbox(sf::RenderWindow* wnd) {
		sf::RectangleShape r0;
		r0.setFillColor(sf::Color(0, 0, 255, 100));
		r0.setSize(sf::Vector2f(hitbox.first.width, hitbox.first.height));
		r0.setPosition(sf::Vector2f(hitbox.first.left, hitbox.first.top));
		sf::RectangleShape r1;
		r1.setFillColor(sf::Color(0, 0, 255, 100));
		r1.setSize(sf::Vector2f(hitbox.second.width, hitbox.second.height));
		r1.setPosition(sf::Vector2f(hitbox.second.left, hitbox.second.top));
		wnd->draw(r0);
		wnd->draw(r1);
	}
#endif
	bool check_collision(const sf::IntRect& other) {
		if (other.intersects(hitbox.first) || other.intersects(hitbox.second)) return true;
		return false;
	}
};

class Pipes
{
private:
	sf::RenderWindow* window; 
	const std::string path = "Assets\\Collider\\pipes.png";
	sf::Texture Pipe_texture;
	float pipes_spacing = 300.f;//pipe spacing(Base = 300)
	const float pipes_spacing_min = 100.f;
	float pipes_spacing_width = 400.f;
	const float minimum_pipe_height = 300.f;//minimum height to generate
	float speed = 150.f;//moving speed(Base = 150)
	float animation_speed = 400.f;//pipe's grown speed(Base = 350)
	std::deque<_Pipe> pipes;
	std::deque<_Pipe> animation;
	Star* star;
	float dt;
	float gen_dt;
	float wait_time;
	float active_time;
	float fade_dt;
	int last_score;
	int index{};
	int j = 0;
	int tint = 255;
	bool gen_star{};
	bool star_hit{};
	bool hidden{};
	void scale(float);
public:
	Pipes(sf::RenderWindow*);

	void draw();
	void reset();
	void set_star_gen();
	void update(float);
	void generate(float);
	void animate(float);
	void hide(bool);
public:
	bool check();
	bool is_star_hit();
	bool check_star_gen();
	bool check_collisions(const sf::IntRect&);
	bool check_star_hit(const sf::IntRect&);
#if _DEBUG
	void show_hitboxes() {
		for (auto& i : animation)
			i.show_hitbox(window);
	}
#endif 
};

